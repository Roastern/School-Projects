#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include "Graph.h"
using std::cout;
using std::endl;
using std::cin;
using std::string;

void EdgeTestInt();
void EdgeTestString();

template<typename V, typename E>
void printEdge(const Edge<V, E> & pEdge);

void VertexTestInt();
void VertexTestString();

void GraphTest();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << "Testing Edge with basic data type: ints" << endl << endl;
	EdgeTestInt();
	cout << "Testing Edge with complex data type: strings" << endl << endl;
	EdgeTestString();

	cout << "Testing Vertex with basic data type: ints" << endl << endl;
	VertexTestInt();
	cout << "Testing Vertex with complex data type: strings" << endl << endl;
	VertexTestString();
	cout << "Testing the graph" << endl << endl;
	GraphTest();

	char c;
	cin >> c;

	return 0;
}

void EdgeTestInt()
{
	cout << "Testing Edge default constructor" << endl;
	Edge<string, int> aEdge;
	printEdge(aEdge);

	cout << "Testing constructor with ID input" << endl;
	Edge<string, int> bEdge(15);
	printEdge(bEdge);

	cout << "Testing constructor with Vertex and Weight input" << endl;
	Vertex<string, int> aVertex("A VERTEX");
	Edge<string, int> cEdge(aVertex, 10);
	printEdge(cEdge);

	cout << "Testing constructor with Vertex, weight, and ID input" << endl;
	Edge<string, int> dEdge(aVertex, 99, 103);
	printEdge(dEdge);

	cout << "Testing copy constructor" << endl;
	Edge<string, int> eEdge(dEdge);
	printEdge(eEdge);

	cout << "Testing assignment operator" << endl;
	aEdge = eEdge;
	printEdge(aEdge);

	cout << "Testing destructor" << endl;
	aEdge.~Edge();
	printEdge(aEdge);

	cout << "Testing all other class methods" << endl;
	aEdge.setWeight(15);
	aEdge.setID(99);
	aEdge.setDest(aVertex);
	printEdge(aEdge);
}

void EdgeTestString()
{
	cout << "Testing Edge default constructor" << endl;
	Edge<string, string> aEdge;
	printEdge(aEdge);

	cout << "Testing constructor with ID input" << endl;
	Edge<string, string> bEdge("hooters");
	printEdge(bEdge);

	cout << "Testing constructor with Vertex and Weight input" << endl;
	Vertex<string, string> aVertex("A VERTEX");
	Edge<string, string> cEdge(aVertex, 10);
	printEdge(cEdge);

	cout << "Testing constructor with Vertex, weight, and ID input" << endl;
	Edge<string, string> dEdge(aVertex, 99, "nope");
	printEdge(dEdge);

	cout << "Testing copy constructor" << endl;
	Edge<string, string> eEdge(dEdge);
	printEdge(eEdge);

	cout << "Testing assignment operator" << endl;
	aEdge = eEdge;
	printEdge(aEdge);

	cout << "Testing destructor" << endl;
	aEdge.~Edge();
	printEdge(aEdge);

	cout << "Testing all other class methods" << endl;
	aEdge.setWeight(15);
	cout << "Setting weight less than 0" << endl;
	try
	{
		aEdge.setWeight(-1);
	}
	catch (char * msg)
	{
		cout << msg << endl;
	}
	aEdge.setID("sup");
	aEdge.setDest(aVertex);
	printEdge(aEdge);
}

template<typename V, typename E>
void printEdge(const Edge<V, E> & pEdge)
{
	cout << "Printing all data stored in Edge" << endl;
	cout << "Weight: " << pEdge.getWeight() << endl;
	cout << "ID: " << pEdge.getID() << endl;
	if (pEdge.getDest() != nullptr)
		cout << "Destination: " << pEdge.getDest()->getData() << endl <<  endl;
	else
		cout << "No Destination" << endl << endl;
}

void VertexTestInt()
{
	cout << "Testing default constructor" << endl;
	Vertex<int, string> aVertex;
	
	cout << "Testing constructor with data input" << endl;
	Vertex<int, string> bVertex(99);

	list<Edge<int, string>> boo;
	Edge<int, string> newEdge("hello");
	Edge<int, string> anewEdge("allo");
	Edge<int, string> bnewEdge("ello");
	boo.push_back(newEdge);
	boo.push_back(anewEdge);
	boo.push_back(bnewEdge);

	cout << "Testing constructor with data and edge list input" << endl;
	Vertex<int, string> cVertex(15, boo);

	cout << "Testing copy constructor" << endl;
	Vertex<int, string> dVertex(cVertex);

	cout << "Testing assignment operator" << endl;
	aVertex = dVertex;

	cout << "Testing delete function" << endl;
	aVertex.delEdge("hello");

	cout << "Try to delete Edge that doesn't exist" << endl;
	try
	{
		aVertex.delEdge("hello");
	}
	catch (char * msg)
	{
		cout << msg << endl;
	}

	boo = aVertex.getEdges();

	cout << "Testing destructor" << endl;

	aVertex.setData(99);
	aVertex.addEdge(newEdge);
	aVertex.Process();
	cout << "Processed? " << aVertex.isProcessed() << endl;
	aVertex.Process();
	cout << "Processed? " << aVertex.isProcessed() << endl;
	aVertex.addEdge(newEdge);
	aVertex.addEdge(newEdge);

	cout << "aVertex data: " << aVertex.getData() << endl;
	cout << "Size of aVertex edge list: " << boo.size() << endl;
}

void VertexTestString()
{
	cout << "Testing default constructor" << endl;
	Vertex<string, string> aVertex;
	
	cout << "Testing constructor with data input" << endl;
	Vertex<string, string> bVertex("whahw");

	list<Edge<string, string>> boo;
	Edge<string, string> newEdge("hello");
	Edge<string, string> anewEdge("allo");
	Edge<string, string> bnewEdge("ello");
	boo.push_back(newEdge);
	boo.push_back(anewEdge);
	boo.push_back(bnewEdge);

	cout << "Testing constructor with data and edge list input" << endl;
	Vertex<string, string> cVertex("hoops", boo);

	cout << "Testing copy constructor" << endl;
	Vertex<string, string> dVertex(cVertex);

	cout << "Testing assignment operator" << endl;
	aVertex = dVertex;

	cout << "Testing delete function" << endl;
	aVertex.delEdge("hello");

	cout << "Try to delete Edge that doesn't exist" << endl;
	try
	{
		aVertex.delEdge("hello");
	}
	catch (char * msg)
	{
		cout << msg << endl;
	}

	boo = aVertex.getEdges();

	cout << "Testing destructor" << endl;

	aVertex.setData("noop");
	aVertex.addEdge(newEdge);
	aVertex.Process();
	cout << "Processed? " << aVertex.isProcessed() << endl;
	aVertex.Process();
	cout << "Processed? " << aVertex.isProcessed() << endl;
	aVertex.addEdge(newEdge);
	aVertex.addEdge(newEdge);

	cout << "aVertex data: " << aVertex.getData() << endl;
	cout << "Size of aVertex edge list: " << boo.size() << endl;
}

void GraphTest()
{
	cout << "Testing default constructor" << endl;
	Graph<string, string> aGraph;

	cout << "Testing constructor with Vertex input" << endl;
	Vertex<string, string> aVertex("aVertex");
	Graph<string, string> bGraph(aVertex);

	cout << "Testing copy constructor" << endl;
	Graph<string, string> cGraph(bGraph);

	cout << "Testing assignment operator" << endl;
	aGraph = cGraph;

	cout << "Testing Vertex insert" << endl;
	aGraph.InsertVertex("bVertex");
	aGraph.InsertVertex("cVertex");
	aGraph.InsertVertex("dVertex");

	cout << "Testing Vertex delete" << endl;
	aGraph.DeleteVertex("dVertex");
	cout << "Testing Vertex delete on Vertex which doesn't exist" << endl;
	try
	{
		aGraph.DeleteVertex("dVertex");
	}
	catch (char * msg)
	{
		cout << msg << endl;
	}

	cout << "Testing Arc insert" << endl;
	aGraph.InsertArc("aVertex", "bVertex", "path1");
	aGraph.InsertArc("bVertex", "cVertex", "path2", 99);
	aGraph.InsertArc("cVertex", "aVertex", "path3");

	cout << "Testing Breadth First Traversal" << endl;
	aGraph.BreadthFirst();

	cout << endl << endl << "Testing Depth First Traversal" << endl;
	aGraph.DepthFirst();

	cout << endl << "Testing Arc delete" << endl;
	aGraph.DeleteArc("aVertex", "bVertex", "path1");
	cout << "Deleting Arc that no longer exists" << endl;
	try
	{
		aGraph.DeleteArc("bVertex", "aVertex", "path1");
	}
	catch (char * msg)
	{
		cout << msg << endl;
	}

	aGraph.BreadthFirst();

	cout << "Testing getWeight()" << endl;
	cout << "Weight of 'path2' is: " << aGraph.getWeight("bVertex", "path2") << endl;

	cout << "Testing getPosition()" << endl;
	cout << "Position of 'cVertex' is: " << aGraph.getPosition("cVertex") << endl;

	cout << "Testing getVertex()" << endl;
	Vertex<string, string> & copyVertex = aGraph.getVertex(2);
	cout << "Retrieved vertex data = " << copyVertex.getData() << endl;
	copyVertex.Process();
	cout << "Is copyVertex processed? " << copyVertex.isProcessed() << endl;

	cout << "Number of vertices in aGraph: " << aGraph.getCount() << endl;
	cout << "Is aGraph empty? " << aGraph.isEmpty() << endl;
}
