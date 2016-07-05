#pragma once

# include <string>


using namespace std;

# include <Havok\XML.h>
namespace Hashmi

{
	class hkobject
	{
	protected:
		static int available_index;
		xml_node<>* xml_node_;

	public:
		string _name_;
		string _class_;
		string _signature_;

		hkobject(string class_, string signature_)
		{
			_name_ = to_string(static_cast<long long>(available_index++));
			//_name_ = name_;
			_class_ = class_;
			_signature_ = signature_;
					
		}

		void to_xml()
		{
			
				XML& xml = XML::getInstance();
				string attributes[] = 
				{
					"name",_name_,
					"class",_class_,
					"signature",_signature_
				};
				xml_node_ = xml.new_node("hkobject",attributes,3);
		}

		
		

	};
}