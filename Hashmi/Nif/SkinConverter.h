#ifndef _SKINCONVERTER_H_
#define _SKINCONVERTER_H_


# include <includes.h>
# include <Nif\util.h>

# include <obj/BSDismemberSkinInstance.h>
#include <obj/NiSkinData.h>
#include <obj/NiSkinPartition.h>
# include <Ref.h>
# include <map>
#include <set>

# include <Nif\NifConverter.h>

namespace Hashmi
{
	class SkinConverter : NifConverter
	{
	
	private:
		
		

		void convert_geometry(NiTriStripsRef node)
		{
			
			NiTriShapeRef shape = DynamicCast<NiTriShape>(NiTriShape::Create());
						
			shape->SetName(node->GetName());
			shape->SetFlags(14);

			/////////////////////////////////////////////////
			//TriShape Data
			////////////////////////////////////////////////

			NiTriShapeDataRef shape_data = DynamicCast<NiTriShapeData>(NiTriShapeData::Create());
			NiTriStripsDataRef strip_data = DynamicCast<NiTriStripsData>(node->GetData()); null_check(strip_data,node->GetName() + " : has no TriStripData.");
			
			shape_data->SetVertices(strip_data->GetVertices());
			shape_data->SetNormals(strip_data->GetNormals());
						
			shape_data->SetTangents(strip_data->GetTangents());
			shape_data->SetBitangents(strip_data->GetBitangents());
			
			
			shape_data->SetTriangles(strip_data->GetTriangles());

			/////////////////////////////////////
			// UV
			/////////////////////////////////////
			shape_data->SetUVSetCount(strip_data->GetUVSetCount());
			for (unsigned int i = 0; i < shape_data->GetUVSetCount(); i++)
			{
				shape_data->SetUVSet(i,strip_data->GetUVSet(i));
			}
						

			NiGeometryDataRef shape_data_ = shape_data;

			shape->SetData(shape_data_);
						
			/////////////////////////////////////////////////
			//Skin Instance
			////////////////////////////////////////////////

			
			BSDismemberSkinInstanceRef skin = DynamicCast<BSDismemberSkinInstance>(BSDismemberSkinInstance::Create());
			skin->SetSkinData(node->GetSkinInstance()->GetSkinData());
			skin->SetSkinPartition(node->GetSkinInstance()->GetSkinPartition());
			
			skin->BindSkin(node->GetSkinInstance()->GetSkeletonRoot(),node->GetSkinInstance()->GetBones());

			
			vector<BodyPartList > partitions;
			BodyPartList part;
			part.partFlag = (BSPartFlag)(BSPartFlag::PF_START_NET_BONESET | BSPartFlag::PF_EDITOR_VISIBLE);
			part.bodyPart = BSDismemberBodyPartType::SBP_32_BODY;

			partitions.push_back(part);
			skin->SetPartitions(partitions);

			skin->SetSkinPartition(node->GetSkinInstance()->GetSkinPartition());

			NiSkinInstanceRef skin_ = skin;
			shape->SetSkinInstance(skin_);

			shape->SetBSProperties(node->GetBSProperties());	
			
			
			NiAVObjectRef old_chld = node;
			NiAVObjectRef new_chld = shape;

			node->GetParent()->AddChild(new_chld);	
			node->GetParent()->RemoveChild(old_chld);
			
		}

		void convert_tangents(NiTriStripsRef node)
		{
			
			NiBinaryExtraDataRef TSpaceRef;

			std::list<NiExtraDataRef> props = node->GetExtraData();
			std::list<NiExtraDataRef>::iterator prop;

			for( prop = props.begin(); prop != props.end(); ++prop )
			{
				if((*prop)->GetName() == "Tangent space (binormal & tangent vectors)") {
					TSpaceRef = DynamicCast<NiBinaryExtraData>(*prop);
					break;
				}
			}
			
			null_check(TSpaceRef,node->GetName() + " : No Tangent Space ExtraData was found");
			
			vector<byte> bin_data = TSpaceRef->GetData();

			
			vector<Vector3 > tangents;
			vector<Vector3 > bitangents;
			
			unsigned int pos = 0;
			int vtcount = node->GetData()->GetVertexCount();

			if (bin_data.size() != vtcount*2)
			{
				error(node->GetName()+" : Tangent Space ExtraData is not correct size. Should be '2 * Num-Vertices' bytes ");
			}
			

			for (int i = 0; i < vtcount; i++)
			{
				
				float x;
				float y;
				float z;
			
				x = Hashmi_Util::read_float(bin_data,pos);
				y = Hashmi_Util::read_float(bin_data,pos);
				z = Hashmi_Util::read_float(bin_data,pos);
				
				Vector3 v(x,y,z);
				tangents.push_back(v);
			}

			for (int i = 0; i < node->GetData()->GetVertexCount(); i++)
			{
				float x;
				float y;
				float z;
			
				x = Hashmi_Util::read_float(bin_data,pos);
				y = Hashmi_Util::read_float(bin_data,pos);
				z = Hashmi_Util::read_float(bin_data,pos);
				
				Vector3 v(x,y,z);
				bitangents.push_back(v);
			}

			node->GetData()->SetTangents(bitangents);
			node->GetData()->SetBitangents(tangents);
		}

		void convert_materials(NiTriStripsRef node)
		{
			vector< Ref<NiProperty> > properties = node->GetProperties();
			
			
			BSLightingShaderPropertyRef shader_prop = DynamicCast<BSLightingShaderProperty>(BSLightingShaderProperty::Create());
			BSShaderTextureSetRef txtr_set = DynamicCast<BSShaderTextureSet>(BSShaderTextureSet::Create());

			bool assigned_texture = false;
			bool assigned_mat = false;

			// Find old material and texture property and assign data to new ones
			for (unsigned int i = 0; i < properties.size(); i++)
			{
				NiMaterialPropertyRef mat_prop = DynamicCast<NiMaterialProperty>(properties[i]);			
				NiTexturingPropertyRef text_prop = DynamicCast<NiTexturingProperty>(properties[i]);			
								
				if (text_prop != NULL && !assigned_texture)
				{
					assigned_texture = true;
					string texture_path = text_prop->GetTexture(TexType::BASE_MAP).source->GetTextureFileName();					
					txtr_set->SetTexture(0,texture_path);
					txtr_set->SetTexture(1,Hashmi_Util::replace(texture_path,".dds","_N.dds"));
					txtr_set->SetTexture(3,"");
					txtr_set->SetTexture(4,"");
					txtr_set->SetTexture(5,"");
					txtr_set->SetTexture(6,"");
					txtr_set->SetTexture(7,"");
					txtr_set->SetTexture(8,"");
				}

				if (mat_prop != NULL && !assigned_mat)
				{
					assigned_mat = true;
					shader_prop->SetEmissiveColor(mat_prop->GetEmissiveColor());
					shader_prop->SetSpecularColor(mat_prop->GetSpecularColor());
					shader_prop->SetGlossiness(mat_prop->GetGlossiness());
					shader_prop->SetTextureClampMode(TexClampMode::WRAP_S_WRAP_T);
					shader_prop->SetShaderFlags1((SkyrimShaderPropertyFlags1)2185233155);
					shader_prop->SetShaderFlags2((SkyrimShaderPropertyFlags2)32769);
				}
				
			}

			if (! assigned_texture || !assigned_mat)
			{
				error(node->GetName() + ": No Texture or Material found.");
			}
						
			// link texture to material
			shader_prop->SetTextureSet(txtr_set);
			
			// assign material to node
			node->ClearProperties();
			node->SetBSProperty(0,(NiPropertyRef)shader_prop);

		}
				
		


	public:

		void convert(NiNodeRef root)
		{
			remove_unused_bones(root);
			rename_bones(root);

			vector< Ref<NiAVObject> >& children = root->GetChildren();
			for (unsigned int i =0; i < children.size(); i++)
			{
				Ref<NiObject> child = children[i];
				NiTriStripsRef tristrip_node = DynamicCast<NiTriStrips>(child);

				if (tristrip_node != NULL)
				{
			
					convert_materials(tristrip_node);
					convert_tangents(tristrip_node);
					convert_geometry(tristrip_node);
					
				}
			}
									
			
		}
		
		void extract_bone_names(NiNodeRef node, vector<string>& names)
		{
			names.push_back(node->GetName());

			vector< Ref<NiAVObject> > children = node->GetChildren();
			for (unsigned int i = 0; i < children.size(); i++)
			{
				Ref<NiObject> child = children[i];
				NiNodeRef child_ninode = DynamicCast<NiNode>(child);
				if (child_ninode != NULL)
				{
					extract_bone_names(child_ninode,names);
				}
			}

		}


	

	};
}

#endif
