#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <iostream>
#include "BinaryTreeNode.h"
#include "Queue.h"
using std::cout;

template<typename T>
class BinaryTree
{
public:
	BinaryTree();
	BinaryTree(const BinaryTreeNode<T> & nBinaryTreeNode);
	BinaryTree(const BinaryTree<T> & nTree);
	BinaryTree<T> & operator=(const BinaryTree<T> & nTree);
	~BinaryTree();

	void Insert(T newData);
	void Delete(T oldData);
	void Purge();
	int Height();
	void InOrderTraversal();
	void PreOrderTraversal();
	void PostOrderTraversal();
	void BreadthFirstTraversal();

private:
	void insert(T newData, BinaryTreeNode<T> & nRoot);
	bool pDelete(T oldData, BinaryTreeNode<T> & nRoot);
	void purge(BinaryTreeNode<T> * nRoot);
	void copyBinaryTreeNode(BinaryTreeNode<T> & nRoot, const BinaryTreeNode<T> * cRoot);
	int findHeight(BinaryTreeNode<T> * nRoot);
	BinaryTreeNode<T> * findLargestLeft(BinaryTreeNode<T> * nRoot);
	BinaryTreeNode<T> * findSmallestRight(BinaryTreeNode<T> * nRoot);
	void IOT(BinaryTreeNode<T> * nRoot);
	void PrOT(BinaryTreeNode<T> * nRoot);
	void POT(BinaryTreeNode<T> * nRoot);
	void BFT();
	BinaryTreeNode<T> * root;
	Queue<BinaryTreeNode<T>> BreadthQ;
};

template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr), BreadthQ()
{

}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTreeNode<T> & nBinaryTreeNode) : root(nBinaryTreeNode), BreadthQ()
{

}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> & nTree) : root(nullptr), BreadthQ()
{
	if (nTree.root != nullptr)
	{
		root = new BinaryTreeNode<T>(nTree.root->data);
		copyBinaryTreeNode(*root, nTree.root);
	}
}

template<typename T>
BinaryTree<T> & BinaryTree<T>::operator=(const BinaryTree<T> & nTree)
{
	if (this->root != nTree.root)
	{
		Purge();

		if (nTree.root != nullptr)
		{
			root = new BinaryTreeNode<T>(nTree.root->data);
			copyBinaryTreeNode(*root, nTree.root);
		}
	}

	return *this;
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	Purge();
}

template<typename T>
void BinaryTree<T>::Insert(T newData)
{
	if (root == nullptr)
		root = new BinaryTreeNode<T>(newData);
	else
		insert(newData, *root);
}

template<typename T>
void BinaryTree<T>::insert(T newData, BinaryTreeNode<T> & nRoot)
{
	bool ret = false;

	if (nRoot.data == newData)
	{
		throw Exception("Given data already exists in tree");
	}

	if (nRoot.data != newData)
	{
		if (newData < nRoot.data)
		{
			if (nRoot.l_child == nullptr)
				nRoot.l_child = new BinaryTreeNode<T>(newData);
			else
				insert(newData, *nRoot.l_child);
		}
		else
		{
			if (nRoot.r_child == nullptr)
				nRoot.r_child = new BinaryTreeNode<T>(newData);
			else
				insert(newData, *nRoot.r_child);
		}
	}
}

template<typename T>
void BinaryTree<T>::Delete(T oldData)
{
	pDelete(oldData, *root);
}

template<typename T>
bool BinaryTree<T>::pDelete(T oldData, BinaryTreeNode<T> & nRoot)
{
	bool nullify = false;

	if (nRoot.data == oldData)
	{
		if (nRoot.l_child == nullptr && nRoot.r_child == nullptr)
		{
			delete &nRoot;

			nullify = true;
		}
		else if (nRoot.l_child != nullptr)
		{
			BinaryTreeNode<T> * lBinaryTreeNode = findLargestLeft(nRoot.l_child);
			T temp = lBinaryTreeNode->data;
			this->Delete(temp);
			nRoot.setData(temp);
			if (nRoot.l_child != nullptr)
			{
				lBinaryTreeNode = findLargestLeft(nRoot.l_child);
				lBinaryTreeNode->r_child = nullptr;
			}
		}
		else
		{
			BinaryTreeNode<T> * rBinaryTreeNode = findSmallestRight(nRoot.r_child);
			T temp = rBinaryTreeNode->data;
			this->Delete(temp);
			nRoot.setData(temp);
			if (nRoot.r_child != nullptr)
			{
				rBinaryTreeNode = findSmallestRight(nRoot.r_child);
				rBinaryTreeNode->l_child = nullptr;
			}
		}
	}
	else if (nRoot.data > oldData)
	{
		if (nRoot.l_child != nullptr)
		{
			nullify = pDelete(oldData, *nRoot.l_child);

			if (nullify)
			{
				nRoot.l_child = nullptr;
				nullify = false;
			}
		}
	}
	else 
	{
		if (nRoot.r_child != nullptr)
		{
			nullify = pDelete(oldData, *nRoot.r_child);

			if (nullify)
			{
				nRoot.r_child = nullptr;
				nullify = false;
			}
		}
	}

	return nullify;
}

template<typename T>
void BinaryTree<T>::Purge()
{
	purge(root);
}

template<typename T>
int BinaryTree<T>::Height()
{
	int height;

	if (root != nullptr)
	{
		height = max(findHeight(root->getLChild()), findHeight(root->getRChild()));
	}
	else
		height = 0;

	return height;
}

template<typename T>
void BinaryTree<T>::purge(BinaryTreeNode<T> * nRoot)
{
	if (nRoot != nullptr)
	{
		purge(nRoot->l_child);
		purge(nRoot->r_child);
		delete nRoot;
	}
}

template<typename T>
void BinaryTree<T>::copyBinaryTreeNode(BinaryTreeNode<T> & nRoot, const BinaryTreeNode<T> * cRoot)
{
	if (cRoot->l_child != nullptr)
	{
		nRoot.l_child = new BinaryTreeNode<T>(cRoot->l_child->data);
		copyBinaryTreeNode(*nRoot.l_child, cRoot->l_child);
	}
	if (cRoot->r_child != nullptr)
	{
		nRoot.r_child = new BinaryTreeNode<T>(cRoot->r_child->data);
		copyBinaryTreeNode(*nRoot.r_child, cRoot->r_child);
	}
}

template<typename T>
int BinaryTree<T>::findHeight(BinaryTreeNode<T> * nRoot)
{
	int ret; 

	if (nRoot == nullptr)
		ret = 0;
	else
		ret = 1 + max(findHeight(nRoot->getLChild()), findHeight(nRoot->getRChild()));

	return ret;
}

template<typename T>
BinaryTreeNode<T> * BinaryTree<T>::findLargestLeft(BinaryTreeNode<T> * nRoot)
{
	BinaryTreeNode<T> * retBinaryTreeNode;

	if (nRoot == nullptr)
		retBinaryTreeNode = nullptr;
	else if (nRoot->r_child != nullptr)
		retBinaryTreeNode = findLargestLeft(nRoot->r_child);
	else
		retBinaryTreeNode = nRoot;

	return retBinaryTreeNode;
}

template<typename T>
BinaryTreeNode<T> * BinaryTree<T>::findSmallestRight(BinaryTreeNode<T> * nRoot)
{
	BinaryTreeNode<T> * retBinaryTreeNode;

	if (nRoot->l_child != nullptr)
		retBinaryTreeNode = findSmallestRight(nRoot->l_child);
	else
		retBinaryTreeNode = nRoot;

	return retBinaryTreeNode;
}

template<typename T>
void BinaryTree<T>::InOrderTraversal()
{
	IOT(root);
}

template<typename T>
void BinaryTree<T>::PreOrderTraversal()
{
	PrOT(root);
}

template<typename T>
void BinaryTree<T>::PostOrderTraversal()
{
	POT(root);
}

template<typename T>
void BinaryTree<T>::BreadthFirstTraversal()
{
	if (root != nullptr)
	{
		BreadthQ.Enqueue(*root);
		BFT();
	}
}

template<typename T>
void BinaryTree<T>::PrOT(BinaryTreeNode<T> * nRoot)
{
	if (nRoot != nullptr)
	{
		cout << nRoot->getData() << " ";
		PrOT(nRoot->getLChild());
		PrOT(nRoot->getRChild());
	}
}

template<typename T>
void BinaryTree<T>::POT(BinaryTreeNode<T> * nRoot)
{
	if (nRoot != nullptr)
	{
		POT(nRoot->getLChild());
		POT(nRoot->getRChild());
		cout << nRoot->getData() << " ";
	}
}

template<typename T>
void BinaryTree<T>::IOT(BinaryTreeNode<T> * nRoot)
{
	if (nRoot != nullptr)
	{
		IOT(nRoot->l_child);
		cout << nRoot->data << " ";
		IOT(nRoot->r_child);
	}
}

template<typename T>
void BinaryTree<T>::BFT()
{
	while (!BreadthQ.isEmpty())
	{
		BinaryTreeNode<T> temp = BreadthQ.Dequeue();
		cout << temp.data << " ";

		if (temp.l_child != nullptr)
			BreadthQ.Enqueue(*temp.l_child);

		if (temp.r_child != nullptr)
			BreadthQ.Enqueue(*temp.r_child);
	}
}

#endif