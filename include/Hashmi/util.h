#ifndef _UTIL_HASHMI_H_
#define _UTIL_HASHMI_H_

#include <vector>
#include<string>

using namespace std;

class String_Util
{
public:
	static unsigned int get_max_len(vector<string> list_strings)
	{
		if (list_strings.size() == 0)
		{
			throw ("Error: list_strings is empty");
		}

		unsigned int max_len = list_strings[0].length();

		for (int i = 0; i < list_strings.size(); i++)
		{
			if (list_strings[i].length() > max_len)
			{
				max_len = list_strings[i].length();
			}
		}

		return max_len;
		
	}
};

#endif
