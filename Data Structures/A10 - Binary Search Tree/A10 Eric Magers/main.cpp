#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "BinaryTree.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

void testIntBinTree();
void testStrBinTree();

int main()
{
	testIntBinTree();
	cout << endl << endl;
	testStrBinTree();

	char c;
	cin >> c;
	_CrtDumpMemoryLeaks();
	return 0;
}

void testStrBinTree()
{
	cout << "Testing Binary Tree functions with strings" << endl << endl;
	cout << "Testing default constructor: " << endl;
	BinaryTree<string> aTree;

	cout << endl << "Testing height of tree function: " << endl;
	cout << aTree.Height() << endl;

	cout << "Testing insert with In Order Traversals:" << endl;
	aTree.Insert("6");
	aTree.InOrderTraversal();
	cout << endl << "Testing data entry for data that already exists in tree:" << endl;
	try
	{
		aTree.Insert("6");
	}
	catch (Exception & except)
	{
		cout << except << endl;
	}
	aTree.Insert("3");
	aTree.Insert("8");
	aTree.InOrderTraversal();
	cout << endl;
	aTree.Insert("10");
	aTree.Insert("4");
	aTree.Insert("9");
	aTree.InOrderTraversal();
	cout << endl;
	aTree.Insert("22");
	aTree.Insert("15");
	aTree.Insert("1");
	aTree.InOrderTraversal();
	cout << endl;
	aTree.Insert("567");
	aTree.InOrderTraversal();
	cout << endl;

	cout << endl << "Testing height of tree function: " << endl;
	cout << aTree.Height() << endl;

	cout << endl << "Testing deletion of node with no children (567): " << endl;
	aTree.Delete("567");
	aTree.InOrderTraversal();
	cout << endl;

	cout << endl << "Testing deletion of node with one child (3): " << endl;
	aTree.Delete("3");
	aTree.InOrderTraversal();
	cout << endl;

	cout << endl << "Testing deletion of node with two children (6)" << endl;
	aTree.Delete("6");
	aTree.InOrderTraversal();
	cout << endl;

	cout << endl << "Testing Breadth First Traversal: " << endl;
	aTree.BreadthFirstTraversal();
	cout << endl;

	cout << endl << "Testing Post Order Traversal: " << endl;
	aTree.PostOrderTraversal();
	cout << endl;

	cout << endl << "Testing Pre Order Traversal" << endl;
	aTree.PreOrderTraversal();
	cout << endl;

	cout << endl << "Testing copy contructor: " << endl;
	BinaryTree<string> bTree(aTree);
	bTree.PreOrderTraversal();

	cout << endl << endl << "Testing assignment operator: " << endl;
	BinaryTree<string> cTree;
	cTree = aTree;
	cTree.PreOrderTraversal();

}

void testIntBinTree()
{
	cout << "Testing Binary Tree functions with ints" << endl << endl;
	cout << "Testing default constructor: " << endl;
	BinaryTree<int> aTree;

	cout << endl << "Testing height of tree function: " << endl;
	cout << aTree.Height() << endl;

	cout << "Testing insert with In Order Traversals:" << endl;
	aTree.Insert(6);
	aTree.InOrderTraversal();
	cout << endl << "Testing data entry for data that already exists in tree:" << endl;
	try
	{
		aTree.Insert(6);
	}
	catch (Exception & except)
	{
		cout << except << endl;
	}
	aTree.Insert(3);
	aTree.Insert(8);
	aTree.InOrderTraversal();
	cout << endl;
	aTree.Insert(10);
	aTree.Insert(4);
	aTree.Insert(9);
	aTree.InOrderTraversal();
	cout << endl;
	aTree.Insert(22);
	aTree.Insert(15);
	aTree.Insert(1);
	aTree.InOrderTraversal();
	cout << endl;
	aTree.Insert(567);
	aTree.InOrderTraversal();
	cout << endl;

	cout << endl << "Testing height of tree function: " << endl;
	cout << aTree.Height() << endl;

	cout << endl << "Testing deletion of node with no children (567): " << endl;
	aTree.Delete(567);
	aTree.InOrderTraversal();
	cout << endl;

	cout << endl << "Testing deletion of node with one child (3): " << endl;
	aTree.Delete(3);
	aTree.InOrderTraversal();
	cout << endl;

	cout << endl << "Testing deletion of node with two children (6)" << endl;
	aTree.Delete(6);
	aTree.InOrderTraversal();
	cout << endl;

	cout << endl << "Testing Breadth First Traversal: " << endl;
	aTree.BreadthFirstTraversal();
	cout << endl;

	cout << endl << "Testing Post Order Traversal: " << endl;
	aTree.PostOrderTraversal();
	cout << endl;

	cout << endl << "Testing Pre Order Traversal" << endl;
	aTree.PreOrderTraversal();
	cout << endl;

	cout << endl << "Testing copy contructor: " << endl;
	BinaryTree<int> bTree(aTree);
	bTree.PreOrderTraversal();

	cout << endl << endl << "Testing assignment operator: " << endl;
	BinaryTree<int> cTree;
	cTree = aTree;
	cTree.PreOrderTraversal();

}