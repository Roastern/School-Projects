#include <iostream>
#include "Book.h"
#include "HashTable.h"
#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC
using std::cout;
using std::cin;
using std::endl;

int AsciiHash(string key);
void visit(Book data);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	HashTable<string, Book> table(10);

	table.setHash(AsciiHash);

	Book temp = {"C++: An Active Learning Approach", "Randal Albert", 635};
	table.Insert("0763757233", temp);

	Book temp1 = {"Rodeo for Dummies", "Calvin Caldwell", 1};
	table.Insert("7063757233", temp1);

	Book temp3 = {"And That n There", "Ralph Carestia", 1};
	table.Insert("7063757234", temp3);

	cout << table["0763757233"].m_title << endl;
	cout << table["7063757233"].m_title << endl;
	cout << table["7063757234"].m_title << endl;

	cout << endl << "Testing traversal" << endl;
	table.Traverse(visit);

	cout << endl << "Testing re-hashing" << endl;
	table.setHash(AsciiHash);

	table.Traverse(visit);

	cout << endl << "Testing copy constructor" << endl << endl;
	HashTable<string, Book> btable(table);
	btable.Traverse(visit);

	cout << endl << "Testing assignment operator" << endl << endl;
	HashTable<string, Book> ctable;
	ctable = btable;
	ctable.Traverse(visit);

	cout << endl << "Testing delete" << endl << endl;
	ctable.Delete("7063757234");
	ctable.Traverse(visit);

	cout << endl << "Attempting to delete data which doesn't exist" << endl;
	try
	{
		ctable.Delete("7063757234");
	}
	catch (char * msg)
	{
		cout << msg << endl;
	}

	ctable.Insert("7063757234", temp3);

	cout << endl << "Attempting to add data with duplicate key" << endl;
	try
	{
		ctable.Insert("7063757234", temp3);
	}
	catch (char * msg)
	{
		cout << msg << endl;
	}

	char c;
	cin >> c;

	return 0;
}

int AsciiHash(string key)
{
	int intK = 0;

	for (int i = 0; i < (int)key.size(); i++)
	{
		intK = intK + key[i];
	}

	return (intK % 10);
}

void visit(Book data)
{
	cout << data.m_title << " by " << data.m_author << " with " << data.m_pages << " page(s) " << endl;
}