# ifndef _HASHMI_SKELETONHKX_H_
# define _HASHMI_SKELETONHKX_H_

# include <includes.h>
# include <rapidxml.hpp>

using namespace rapidxml;
namespace Hashmi
{
	class SkeletonHKX
	{
		struct Pose
		{
			Vector3 translation;
			Vector4 rotation;
			Vector3 scale;
		};

		vector<string> bone_names;
		vector<int> parent_indices;

		vector<string> bone_names_ragdoll;
		vector<int> parent_indices_ragdoll;

		vector<Pose> pose;
		vector<Pose> pose_ragdoll;

		void make(NiNodeRef nif_root)
		{
			xml_document<> doc;
			xml_node<>* decl = doc.allocate_node(node_declaration);
			decl->append_attribute(doc.allocate_attribute("version", "1.0"));
			decl->append_attribute(doc.allocate_attribute("encoding", "ascii"));
			doc.append_node(decl);

			xml_node<>* root = doc.allocate_node(node_element, "hkpackfile");
			root->append_attribute(doc.allocate_attribute("classversion", "1.0"));
			root->append_attribute(doc.allocate_attribute("contentsversion", "hk_2010.2.0-r1"));
			root->append_attribute(doc.allocate_attribute("toplevelobject", "#0115"));		
			doc.append_node(root);

			xml_node<>* data = doc.allocate_node(node_element, "hksection");
			data->append_attribute(doc.allocate_attribute("name", "__data__"));		
			doc.append_node(data);


		}



	};
}
# endif