# pragma once
# include <Havok\hkobject.h>
# include <includes.h>

namespace Hashmi
{
	class xxx : hkobject
	{
	};
}


namespace Hashmi
{
	class hkpCapsuleShape : hkobject
	{
		float radius;
		Vector3 v1;
		Vector3 v2;

		hkpCapsuleShape(float radius_, Vector3 v1_, Vector3 v2_) : hkobject("hkpCapsuleShape","0xdd0b1fd3")
		{
			radius = radius_;
			v1 = v1_;
			v2 = v2_;			
		}

		string to_string(Vector3 v)
		{
			stringstream ss;			
			ss << "(" << v.x << " " << v.y << " " << v.z <<  " " << radius << ")";
			return ss.str();
		}

		void to_xml()
		{
			XML& xml = XML::getInstance();

			string attributes_rad[] = 
			{				
				"name","radius"
			};

			string attributes_v1[] = 
			{				
				"name","vertexA"
			};
				

			string attributes_v2[] = 
			{				
				"name","vertexB"
			};
				
						
			xml_node<>* rad_ = xml.new_node("hkparam",attributes_rad,1,Hashmi_Util::tostr(radius));
			xml_node<>* v1_ = xml.new_node("hkparam",attributes_v1,1,to_string(v1));
			xml_node<>* v2_ = xml.new_node("hkparam",attributes_v2,1,to_string(v2));

			xml_node_->append_node(xml.new_param("userData","0"));
			xml_node_->append_node(rad_);
			xml_node_->append_node(v1_);
			xml_node_->append_node(v2_);

		}
		


	};
}

