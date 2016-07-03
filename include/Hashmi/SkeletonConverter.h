# ifndef _SKELETON_CONVERTER_H_
# define _SKELETON_CONVERTER_H_

# include <Hashmi\includes.h>
# include <Hashmi\NifConverter.h>
# include <Hashmi\NifFile.h>
# include <obj\bhkCapsuleShape.h>
# include <obj\bhkRigidBody.h>
# include <obj\bhkBlendCollisionObject.h>


namespace Hashmi
{

	class SkeletonConverter : NifConverter
	{
		
		bhkRigidBodyRef get_rigid_body(NiNodeRef node)
		{
			bhkBlendCollisionObjectRef coll_obj = DynamicCast<bhkBlendCollisionObject>(node->GetCollisionObject()); null_check(coll_obj);
			bhkRigidBodyRef rigid_body = DynamicCast<bhkRigidBody>(coll_obj->GetBody()); null_check(rigid_body);
			return rigid_body;
		}
		
		

		void remove_controllers_extradata(NiNodeRef node)
		{
			node->ClearControllers();
			node->ClearExtraData();

			vector< Ref<NiAVObject> >& children = node->GetChildren();
			for (unsigned int i =0; i < children.size(); i++)
			{
				Ref<NiAVObject> child = children[i];
				NiNodeRef child_ninode = DynamicCast<NiNode>(child);
				if (child_ninode != NULL)
				{
					remove_controllers_extradata(child_ninode);
				}				

			}
		}
		
		void tune_rigidBody(NiNodeRef node)
		{
			bhkRigidBodyRef rigid_body = get_rigid_body(node);
			rigid_body->SetMotionSystem(MotionSystem::MO_SYS_BOX);
			rigid_body->SetDeactivatorType(DeactivatorType::DEACTIVATOR_NEVER);
			rigid_body->SetSolverDeactivation(SolverDeactivation::SOLVER_DEACTIVATION_LOW);
			rigid_body->SetQualityType(MotionQuality::MO_QUAL_FIXED);
			
		}

		void tune_bhkRigidBody(NiNodeRef node)
		{
			cout << node->GetName() << endl;;
			if ((node->GetCollisionObject()) != NULL)
			{
				tune_rigidBody(node);
			}
			
			vector< Ref<NiAVObject> > children = node->GetChildren();
			for (unsigned int i =0; i < children.size(); i++)
			{
				Ref<NiAVObject> child = children[i];
				NiNodeRef child_ninode = DynamicCast<NiNode>(child);
				if (child_ninode != NULL)
				{
					tune_bhkRigidBody(child_ninode);
				}				

			}
		}

	public:
		void convert(NiNodeRef obl_root_, NiNodeRef template_root_)
		{
			
			NiNodeRef obl_root__ = find_node_OR_FAIL(obl_root_,"Bip01");
			obl_root_->ClearChildren();
			obl_root_ = obl_root__;
			obl_root_->SetName("NPC Root [Root]");


			remove_controllers_extradata(obl_root_);
			tune_bhkRigidBody(obl_root_);		


			NiNodeRef camera_node_ = find_node_OR_FAIL(template_root_,"Camera01.Target");			
			template_root_->ClearChildren();

			obl_root_->AddChild((NiAVObjectRef)camera_node_);
			template_root_->AddChild((NiAVObjectRef)obl_root_);
			int y = 0;
			
		}

	};
}
# endif
