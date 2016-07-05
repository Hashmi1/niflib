#ifndef _NIFCONVERTER_H_
#define _NIFCONVERTER_H_

# include <includes.h>
# include <map>

namespace Hashmi
{
	class NifConverter
	{
	protected:
		void remove_unused_bones(NiNodeRef root)
		{

			vector<string> unused_bones;
			unused_bones.push_back("Bip01");
			unused_bones.push_back("Bip01 Neck");

			for (unsigned int j = 0; j < unused_bones.size(); j++)
			{

				vector< Ref<NiAVObject> >& children = root->GetChildren();
				for (unsigned int i =0; i < children.size(); i++)
				{
					Ref<NiAVObject> child = children[i]; 
					NiNodeRef child_ninode = DynamicCast<NiNode>(child);

					if (child_ninode == NULL)
					{
						continue;
					}

					if (unused_bones[j] == (child_ninode->GetName()) )
					{
						root->RemoveChild(child);
						break;
					}
				}
			}
		}

		void rename_bone(NiNodeRef bone, map<string, string>& name_mapping)
		{

			string bone_name = bone->GetName();
			if (name_mapping.count(bone_name) == 0)
			{
				//throw("No replacememt found");
				cout << bone_name << endl;
			}
			else
			{
				bone->SetName(name_mapping.at(bone_name));
			}
		}

		void rename_bones(NiNodeRef root, map<string,string>& name_map)
		{
			rename_bone(root, name_map);

			vector< Ref<NiAVObject> > children = root->GetChildren();
			for (unsigned int i =0; i < children.size(); i++)
			{
				Ref<NiObject> child = children[i];
				NiNodeRef child_ninode = DynamicCast<NiNode>(child);
				if (child_ninode != NULL)
				{
					rename_bones(child_ninode);
				}
			}
		}

		void rename_bones(NiNodeRef root)
		{
			map<string,string> name_mapping;

#pragma region name_mapping_

			name_mapping["Bip01"] = "NPC Root [Root]"; // Bip01
			name_mapping["Bip01 Root"] = "NPC Root [Root]";
			name_mapping["Bip01 COM"] = "NPC COM [COM ]";
			name_mapping["Bip01 Pelvis"] = "NPC Pelvis [Pelv]";
			name_mapping["Bip01 L Thigh"] = "NPC L Thigh [LThg]";
			name_mapping["Bip01 L Calf"] = "NPC L Calf [LClf]";
			name_mapping["Bip01 L Foot"] = "NPC L Foot [Lft ]";
			name_mapping["Bip01 L Toe0"] = "NPC L Toe0 [LToe]";
			name_mapping["Bip01 R Thigh"] = "NPC R Thigh [RThg]";
			name_mapping["Bip01 R Calf"] = "NPC R Calf [RClf]";
			name_mapping["Bip01 R Foot"] = "NPC R Foot [Rft ]";
			name_mapping["Bip01 R Toe0"] = "NPC R Toe0 [RToe]";
			name_mapping["WeaponDagger"] = "WeaponDagger";
			name_mapping["WeaponAxe"] = "WeaponAxe";
			name_mapping["WeaponSword"] = "WeaponSword";
			name_mapping["WeaponMace"] = "WeaponMace";
			name_mapping["SkirtFBone01"] = "SkirtFBone01";
			name_mapping["SkirtFBone02"] = "SkirtFBone02";
			name_mapping["SkirtFBone03"] = "SkirtFBone03";
			name_mapping["SkirtBBone01"] = "SkirtBBone01";
			name_mapping["SkirtBBone02"] = "SkirtBBone02";
			name_mapping["SkirtBBone03"] = "SkirtBBone03";
			name_mapping["SkirtLBone01"] = "SkirtLBone01";
			name_mapping["SkirtLBone02"] = "SkirtLBone02";
			name_mapping["SkirtLBone03"] = "SkirtLBone03";
			name_mapping["SkirtRBone01"] = "SkirtRBone01";
			name_mapping["SkirtRBone02"] = "SkirtRBone02";
			name_mapping["SkirtRBone03"] = "SkirtRBone03";
			name_mapping["Bip01 Spine"] = "NPC Spine [Spn0]";
			name_mapping["Bip01 Spine1"] = "NPC Spine1 [Spn1]";
			name_mapping["Bip01 Spine2"] = "NPC Spine2 [Spn2]";
			name_mapping["Bip01 Neck1"] = "NPC Neck [Neck]";   /////////////////////// neck
			name_mapping["Bip01 Head"] = "NPC Head [Head]";
			name_mapping["Bip01 Head MagicNode"] = "NPC Head MagicNode [Hmag]";
			name_mapping["Bip01EyeBone"] = "NPCEyeBone";
			name_mapping["Bip01 R Clavicle"] = "NPC R Clavicle [RClv]";
			name_mapping["Bip01 R UpperArm"] = "NPC R UpperArm [RUar]";
			name_mapping["Bip01 R Forearm"] = "NPC R Forearm [RLar]";
			name_mapping["Bip01 R Hand"] = "NPC R Hand [RHnd]";
			name_mapping["Bip01 R Finger0"] = "NPC R Finger00 [RF00]";
			name_mapping["Bip01 R Finger01"] = "NPC R Finger01 [RF01]";
			name_mapping["Bip01 R Finger02"] = "NPC R Finger02 [RF02]";
			name_mapping["Bip01 R Finger1"] = "NPC R Finger10 [RF10]";
			name_mapping["Bip01 R Finger11"] = "NPC R Finger11 [RF11]";
			name_mapping["Bip01 R Finger12"] = "NPC R Finger12 [RF12]";
			name_mapping["Bip01 R Finger2"] = "NPC R Finger20 [RF20]";
			name_mapping["Bip01 R Finger21"] = "NPC R Finger21 [RF21]";
			name_mapping["Bip01 R Finger22"] = "NPC R Finger22 [RF22]";
			name_mapping["Bip01 R Finger3"] = "NPC R Finger30 [RF30]";
			name_mapping["Bip01 R Finger31"] = "NPC R Finger31 [RF31]";
			name_mapping["Bip01 R Finger32"] = "NPC R Finger32 [RF32]";
			name_mapping["Bip01 R Finger4"] = "NPC R Finger40 [RF40]";
			name_mapping["Bip01 R Finger41"] = "NPC R Finger41 [RF41]";
			name_mapping["Bip01 R Finger42"] = "NPC R Finger42 [RF42]";
			name_mapping["Bip01 R MagicNode"] = "NPC R MagicNode [RMag]";
			name_mapping["WEAPON"] = "WEAPON";
			name_mapping["AnimObjectR"] = "AnimObjectR";
			name_mapping["Bip01 R ForearmTwist1"] = "NPC R ForearmTwist1 [RLt1]";
			name_mapping["Bip01 R ForearmTwist2"] = "NPC R ForearmTwist2 [RLt2]";
			name_mapping["Bip01 R UpperarmTwist1"] = "NPC R UpperarmTwist1 [RUt1]";
			name_mapping["Bip01 R UpperarmTwist2"] = "NPC R UpperarmTwist2 [RUt2]";
			name_mapping["Bip01 R Pauldron"] = "NPC R Pauldron";
			name_mapping["Bip01 L Clavicle"] = "NPC L Clavicle [LClv]";
			name_mapping["Bip01 L UpperArm"] = "NPC L UpperArm [LUar]";
			name_mapping["Bip01 L Forearm"] = "NPC L Forearm [LLar]";
			name_mapping["Bip01 L Hand"] = "NPC L Hand [LHnd]";
			name_mapping["Bip01 L Finger0"] = "NPC L Finger00 [LF00]";
			name_mapping["Bip01 L Finger01"] = "NPC L Finger01 [LF01]";
			name_mapping["Bip01 L Finger02"] = "NPC L Finger02 [LF02]";
			name_mapping["Bip01 L Finger1"] = "NPC L Finger10 [LF10]";
			name_mapping["Bip01 L Finger11"] = "NPC L Finger11 [LF11]";
			name_mapping["Bip01 L Finger12"] = "NPC L Finger12 [LF12]";
			name_mapping["Bip01 L Finger2"] = "NPC L Finger20 [LF20]";
			name_mapping["Bip01 L Finger21"] = "NPC L Finger21 [LF21]";
			name_mapping["Bip01 L Finger22"] = "NPC L Finger22 [LF22]";
			name_mapping["Bip01 L Finger3"] = "NPC L Finger30 [LF30]";
			name_mapping["Bip01 L Finger31"] = "NPC L Finger31 [LF31]";
			name_mapping["Bip01 L Finger32"] = "NPC L Finger32 [LF32]";
			name_mapping["Bip01 L Finger4"] = "NPC L Finger40 [LF40]";
			name_mapping["Bip01 L Finger41"] = "NPC L Finger41 [LF41]";
			name_mapping["Bip01 L Finger42"] = "NPC L Finger42 [LF42]";
			name_mapping["Bip01 L MagicNode"] = "NPC L MagicNode [LMag]";
			name_mapping["SHIELD"] = "SHIELD";
			name_mapping["AnimObjectL"] = "AnimObjectL";

			/////////////////////////
			//twists
			/////////////////

			name_mapping["Bip01 L ForearmTwist"] = "NPC L ForearmTwist2 [LLt2]";
			name_mapping["Bip01 L UpperarmTwist"] = "NPC L UpperarmTwist2 [LUt2]";
			name_mapping["Bip01 L UpperArmTwist"] = "NPC L UpperarmTwist2 [LUt2]";

			name_mapping["Bip01 R ForearmTwist"] = "NPC R ForearmTwist2 [RLt2]";			
			name_mapping["Bip01 R UpperarmTwist"] = "NPC R UpperarmTwist2 [RUt2]";
			name_mapping["Bip01 R UpperArmTwist"] = "NPC R UpperarmTwist2 [RUt2]";

			/////////////////////////
			//
			/////////////////


			name_mapping["Bip01 L ForearmTwist1"] = "NPC L ForearmTwist1 [LLt1]";
			name_mapping["Bip01 L ForearmTwist2"] = "NPC L ForearmTwist2 [LLt2]";
			name_mapping["Bip01 L UpperarmTwist1"] = "NPC L UpperarmTwist1 [LUt1]";
			name_mapping["Bip01 L UpperarmTwist2"] = "NPC L UpperarmTwist2 [LUt2]";
			name_mapping["Bip01 L Pauldron"] = "NPC L Pauldron";
#pragma endregion name_mapping_

			rename_bones(root,name_mapping);

		}

		void print_children(NiNodeRef root)
		{
			vector< Ref<NiAVObject> >& children = root->GetChildren();
			for (unsigned int i =0; i < children.size(); i++)
			{
				Ref<NiAVObject> child = children[i];
				string name = child->GetName();
				cout << name << endl;

			}
		}

		NiNodeRef find_node(NiNodeRef node, string name)
		{
			if (node->GetName() == name)
			{
				return node;
			}

			NiNodeRef required_node = NULL;

			vector< Ref<NiAVObject> >& children = node->GetChildren();
			for (unsigned int i =0; i < children.size(); i++)
			{
				Ref<NiAVObject> child = children[i];
				NiNodeRef child_ninode = DynamicCast<NiNode>(child);
				if (child_ninode != NULL)
				{
					required_node = find_node(child_ninode,name);
					if (required_node != NULL)
					{
						break;
					}
				}
				

			}

			return required_node;

			
		}

		NiNodeRef find_node_OR_FAIL(NiNodeRef node, string name, string err_msg = "A Node was not found")
		{
			NiNodeRef required_node = find_node(node,name);
			null_check(required_node, name + " was not found.");
			
			return required_node;
		}

		void error(string message)
		{
			cout << message << endl;
			throw -1;
		}

		template <typename T>
		void null_check(T obj, string message = "A Dynamic Cast Failed")
		{
			if (obj == NULL)
			{
				error(message);				
			}
		}

		

	};
}

#endif