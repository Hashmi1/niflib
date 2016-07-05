# include <string>
# include <map>
# include <rapidxml.hpp>
# include <rapidxml_print.hpp>


# include <iostream>

using namespace std;
using namespace rapidxml;

namespace Hashmi
{
	class XML
	{
	private:
		static XML* instance;
		xml_document<> doc;
		map<string,string> string_registry;

	public:
		

		static XML& getInstance()
		{
			if (instance == 0)
			{
				instance = new XML();
			}

			return *instance;
		}

		const char* str(string string_)
		{
			if (!string_registry.count(string_))
			{
				string_registry[string_] = string_;
			}

			return string_registry[string_].c_str();
		}

		xml_node<>* new_param(string name, int num_elements ,string data)
		{
			string attr[] =
			{
				"name",name,
				"numelements",Hashmi_Util::tostr(num_elements)
			};

			XML& xml = XML::getInstance();
			return xml.new_node("hkparam",attr,2,data);
		}

		xml_node<>* new_param(string name, string data)
		{
			string attr[] =
			{
				"name",name,
			};

			XML& xml = XML::getInstance();
			return xml.new_node("hkparam",attr,1,data);
		}

		xml_node<>* new_node(string type, string attributes[], int num_attr, string value="")
		{			

			xml_node<>* node = doc.allocate_node(node_element, str(type));

			for (int i = 0; i < num_attr*2; i = i + 2)
			{
				node->append_attribute(doc.allocate_attribute(str(attributes[i]), str(attributes[i+1])));						
			}

			if (value != "")
			{
				node->value(str(value));
			}
			
			return node;
		}

		void add_node(xml_node<>* node)
		{
			doc.append_node(node);
		}

		void print()
		{
			cout << doc;
		}
		

	};
};