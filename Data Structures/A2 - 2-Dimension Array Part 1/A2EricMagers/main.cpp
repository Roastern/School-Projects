#include "Array2D.cpp"
#include <iostream>
#include <string>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void testInts();
void testStrings();
template<typename T>
void printArray(Array2D<T> &boo);
template<typename T>
void initializeArrayInts(Array2D<T> &boo);
template<typename T>
void initializeArrayStrings(Array2D<T> &boo);
template<typename T>
void printArray(const Array2D<T> &boo);

int main()
{
	testInts();
	testStrings();

	#ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory leaks!" << endl;
	}
	#endif

	char c;
	cin >> c;
	return 0;
}

void testInts()
{
	cout << "Testing with a simple data type: integers" << endl;
	cout << "First, we'll test the constructors:" << endl;

	cout << "Testing the default constructor, row and column should = 0)" << endl;
	Array2D<int> blob;
	cout << "Rows: " << blob.getRow() << " Columns: " << blob.getColumn() << endl << endl;

	cout << "Testing the constructor with both rows and columns defined at initialization: " << endl;
	Array2D<int> boo(3, 5);
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;

	cout << "Testing subscript operators with valid input: " << endl;
	initializeArrayInts(boo);
	printArray(boo);

	cout << "Testing copy constructor: " << endl;
	Array2D<int> bo(boo);
	cout << "Rows: " << bo.getRow() << " Columns: " << bo.getColumn() << endl << endl;
	printArray(bo);

	cout << "Testing the assignment operator: " << endl;
	blob = bo;
	cout << "Rows: " << blob.getRow() << " Columns: " << blob.getColumn() << endl << endl;
	printArray(blob);

	cout << "Now testing mutator functions for both rows and columns: " << endl << endl;
	cout << "First with adding rows: " << endl;
	boo.setRow(6);
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;
	initializeArrayInts(boo);
	printArray(boo);

	cout << "Now deleting rows: " << endl;
	boo.setRow(3);
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;
	printArray(boo);

	cout << "Now passing an invalid row length: " << endl;
	try
	{
		boo.setRow(-1);
	}
	catch (Exception &except)
	{
		cout << except << endl << endl;
	}

	cout << "Now adding columns (maintains data position in current rows/columns): " << endl;
	boo.setColumn(7);
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;
	printArray(boo);

	cout << "Now deleting columns (maintains data position in current rows/columns which are being kept): " << endl;
	boo.setColumn(5);
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;
	printArray(boo);

	cout << "Now passing invalid value for column: " << endl;
	try
	{
		boo.setColumn(-1);
	}
	catch (Exception &except)
	{
		cout << except << endl << endl;
	}
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;
	printArray(boo);

	cout << "Testing subscipt operator access on a const object: " << endl;
	const Array2D<int> const_boo(boo);
	printArray(const_boo);

}

void testStrings()
{
	cout << "Testing with complex data type: strings" << endl;
	cout << "First, we'll test the constructors:" << endl;

	cout << "Testing the default constructor, row and column should = 0)" << endl;
	Array2D<string> blob;
	cout << "Rows: " << blob.getRow() << " Columns: " << blob.getColumn() << endl << endl;

	cout << "Testing the constructor with both rows and columns defined at initialization: " << endl;
	Array2D<string> boo(3, 5);
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;

	cout << "Testing subscript operators with valid input: " << endl;
	initializeArrayStrings(boo);
	printArray(boo);

	cout << "Testing copy constructor: " << endl;
	Array2D<string> bo(boo);
	cout << "Rows: " << bo.getRow() << " Columns: " << bo.getColumn() << endl << endl;
	printArray(bo);

	cout << "Testing the assignment operator: " << endl;
	blob = bo;
	cout << "Rows: " << blob.getRow() << " Columns: " << blob.getColumn() << endl << endl;
	printArray(blob);

	cout << "Now testing mutator functions for both rows and columns: " << endl << endl;
	cout << "First with adding rows: " << endl;
	boo.setRow(6);
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;
	initializeArrayStrings(boo);
	printArray(boo);

	cout << "Now deleting rows: " << endl;
	boo.setRow(3);
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;
	printArray(boo);

	cout << "Now passing an invalid row length: " << endl;
	try
	{
		boo.setRow(-1);
	}
	catch (Exception &except)
	{
		cout << except << endl << endl;
	}

	cout << "Now adding columns (maintains data position in current columns): " << endl;
	boo.setColumn(7);
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;
	printArray(boo);

	cout << "Now deleting columns (creates a loss of data): " << endl;
	boo.setColumn(5);
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;
	printArray(boo);

	cout << "Now passing invalid value for column: " << endl;
	try
	{
		boo.setColumn(-1);
	}
	catch (Exception &except)
	{
		cout << except << endl << endl;
	}
	cout << "Rows: " << boo.getRow() << " Columns: " << boo.getColumn() << endl << endl;
	printArray(boo);

	cout << "Testing subscipt operator access on a const object: " << endl;
	const Array2D<string> const_boo(boo);
	printArray(const_boo);

}


template<typename T>
void printArray(Array2D<T> &boo)
{
	for (int i = 0; i < boo.getRow(); i++)
	{
		for (int j = 0; j < boo.getColumn(); j++)
		{
			cout << boo[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template<typename T>
void printArray(const Array2D<T> &boo)
{
	for (int i = 0; i < boo.getRow(); i++)
	{
		for (int j = 0; j < boo.getColumn(); j++)
		{
			cout << boo[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template<typename T>
void initializeArrayInts(Array2D<T> &boo)
{
	for (int i = 0; i < boo.getRow(); i++)
	{
		for (int j = 0; j < boo.getColumn(); j++)
		{
			boo[i][j] = i + j;
		}
	}
}

template<typename T>
void initializeArrayStrings(Array2D<T> &boo)
{
	for (int i = 0; i < boo.getRow(); i++)
	{
		for (int j = 0; j < boo.getColumn(); j++)
		{
			boo[i][j] = to_string(i + j);
		}
	}
}