#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Queue.h"
#include <iostream>
using namespace std;

void QueueTest();

int main()
{
	QueueTest();
	char c;
	cin >> c;
	_CrtDumpMemoryLeaks();
}

void QueueTest()
{
	Queue<int> aqueue;

	cout << "Testing isEmpty(): " << aqueue.isEmpty() << endl;
	cout << "Testing Enqueue()" << endl;
	for (int i = 0; i < 10; i++)
	{
		try
		{
			aqueue.Enqueue(i);
		}
		catch (Exception & except)
		{
			cout << except << endl;
		}
	}

	cout << "Testing isEmpty(): " << aqueue.isEmpty() << endl;
	cout << endl << "Testing Dequeue()" << endl;
	for (int i = aqueue.Size(); i >= 0; i--)
	{
		try
		{
			aqueue.Dequeue();
		}
		catch (Exception & except)
		{
			cout << except << endl;
		}
		cout << aqueue.Size() << endl;
	}

	for (int i = 0; i < 10; i++)
	{
		aqueue.Enqueue(i);
		cout << aqueue.Front() << endl;
	}

	cout << endl << "Testing copy constructor" << endl;
	Queue<int> bqueue = aqueue;
	cout << endl << "BSIZE " << bqueue.Size() << endl << endl;
	for (int i = bqueue.Size(); i > 4; i--)
	{
		cout << bqueue.Dequeue() << endl;
	}

	cout << endl << "Testing assignment operator" << endl;
	aqueue = bqueue;

	cout << "Testing isEmpty(): " << aqueue.isEmpty() << endl;
	for (int i = aqueue.Size(); i > 0; i--)
	{
		cout << aqueue.Dequeue() << endl;
	}

	cout << "Testing the ability to manipulate data at the front of the queue" << endl;
	aqueue.Enqueue(99);
	int &num = aqueue.Front();

	cout << "The value stored at the front of the queue is: " << num << endl;
	num = num + 1;
	cout << "The value stored at the front of the queue is now: " << aqueue.Front() << endl;
}