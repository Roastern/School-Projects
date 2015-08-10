#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Stack.h"
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
void PushPopPeekTest(Stack<T> &astack);

void main()
{
	bool running = true;
	if (running)
	{
		Stack<int> astack(10);
		PushPopPeekTest(astack);
	}

	char c;
	std::cin >> c;
	_CrtDumpMemoryLeaks();
}

template<typename T>
void PushPopPeekTest(Stack<T> & astack)
{
	cout << "Testing Push() " << endl;
	for (int i = 0; i < 11; i++)
	{
		try
		{
			astack.Push(i);
		}
		catch (Exception & except)
		{
			cout << endl << "Testing overflow exception" << endl;
			cout << except << endl;
		}
	}
	cout << "Stack is full: " << astack.isFull() << endl;
	cout << "Stack is empty: " << astack.isEmpty() << endl;

	cout << endl << "Testing Pop() " << endl;
	for (int i = 10; i >= 0; i--)
	{
		try
		{
			cout << astack.Pop() << endl;
		}
		catch (Exception & except)
		{
			cout << endl << "Testing underflow exception" << endl;
			cout << except << endl;
		}
	}
	cout << "Stack is full: " << astack.isFull() << endl;
	cout << "Stack is empty: " << astack.isEmpty() << endl;

	for (int i = 0; i < 10; i++)
	{
		try
		{
			astack.Push(i);
		}
		catch (Exception & except)
		{
			cout << except << endl;
		}
	}

	cout << endl << "Testing copy constructor " << endl;
	Stack<int> bstack(astack);
	cout << bstack.Pop() << endl;
	cout << bstack.Pop() << endl;
	cout << bstack.Pop() << endl;
	cout << bstack.Pop() << endl;
	cout << bstack.Pop() << endl;
	cout << bstack.Pop() << endl;
	cout << endl << "Testing Peek() " << endl;
	cout << bstack.Peek() << endl;

	cout << endl << "Testing assignment operator" << endl;
	astack = bstack;
	cout << "Stack is full: " << astack.isFull() << endl;
	cout << "Stack is empty: " << astack.isEmpty() << endl;
	cout << astack.Peek() << endl;
	cout << astack.Pop() << endl;
	cout << astack.Pop() << endl;
	cout << astack.Pop() << endl;
	cout << astack.Pop() << endl;
	try
	{
		cout << astack.Peek() << endl;
	}
	catch (Exception &except)
	{
		cout << except << endl;
	}
}
