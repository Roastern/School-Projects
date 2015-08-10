/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			Sorts.cpp
* Date Created:		4/20/2014
* Modifications:	
*
************************************************************/
#include "Sorts.h"

/**********************************************************************	
* Purpose: Initializes the c-array, vector and Array objects to be the
*			same size and store the same values
*
* Entry: out_stream will be the stream for the output, size is the 
*			defined size for all arrays
*
* Exit: Calls initiateArrays() to set all arrays to the same values 
*			and size
*
************************************************************************/
Sorts::Sorts(ostream & out_stream, int size) : out(out_stream), array_size(size), start(0), sort_time(0)
{
	srand(time(NULL));
	i_array_c = new int[array_size];
	i_array = new int[array_size];
	a_array_c.setLength(array_size);
	v_array_c.resize(array_size);

	for (int i = 0; i < array_size; i++)
	{
		i_array_c[i] = rand() % array_size;
		a_array_c[i] = i_array_c[i];
		v_array_c[i] = i_array_c[i];
	}

	initiateArrays();
}

/**********************************************************************	
* Purpose: Deletes all dynamically allocated arrays
*
* Entry: No values are entered
*
* Exit: No values are returned
*
************************************************************************/
Sorts::~Sorts()
{
	delete [] i_array;
	delete [] i_array_c;
	i_array = nullptr;
	i_array_c = nullptr;
}

/**********************************************************************	
* Purpose: Sets the arrays which are to be sorted to equal the 
*			unsorted arrays
*
* Entry: No values are entered
*
* Exit: No values are returned
*
************************************************************************/
void Sorts::initiateArrays()
{
	for (int i = 0; i < array_size; i++)
	{
		i_array[i] = i_array_c[i];
	}
	v_array = v_array_c;
	a_array = a_array_c;
}

/**********************************************************************	
* Purpose: Runs through all of the sorting algorithms on the arrays
*
* Entry: No values are entered
*
* Exit: No values are returned
*
************************************************************************/
void Sorts::runSorts()
{
	Bubble();
	FBubble();
	Select();
	Insert();
	Shell();
	Heap();
	Merg();
	Quick();
}

/**********************************************************************	
* Purpose: Stores the current time which is used to calculate the 
*			total running time for each sort
*
* Entry: No values are entered
*
* Exit: The current time is stored in start
*
************************************************************************/
void Sorts::startClock()
{
	start = clock();
}

/**********************************************************************	
* Purpose: Calculates the total running time of the sort
*
* Entry: No values are entered
*
* Exit: The total running time is stored in sort_time as a double
*
************************************************************************/
void Sorts::stopClock()
{
	sort_time = (clock() - start) /	double(CLOCKS_PER_SEC);
}

/**********************************************************************	
* Purpose: Runs the bubble sort on the c-array, vector and Array
*
* Entry: No values are entered
*
* Exit: Calls initiateArrays() to reset the sorted arrays back to their
*			original, unsorted state
*
************************************************************************/
void Sorts::Bubble()
{
	out << "Running BubbleSort"
		<< endl;
	out << "On C-Array, swap() defined as seperate function" << endl;

	startClock();
	BubbleSortS(i_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << i_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	initiateArrays();

	out << "On C-Array, swap done in sorting function" << endl;

	startClock();
	BubbleSort(i_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << i_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "Having the swap defined in a seperate function does" << endl
		<< " makes a big difference for bigger arrays." << endl << endl;

	out << "On Array<int>, swap done in sorting function" << endl;

	startClock();
	BubbleSort(a_array);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << a_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On vector, swap done in sorting function" << endl;

	startClock();
	BubbleSort(v_array);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << v_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	initiateArrays();
}

/**********************************************************************	
* Purpose: Runs the flagged bubble sort on the c-array, vector and Array
*
* Entry: No values are entered
*
* Exit: Calls initiateArrays() to reset the sorted arrays back to their
*			original, unsorted state
*
************************************************************************/
void Sorts::FBubble()
{
	out << "Running Flagged BubbleSort"
		<< endl;
	out << "On C-Array" << endl;

	startClock();
	FlagBubble(i_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << i_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On Array<int>" << endl;

	startClock();
	FlagBubble(a_array);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << a_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On vector" << endl;

	startClock();
	FlagBubble(v_array);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << v_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	initiateArrays();
}

/**********************************************************************	
* Purpose: Runs the selection sort on the c-array, vector and Array
*
* Entry: No values are entered
*
* Exit: Calls initiateArrays() to reset the sorted arrays back to their
*			original, unsorted state
*
************************************************************************/
void Sorts::Select()
{
	out << "Running Selection Sort"
		<< endl;
	out << "On C-Array" << endl;

	startClock();
	Selection(i_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << i_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On Array<int>" << endl;

	startClock();
	Selection(a_array);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << a_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On vector" << endl;

	startClock();
	Selection(v_array);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << v_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	initiateArrays();
}

/**********************************************************************	
* Purpose: Runs the insertion sort on the c-array, vector and Array
*
* Entry: No values are entered
*
* Exit: Calls initiateArrays() to reset the sorted arrays back to their
*			original, unsorted state
*
************************************************************************/
void Sorts::Insert()
{
	out << "Running Insertion Sort"
		<< endl;
	out << "On C-Array" << endl;

	startClock();
	InsertionSort(i_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << i_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On Array<int>" << endl;

	startClock();
	InsertionSort(a_array);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << a_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On vector" << endl;

	startClock();
	InsertionSort(v_array);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << v_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	initiateArrays();
}

/**********************************************************************	
* Purpose: Runs the shell sort on the c-array, vector and Array
*
* Entry: No values are entered
*
* Exit: Calls initiateArrays() to reset the sorted arrays back to their
*			original, unsorted state
*
************************************************************************/
void Sorts::Shell()
{
	out << "Running Shell Sort"
		<< endl;
	out << "On C-Array" << endl;

	startClock();
	ShellSort(i_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << i_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On Array<int>" << endl;

	startClock();
	ShellSort(a_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << a_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On vector" << endl;

	startClock();
	ShellSort(v_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << v_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	initiateArrays();
}

/**********************************************************************	
* Purpose: Runs the heap sort on the c-array, vector and Array
*
* Entry: No values are entered
*
* Exit: Calls initiateArrays() to reset the sorted arrays back to their
*			original, unsorted state
*
************************************************************************/
void Sorts::Heap()
{
	out << "Running Heap Sort"
		<< endl;
	out << "On C-Array" << endl;

	startClock();
	HeapSort(i_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << i_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On Array<int>" << endl;

	startClock();
	HeapSort(a_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << a_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On vector" << endl;

	startClock();
	HeapSort(v_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << v_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	initiateArrays();
}

/**********************************************************************	
* Purpose: Runs the merge sort on the c-array, vector and Array
*
* Entry: No values are entered
*
* Exit: Calls initiateArrays() to reset the sorted arrays back to their
*			original, unsorted state
*
************************************************************************/
void Sorts::Merg()
{
	out << "Running Merge Sort"
		<< endl;
	out << "On C-Array" << endl;

	startClock();
	MergeSort(i_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << i_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On Array<int>" << endl;

	startClock();
	MergeSort(a_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << a_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On vector" << endl;

	startClock();
	MergeSort(v_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << v_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	initiateArrays();
}

/**********************************************************************	
* Purpose: Runs the quick sort on the c-array, vector and Array
*
* Entry: No values are entered
*
* Exit: Calls initiateArrays() to reset the sorted arrays back to their
*			original, unsorted state
*
************************************************************************/
void Sorts::Quick()
{
	out << "Running Quick Sort"
		<< endl;
	out << "On C-Array" << endl;

	startClock();
	QuickSort(i_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << i_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On Array<int>" << endl;

	startClock();
	QuickSort(a_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << a_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	out << "On vector" << endl;

	startClock();
	QuickSort(v_array, array_size);
	stopClock();

	for (int i = 0; i < array_size; i = i + 1000)
	{
		out << i << ": " << v_array[i] << endl;
	}

	out << "SORT TIME: " << sort_time << endl << endl;

	initiateArrays();
}