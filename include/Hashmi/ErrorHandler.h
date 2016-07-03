# ifndef _HASHMI_ERROR_HANDLER_H_
# define _HASHMI_ERROR_HANDLER_H_

# include <Hashmi\includes.h>

namespace Hashmi
{
	class ErrorHandler
	{
	public:
		static void err(string msg1, string msg2 = "", string msg3 = "")
		{
			cout << msg1 << msg2 << msg3 << endl;
			throw msg1;
		}

		static void null_check(NiObjectRef obj)
		{
			if (obj == NULL)
			{
				err("A Dynamic Cast Failed");
			}
		}

		static bool isNull(NiObjectRef obj)
		{
			return (obj == NULL);
		}
	};
}


# endif