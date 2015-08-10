/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 5
* Filename:			DirectoryTree.cpp
* Date Created:		5/20/2014
* Modifications:	
*
************************************************************/

#ifndef DIRECTORYTREE_CPP_
#define DIRECTORYTREE_CPP_

#include "DirectoryTree.h"

/**********************************************************************	
* Purpose: Default constructor, sets dirRoot, name to empty strings, out
*			to cout, and folder to false
*
* Entry: No values are entered
*
* Exit: An empty DirectoryTree is created
*
************************************************************************/
DirectoryTree::DirectoryTree() : dirRoot(), name(), out(cout), folder(false)
{

}

/**********************************************************************	
* Purpose: sets dirRoot to the given value, name to 
*			an empty string, out to the given value, and folder to false
*
* Entry: nDirRoot is the string to be stored in dirRoot and nOut is the
*		 value to be stored in out
*
* Exit: A DirectoryTree is created storing the given values
*
************************************************************************/
DirectoryTree::DirectoryTree(string nDirRoot, ostream & nOut) : dirRoot(nDirRoot), name(), 
																out(nOut), folder(false)
{

}

/**********************************************************************	
* Purpose: sets dirRoot and name to the given strings, out to the given 
*		   value, and folder to the given value
*
* Entry: nDirRoot is the string to be stored in dirRoot 
*		 filename is the string to be stored in name
*		 nOut is the output stream to be stored in out
*		 isFolder is the value to be stored in folder
*
* Exit: A DirectoryTree is created storing the given values
*
************************************************************************/
DirectoryTree::DirectoryTree(string nDirRoot, string filename, ostream & nOut, bool isFolder) 
	                         : dirRoot(nDirRoot), name(filename), out(nOut), folder(isFolder)
{

}

/**********************************************************************	
* Purpose: sets dirRoot and name to the given strings, out to the given 
*		   value, and folder to the given value
*
* Entry: nDirRoot is the string to be stored in dirRoot 
*		 filename is the string to be stored in name
*		 nOut is the output stream to be stored in out
*		 isFolder is the value to be stored in folder
*
* Exit: A DirectoryTree is created storing the given values
*
************************************************************************/
DirectoryTree::DirectoryTree(const DirectoryTree & copy) : dirRoot(copy.dirRoot), name(copy.name), 
														   out(copy.out), folder(copy.folder)
{
	child = copy.child;
}

/**********************************************************************	
* Purpose: Sets all the values stored in the current DirectoryTree to 
*		   the values stored in the given Tree.
*
* Entry: copy is the DirectoryTree to be copied
*
* Exit: all the values stored in copy are copied into the current directory
*		tree.
*		The reference to the current directory tree is returned
*
************************************************************************/
DirectoryTree & DirectoryTree::operator=(const DirectoryTree & copy)
{
	if (this->name != copy.name)
	{
		name = copy.name;
		dirRoot = copy.dirRoot;
		child = copy.child;
		folder = copy.folder;
	}

	return *this;
}

/**********************************************************************	
* Purpose: Default destructor, destroys the directory tree
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned, the directory tree is destroyed
*
************************************************************************/
DirectoryTree::~DirectoryTree()
{
	Purge();
}

/**********************************************************************	
* Purpose: Deletes the entire directory tree
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned, the directory tree is deleted
*		dirRoot, name, and folder are reset to their default values
*
************************************************************************/
void DirectoryTree::Purge()
{
	dirRoot = string();
	name = string();
	folder = false;
	child.Purge();
}

/**********************************************************************	
* Purpose: Prints the directory tree header and calls PrintDirectoryTree(string)
*		   to print the entire directory tree
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
void DirectoryTree::PrintDirectoryTree() const
{
	out << "Listing directory tree stored at: " << dirRoot << endl;
	PrintDirectoryTree("");
}

/**********************************************************************	
* Purpose: Recursively prints the directory tree
*
* Entry: tab is the tab printed before the directory tree to indent the
*		 files/folders
*
* Exit: Nothing is returned
*
************************************************************************/
void DirectoryTree::PrintDirectoryTree(string tab) const
{
	if (dirRoot != "")
	{
		if (folder == true)
		{
			if (name == "")
			{
				out << tab << "Folder: " << dirRoot << endl;
			}
			else
				out << tab << "Folder: " << name << endl;
		}
		else
		{
			if (name == "")
			{
				out << tab << "File: " << dirRoot << endl;
			}
			else
				out << tab << "File: " << name << endl;
		}

		if (!child.isEmpty())
		{
			tab = tab + "\t";

			const Node<DirectoryTree> * cur = child.head;
			const DirectoryTree * pCur = &cur->data;

			pCur->PrintDirectoryTree(tab);

			do 
			{
				cur = cur->next;
				pCur = &cur->data;
				pCur->PrintDirectoryTree(tab);
			} while (cur != child.tail);
		}
	}
}

/**********************************************************************	
* Purpose: Calls PopulateDirectoryTree on the current directory trees
*		   dirRoot and name
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
void DirectoryTree::PopulateDirectoryTree()
{
	PopulateDirectoryTree(dirRoot, name);
}

/**********************************************************************	
* Purpose: Recursively populates the directory tree, changing the folder
*		   flag if the current object is a folder
*
* Entry: nDirRoot is the directory root to be evaluated, mask is the name
*		 of the current file/folder
*
* Exit: Nothing is returned
*
************************************************************************/
void DirectoryTree::PopulateDirectoryTree(string nDirRoot, string mask)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA FileFindData;

	string searchPath = nDirRoot + "\\";

	hFind = FindFirstFile((searchPath + "*").c_str(), &FileFindData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			string filename = FileFindData.cFileName;

			if (filename == ".." || filename == ".")
			{
				string newSearchPath = searchPath + filename;
				DirectoryTree * newTree = new DirectoryTree(newSearchPath, filename, out, false);
				child.Append(*newTree);
				delete newTree;
			}

			else
			{
				if (FileFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					string newSearchPath = searchPath + filename;
					DirectoryTree * newTree = new DirectoryTree(newSearchPath, filename, out, true);
					child.Append(*newTree);
					Node<DirectoryTree> * curr = child.tail;
					DirectoryTree * pCurr = &curr->data;
					pCurr->PopulateDirectoryTree();
					delete newTree;
				}
				else
				{
					string newSearchPath = searchPath + filename;
					DirectoryTree * newTree = new DirectoryTree(newSearchPath, filename, out, false);
					child.Append(*newTree);
					delete newTree;
				}

				folder = true;
			}
		} while ( FindNextFile(hFind, &FileFindData));
	}
}

/**********************************************************************	
* Purpose: Returns the directory root stored in the directory tree
*
* Entry: Nothing is passed into this function
*
* Exit: dirRoot is returned
*
************************************************************************/
string DirectoryTree::getDirRoot() const
{
	return dirRoot;
}

/**********************************************************************	
* Purpose: Returns the name stored in the directory tree
*
* Entry: Nothing is passed into this function
*
* Exit: name is returned
*
************************************************************************/
string DirectoryTree::getName() const
{
	return name;
}

#endif