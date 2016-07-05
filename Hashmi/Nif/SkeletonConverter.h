# ifndef _SKELETON_CONVERTER_H_
# define _SKELETON_CONVERTER_H_


# include <includes.h>
# include <Nif\NifConverter.h>
# include <Nif\NifFile.h>
# include <obj\bhkCapsuleShape.h>
# include <obj\bhkRigidBody.h>
# include <obj\bhkBlendCollisionObject.h>
# include <obj\bhkSphereShape.h>


namespace Hashmi
{

	class SkeletonConverter : NifConverter
	{
		
		
		bhkRigidBodyRef get_rigid_body(NiNodeRef node) // Assuming all collision objects are rigidbody
		{
			bhkBlendCollisionObjectRef coll_obj = DynamicCast<bhkBlendCollisionObject>(node->GetCollisionObject()); null_check(coll_obj,node->GetName() + " does not have bhkBlendCollisionObject");
			bhkRigidBodyRef rigid_body = DynamicCast<bhkRigidBody>(coll_obj->GetBody()); null_check(rigid_body,node->GetName() + " does not have bhkRigidBody");
			return rigid_body;
		}

		void convert(NiNodeRef node)
		{

			remove_depreciated_data(node);
			replace_spheres(node);			
			tune_bhkRigidBody(node);

			vector< Ref<NiAVObject> >& children = node->GetChildren();
			for (unsigned int i =0; i < children.size(); i++)
			{
				Ref<NiAVObject> child = children[i];
				NiNodeRef child_ninode = DynamicCast<NiNode>(child);
				if (child_ninode != NULL)
				{
					convert(child_ninode);
				}				
			}
		}

		void replace_spheres(NiNodeRef node)
		{
			if (node->GetCollisionObject() != NULL)
			{
				bhkRigidBodyRef rigid_body = get_rigid_body(node);
				bhkSphereShapeRef sphere = DynamicCast<bhkSphereShape>(rigid_body->GetShape());
				if (sphere != NULL)
				{
					bhkCapsuleShapeRef capsule = DynamicCast<bhkCapsuleShape>( bhkCapsuleShape::Create());
					capsule->SetRadius(sphere->GetRadius());
					capsule->SetFirstPoint(Vector3(0,0,0));
					capsule->SetSecondPoint(Vector3(0,0,0));
					capsule->SetRadius1(sphere->GetRadius());
					capsule->SetRadius2(sphere->GetRadius());
					capsule->SetMaterial(HavokMaterial::HAV_MAT_SKIN);

					rigid_body->SetShape(capsule);
				}
			}
		}
		
		void remove_depreciated_data(NiNodeRef node)
		{
			node->ClearControllers();
			node->ClearExtraData();
			
		}

		void tune_bhkRigidBody(NiNodeRef node)
		{
			
			if ((node->GetCollisionObject()) != NULL)
			{
				bhkRigidBodyRef rigid_body = get_rigid_body(node);
				rigid_body->SetMotionSystem(MotionSystem::MO_SYS_BOX);
				rigid_body->SetDeactivatorType(DeactivatorType::DEACTIVATOR_NEVER);
				rigid_body->SetSolverDeactivation(SolverDeactivation::SOLVER_DEACTIVATION_LOW);
				rigid_body->SetQualityType(MotionQuality::MO_QUAL_FIXED);
			}			
			
		}


	public:
		void convert(NiNodeRef obl_root_, NiNodeRef template_root_)
		{
			
			NiNodeRef obl_root__ = find_node_OR_FAIL(obl_root_,"Bip01");
			obl_root_->ClearChildren();
			obl_root_ = obl_root__;
			obl_root_->SetName("NPC Root [Root]");


			convert(obl_root_);
			
			NiNodeRef camera_node_ = find_node_OR_FAIL(template_root_,"Camera01.Target");			
			template_root_->ClearChildren();

			obl_root_->AddChild((NiAVObjectRef)camera_node_);
			template_root_->AddChild((NiAVObjectRef)obl_root_);
						
		}

	};
}
# endif
