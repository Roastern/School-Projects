/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 5
* Filename:			DirectoryTree.h
* Date Created:		5/20/2014
* Modifications:	
*
************************************************************/

#ifndef DIRECTORYTREE_H_
#define DIRECTORYTREE_H_

#include <Windows.h>
#include <iostream>
#include <string>
#include "doublelinkedlist.h"
#include "Exception.h"
using std::string;
using std::cout;

/************************************************************************
* Class: DirectoryTree
*
* Purpose: This class creates a double linked list of Node objects
*
* Manager functions:	
* 	DirectoryTree ( )
* 		Creates a DirectoryTree object which is storing no data	
*	DirectoryTree (string nDirRoot, ostream & nOut)
*		Creates a directoryTree with a directory root and output stream specified
*	DirectoryTree (string nDirRoot, string filename, ostream & nOut, bool isFolder)
*		Creates a DirectoryTree with a directory root, filename output stream and 
*		folder flag specified
*	DirectoryTree (const DirectoryTree & copy)
*		Copies the data from copy into a new Directory Tree
*	DirectoryTree & operator=(const DirectoryTree & copy)
*		Copies all the data stored in the given directory tree (copy) and places it in
*		the current directory tree
*	~DirectoryTree ( )
*		Calls Purge() to delete the directory tree
*
* Methods:		
*
*	PopulateDirectoryTree ( )
*		Populates the directory tree by calling the overloaded PopulateDirectoryTree
*	PrintDirectoryTree ( ) const
*		Prints the directory tree to the stored output stream
*	Purge ( )
*		Destroyes the directory tree
*	getDirRoot ( ) const
*		Returns the directory root
*	getName ( ) const
*		Returns the name of the file/folder stored at the directory root
*	PopulateDirectoryTree (string nDirRoot, string name)
*		Populates the directory tree recursively
*	PrintDirectoryTree (string tab) const
*		Prints the directory tree to the stored output stream
*************************************************************************/

class DirectoryTree
{
private:
	string dirRoot;
	string name;
	bool folder;
	DoubleLinkedList<DirectoryTree> child;
	ostream & out;

	void PopulateDirectoryTree(string nDirRoot, string name);
	void PrintDirectoryTree(string tab) const;

public:
	DirectoryTree();
	DirectoryTree(string nDirRoot, ostream & nOut);
	DirectoryTree(string nDirRoot, string filename, ostream & nOut, bool isFolder);
	DirectoryTree(const DirectoryTree & copy);
	DirectoryTree & operator=(const DirectoryTree & copy);
	~DirectoryTree();

	void PopulateDirectoryTree();
	void PrintDirectoryTree() const;
	void Purge();

	string getDirRoot() const;
	string getName() const;
};

#endif