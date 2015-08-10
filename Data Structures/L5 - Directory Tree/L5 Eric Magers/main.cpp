/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 5
* Filename:			main.cpp
* Date Created:		5/20/2014
* Modifications:	
*
* Overview:
*	This program stores all files/folders within the given path
*	on the hard drive to a directory tree, which then prints the
*	names of the files and folders to a text document
*
* Input:
*	Input is passed as a command line arugument. Input must be a 
*	file path without the '\' at the end. For instance, to traverse
*	the entire C drive, you must pass 'C:' as the command line argument
*
* Output:
*	Output for this program will be in the following form:
*	The root of the directory (the directory passed in from the command line
*		The all files and folders stored in directory
*
*	Each level of folders/files will be indented by an additional tab
*
************************************************************/

#include <stdlib.h>
#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC
#include "DirectoryTree.h"
#include <iostream>
#include <fstream>
using std::cout;

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	string startPath = argv[1];

	ofstream file;
	file.open("Directory Tree.txt");
	
	DirectoryTree newTree(startPath, file);
	newTree.PopulateDirectoryTree();
	//newTree.PrintDirectoryTree();

	file.close();

	return 0;
}