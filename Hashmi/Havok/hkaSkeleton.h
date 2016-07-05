# include <includes.h>
# include <Havok\hkobject.h>
# include <map>

using namespace std;

namespace Hashmi
{
	class hkaSkeleton : hkobject
	{
		struct Pose
		{
			Vector3 translation;
			Quaternion rotation;
			Vector3 scale;
		};


		string root;
		vector<string> bones;
		map<string,int> bone_indices;
		vector<int> parent_indices;
		
		vector<Pose> pose;

		string to_string(vector<int> lst)
		{
			stringstream ss;
			ss << endl;
			for (unsigned int i = 0; i < parent_indices.size()-1; i++)
			{
				ss << parent_indices[i] << " ";
			}
			ss  << parent_indices[parent_indices.size()-1] << endl;
		}

		hkaSkeleton() : hkobject("hkaSkeleton","0x366e8220")
		{

		}

		void to_xml()
		{
			XML& xml = XML::getInstance();
			xml_node_->append_node(xml.new_param("name","NPC Root [Root]"));
			xml_node_->append_node(xml.new_param("parentIndices",parent_indices.size(),to_string(parent_indices)));
			

		}

		bool isRoot(NiNodeRef node)
		{
			return (node->GetParent() == NULL);
		}

		void read_nif(NiNodeRef node)
		{
						
			bones.push_back(node->GetName());
			bone_indices[node->GetName()] = bones.size()-1; 

			if (isRoot(node))
			{
				root = node->GetName();
				parent_indices.push_back(-1);
			}

			else
			{					
				int parent_index = bone_indices[node->GetParent()->GetName()];
				parent_indices.push_back(parent_index);
			}
			
			Pose bone_pose;

			bone_pose.translation = node->GetLocalTranslation();
			bone_pose.rotation = node->GetLocalRotation().AsQuaternion();
			bone_pose.scale = Vector3(node->GetLocalScale(),1,1);

			pose.push_back(bone_pose);

			vector< Ref<NiAVObject> >& children = node->GetChildren();
			for (unsigned int i =0; i < children.size(); i++)
			{
				Ref<NiAVObject> child = children[i];
				NiNodeRef child_ninode = DynamicCast<NiNode>(child);
				if (child_ninode != NULL)
				{
					read_nif(child_ninode);
				}				
			}
		}

		
	};
}