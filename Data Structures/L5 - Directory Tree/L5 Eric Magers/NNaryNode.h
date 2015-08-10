#ifndef NNaryNODE_H_
#define NNaryNODE_H_

#include "DoubleLinkedList.h"
#include "Exception.h"

template<typename T>
ostream & NNaryNode<T>::operator<<(ostream & out, NNaryNode<T> & nNode)
{
	out << data;
	
	return out;
}

template<typename T>
class NNaryNode
{
	friend DirectoryTree;
	friend ostream & operator<<(ostream & out, NNaryNode<T> & nNode);

private:
	NNaryNode<T> * parent;
	DoubleLinkedList<NNaryNode<T>> child;
	T data;

public:
	NNaryNode();
	NNaryNode(T newData);
	NNaryNode(const NNaryNode<T> & copy);
	NNaryNode<T> & operator=(const NNaryNode<T> & copy);
	~NNaryNode();

	const NNaryNode<T> & getParent() const;
	const NNaryNode<T> & getChild(int index);
	T getData();

	void setParent(const NNaryNode<T> & nParent);
	void setChild(T newData);
	void setData(T newData);
};

template<typename T>
NNaryNode<T>::NNaryNode() : parent(nullptr), child(), data()
{

}

template<typename T>
NNaryNode<T>::NNaryNode(T newData) : parent(nullptr), child(), data(newData)
{

}

template<typename T>
NNaryNode<T>::NNaryNode(const NNaryNode<T> & copy) : parent(copy.parent), child(copy.child), 
													 data(copy.data)
{

}

template<typename T>
NNaryNode<T> & NNaryNode<T>::operator=(const NNaryNode<T> & copy)
{
	if (this != *copy)
	{
		parent = copy.parent;
		child = copy.child;
		data = copy.data;
	}
	
	return *this;
}

template<typename T>
NNaryNode<T>::~NNaryNode()
{
	parent = nullptr;
	child.Purge();
}

template<typename T>
NNaryNode<T> & NNaryNode<T>::getParent() const
{
	return parent;
}

template<typename T>
NNaryNode<T> & NNaryNode<T>::getChild(int index) const
{
	if (index < 0)
	{
		throw Exception("Index exceeds lower bounds");
	}
	else if (index > child.Size())
	{
		throw Exception("Index exceeds upper bounds");
	}

	count = 0;
	DoubleLinkedList<NNaryNode<T> *> * curr = child.First();

	while (count != index)
	{
		curr = curr->next;
	}

	return *curr;
}

template<typename T>
T NNaryNode<T>::getData() const
{
	return data;
}

template<typename T>
void NNaryNode<T>::setParent(const NNaryNode<T> & nParent)
{
	parent = nParent;
}

template<typename T>
void NNaryNode<T>::setChild(T newData)
{
	child.Append(newData);
}

template<typename T>
void NNaryNode<T>::setData(T newData)
{
	data = newData;
}

#endif