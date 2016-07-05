#ifndef _NIFFILE_H_
#define _NIFFILE_H_

# include <includes.h>

namespace Hashmi
{
	struct NifFile
	{
	private:
		NifInfo					nifInfo;
		NiNodeRef				root_;
	public:

		NifFile(string file)
		{
			root_ = DynamicCast<NiNode>(ReadNifTree(file,&nifInfo));
			if (root_ == NULL)
			{
				throw("Error Root is not NiNode");
			}
			
		}

		NifFile(NiNodeRef root)
		{
			root_ = root;			
		}


		static NiNodeRef open(string file_)
		{
			NifFile nif(file_);
			return nif.root();
		}

		NiNodeRef root()
		{
			return root_;
		}

		void write(string file)
		{
			WriteNifTree(file,root_,nifInfo);
		}
		
		void change_version()
		{
			nifInfo.version = VER_20_2_0_7;
			nifInfo.userVersion = 12;
			nifInfo.userVersion2 = 83;
			nifInfo.exportInfo2 = " PE Skinned Geometry (Dismem)";
		}

	};
}

# endif