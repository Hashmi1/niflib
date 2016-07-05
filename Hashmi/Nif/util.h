#ifndef _UTIL_HASHMI_H_
#define _UTIL_HASHMI_H_

#include <vector>
#include<string>
# include <iostream>

using namespace std;

class Hashmi_Util
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
	static string replace(string text, string replace_this, string with_this)
	{
				
		unsigned int pos = text.find(replace_this);
		if (pos == -1)
		{
			return text;
		}

		string output = text.replace(pos,replace_this.length(),with_this);
		return output;
				
	}
	static float read_float(vector<unsigned char>& bin, unsigned int& pos)
	{

		float f;

		unsigned char b[] = {bin[pos], bin[pos+1], bin[pos+2], bin[pos+3]};		
		memcpy(&f, &b, 4);
		pos += 4;

		return f;
	}
	template <typename T> static string tostr(const T& t) { 
		ostringstream os; 
		os<<t; 
		return os.str(); 
	}
};

#endif
