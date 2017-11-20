/* File: <main.cpp>
* Name: <William Fry>
* Revised: <3/16/2017>
* Course: CS340
*
* Desc: <program description>
*/
#include <string>
#include <iostream>
#include <fstream>
#include "Graph.hpp"
#include <ctype.h>
#include <limits>
using namespace std;

bool openFile(ifstream& fin, const char* fileName);
void loadFromFile(const char* fileName, const char delimiter, Graph<int>* myGraph);
int getNodeIdFromLine(string line);
void addEdgesAtCurrentVertex(string line,int currentVertexId ,Graph<int>* myGraph);
int getNeighborIdFromLine(string line,int& currentPositionInLine);
int getNeighorWeightFromLine(string line,int& currentPositionInLine);
int getSourceNode(Graph<int>* graph);
int getDestinationNode(int sourceNode,Graph<int>* graph);
int main() {
  const char* fileName = "graphin_Fig5.txt";
	Graph<int>* myGraph = new Graph<int>();
	loadFromFile(fileName, ':', myGraph);
  int sourceNode = getSourceNode(myGraph);
  int destinationNode = getDestinationNode(sourceNode,myGraph);

if(destinationNode > -1)
  {
  cout << "Checking the Graph for cycles . . " << endl;
    myGraph->DFS();

  if(myGraph->isGraphAcyclic())
  {
    cout << "Graph is Acyclic Performing DAG SP algorithm." << endl;
    myGraph->dagSP(sourceNode);
  }
  else
  {
    cout << "Graph has cycle(s). . ." << endl;
    cout << "Checking for Negative edge weights. . ." << endl;
    if(myGraph->hasNegativeEdgeWeights())
    {
      cout << "Negative Edge Weight(s) detected. . ." << endl;
      cout << "Bellman-Ford SP algorithm will be performed." << endl;
     if(myGraph->bellmanFord(sourceNode) == false)
     {
       cout << "Negative Edge Weight Cycle Detected. . . Exiting . . . " << endl;
       exit(0);
     }
     
    }else
    {
      cout << "Graph Has Only Positive EdgeWeights. . ." << endl;
      cout << "Dijkstra's SP algorithm will be performed." << endl;
      myGraph->dijkstraSP(sourceNode);
    
    }
   
  }
   myGraph->outputShortestPath(sourceNode,destinationNode);
   cout << "Shortest Path Distance To Chosen Destination: " << myGraph->getDistance(destinationNode) << endl;
  
   
   destinationNode = getDestinationNode(sourceNode,myGraph);

   while(destinationNode > 0)
   {
    myGraph->outputShortestPath(sourceNode,destinationNode);
    cout << "Shortest Path Distance To Chosen Destination: " << myGraph->getDistance(destinationNode) << endl;
    destinationNode = getDestinationNode(sourceNode,myGraph);
   }

 }

	delete myGraph;
	myGraph = nullptr;
	return 0;
}

bool openFile(ifstream & fin, const char* fileName)
{
	fin.open(fileName);
	return fin.is_open();
}

void loadFromFile(const char* fileName, const char delimiter, Graph<int>* myGraph)
{
	int currentVertexId = 0;
	int adjVertex = 0;
	string line;
	ifstream fin;
	int i = 0;
	if (!openFile(fin, fileName)) 
  {
		cerr << "Error: Unable to open file." << endl;
		exit(1);
	}

	while (getline(fin,line))
	{
		currentVertexId = getNodeIdFromLine(line);
		(*myGraph).addVertex(currentVertexId);
	}

	fin.clear();
	fin.seekg(0, fin.beg);
	while (getline(fin,line))
	{
		  //Add the Edges that are Adjacent to each previously Created Vertex
		  currentVertexId = getNodeIdFromLine(line); 
      addEdgesAtCurrentVertex(line,currentVertexId,myGraph); //Create the Edges that are adjacent to recently added Vertex.
  }
  
}

//Used when preforming DFS and Dijkstra/Prim's algorithm's to construct the vertexes.
int getNodeIdFromLine(string line)
{
	return stoi(line.substr(0));
}

//Function used when preforming dfs on directed unweighted graphs
//Returns a list of all the neighborids from the current line.

void addEdgesAtCurrentVertex(string line,int currentVertexId,Graph<int>* myGraph)
{
int i = 1;
int&  currentPositionInLine = i;
int neighborId;
int edgeWeight;
  while(i < line.size()-1)
  {
    neighborId = getNeighborIdFromLine(line,++currentPositionInLine);
    edgeWeight = getNeighorWeightFromLine(line,++currentPositionInLine);
   (*myGraph).addNeighbor(currentVertexId,edgeWeight,neighborId);
  }

}

int getNeighborIdFromLine(string line,int& currentPositionInLine)
{

  for(currentPositionInLine; currentPositionInLine < line.size(); ++currentPositionInLine)
  {
    if(isdigit(line.at(currentPositionInLine)))
    {
      return stoi(line.substr(currentPositionInLine));
    }
    
  }

}

int getNeighorWeightFromLine(string line,int& currentPositionInLine)
{
  for(currentPositionInLine; currentPositionInLine < line.size(); ++currentPositionInLine)
  {
      if(isdigit(line.at(currentPositionInLine)))
      {
        return stoi(line.substr(currentPositionInLine));
      }
      else if(line.at(currentPositionInLine) == '-')
      {
        ++currentPositionInLine;
        return stoi(line.substr(currentPositionInLine)) - (2 * stoi(line.substr(currentPositionInLine)));
      }
  }
}
int getSourceNode(Graph<int>* graph)
{
int sourceNode;
cout << "Input sourceNode 1-" << graph->getGraphSize() <<": ";
cin >> sourceNode;

while(cin.fail() || sourceNode > graph->getGraphSize() || sourceNode < 1)
{
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Invalid Selection Please Choose a valid selection." << endl;

cout << "Input sourceNode 1-" << graph->getGraphSize() <<": ";
cin >> sourceNode;
}
return sourceNode;
}
int getDestinationNode(int sourceNode,Graph<int>* graph)
{
int destinationNode;
cout << "Enter -1 to Exit" << endl;
cout << "Input DestinationNode 1-" << graph->getGraphSize() <<": ";

cin >> destinationNode;

while(cin.fail() || destinationNode == sourceNode || destinationNode > graph->getGraphSize())
{
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Invalid Selection Please Choose a valid selection." << endl;
cout << "Enter -1 to Exit" << endl;
cout << "Input destinationNode 1-" << graph->getGraphSize() <<": ";
cin >> destinationNode;
}
return destinationNode;
}
