#pragma once
#ifndef Graph_hpp
#define Graph_hpp

#include <list>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <limits.h>
#include <set>
using namespace std;
template <typename E>
class Graph
{
private:
  int nodeId;
  int time;
  bool acyclic;
  int edgeCount;
  int vertexCount;
class Node;
class Edge;
  class Node{
	public:
		E vertexData;
		char color;
		int discoveryTime;
		int finishTime;
		vector<Edge*> neighbors;
		Node* parent;
    int distance;
		Node(const E& vertexData, int discoveryTime, int finishTime)
			:vertexData(vertexData), discoveryTime(discoveryTime), finishTime(finishTime)
		{
			color = 'w';
		}
		void addNeighbor(Edge* edge)
		{
			neighbors.push_back(edge);
		}	
	};//end Node

  class Edge
  {
    public:
     friend class Node;
     int weight;
     Node* source;
     Node* destination;
     Edge(int weight,Node* source,Node* destination)
       : weight(weight), source(source),destination(destination)  
     {

     }
   };//End Edge

  
	Node* createNode(const E& vertex, int discoveryTime, int finishTime)
	{
		return new Node(vertex,discoveryTime,finishTime);
	}

 Edge* createEdge(int weight,Node* source,Node* destination)
     {
       return new Edge(weight, source,destination);
     }
  void releaseGraph()
  {
    graph.clear();
    for(int i = 0; i < edges.size();i++)
    {
      delete edges[i];
      edges[i] = nullptr;
    }
  }

  void relax(Node* node1, Node* node2,int weight)
  {

   

     if(node1->distance != INT_MAX && node2->distance > node1->distance + weight)
     {
       node2->distance = node1->distance + weight;
       node2->parent = node1;
     }

   
  }

  void initSingleSource(int source)
  {
   	for (typename std::map<E, Node*>::iterator it = graph.begin(); it != graph.end(); it++)
  {
            it->second->distance = INT_MAX;
            it->second->parent = nil;
  
  }
   graph[source]->distance = 0;

  }

void buildHeap(vector<Node*>& vertexHeap, int count)
{

	for (int i = count / 2; i >= 0; i--) 
	{
		minHeapify(vertexHeap, i, count);
	}
}

void minHeapify(vector<Node*>& vertexHeap, int rootIndex, int n)
{

	int min;
  int left  = 2 * rootIndex;
  int right = 2 * rootIndex + 1;
	Node* temp;
  

if(left < vertexHeap.size() && (vertexHeap[left]->distance) < (vertexHeap[rootIndex]->distance))
{
  min = left;
}
else
{
  min = rootIndex;
}
if(right < vertexHeap.size() && (vertexHeap[right]->distance) < (vertexHeap[min]->distance))
{
  min = right;
}

if(min != rootIndex)
{
  temp = vertexHeap[rootIndex];
	vertexHeap[rootIndex] = vertexHeap[min];
	vertexHeap[min] = temp;
  minHeapify(vertexHeap,min,n);
}

}
Node* extractMin(vector<Node*>& vertex)
{
  Node* temp;
  Node* min = vertex[0];
  temp = vertex[0];
  vertex[0] = vertex[vertex.size()-1];
  vertex[vertex.size()-1] = temp;
  vertex.pop_back();
  return min;
}

protected:
		stack<Node*>topoGraphStack;		
    map<E,Node*> graph;
    vector<Edge*> edges;
		queue<Node*>backEdgeQueue;
    Node* nil;
public:
	Graph()
	{
    nil = createNode(0,0,0);
    edgeCount = 0;
		nodeId = 1;
		acyclic = true;
    vertexCount = 0;
	}

	~Graph() 
  {
    delete nil;
    nil = nullptr;
    releaseGraph();
  }
	void addVertex(E vertex)
	{
		Node* node = createNode(vertex,0, 0);
		graph[nodeId++] = node;
    vertexCount++;

	}
	void addNeighbor(int nodeId,int weight,int neighborNodeId)
  {
     Edge* edge = createEdge(weight,graph[nodeId],graph[neighborNodeId]);
   	 graph[nodeId]->addNeighbor(edge);
     edges.push_back(edge);
     edgeCount++;
	}

	bool isGraphAcyclic() {
		return acyclic;
	}
	
 void displayEdgesAndWeights()
 {
  //created to show the validity of my graph after i had it constructed

   for(int i = 0; i < edges.size();i++)
   {
     cout << "An Edge exists from " << edges[i]->source->vertexData << " to " << edges[i]->destination->vertexData << " With " << edges[i]->weight << " Weight" << endl; 
   }
 }

void DFS() 
{
		time = 0;
		for (typename std::map<E, Node*>::iterator it = graph.begin(); it != graph.end(); it++) {
			if (it->second->color == 'w')
			{
				DFSVisit(it->second);
			}
		}
}
void DFSVisit(Node* vertex)
{
		time++;
		vertex->discoveryTime = time;
		vertex->color = 'g';
		for (int i = 0; i < vertex->neighbors.size(); i++)
		{
			if (vertex->neighbors[i]->destination->color == 'w')
			{
				DFSVisit(vertex->neighbors[i]->destination);
			}
			else {
				if (vertex->neighbors[i]->destination->color == 'g')
				{

				   acyclic = false;
           backEdgeQueue.push(vertex);
           backEdgeQueue.push(vertex->neighbors[i]->destination);
				}
			}
		}
		vertex->color = 'b';
		time++;
		vertex->finishTime = time;
		topoGraphStack.push(vertex);
}

int getGraphSize()
{
return graph.size();
}

bool hasNegativeEdgeWeights()
{
	for (typename std::map<E, Node*>::iterator it = graph.begin(); it != graph.end(); it++)
  {
	  for (int i = 0; i < it->second->neighbors.size(); i++)
		{
        if(it->second->neighbors[i]->weight < 0)
        {
          return true;
        }
		}



  }

  return false;
}
bool bellmanFord(int source)
{
  initSingleSource(source);

for (int i = 0; i < vertexCount-1;i++)
  {
    for(int j = 0; j < edgeCount;j++)
    {
        relax(edges[j]->source,edges[j]->destination,edges[j]->weight);
    }
  }
  for(int j = 0; j < edgeCount;j++)
   {
        if(edges[j]->source->distance != INT_MAX && (edges[j]->destination->distance > edges[j]->source->distance + edges[j]->weight))
        {
           return false;   
        }
   }
return true;
}

int getDistance(int dest)
{

return graph[dest]->distance;

}
void outputShortestPath(int source,int destination)
{
  Node* temp = graph[destination];
  if(graph[destination]->distance != INT_MAX)
  {
    cout << "Shortest Path: ";
    while(temp != graph[source])
    {
    cout << temp->vertexData << " <- ";
    temp = temp->parent;
    }
  cout << temp->vertexData << endl;
  }else
  {
    cout << "Shortest Path to chosen Destination does not exist Please Choose another destination." << endl;
  }
}

void dagSP(int sourceNode)
{
initSingleSource(sourceNode);
while(!topoGraphStack.empty())
{
  
for(int i = 0;i < topoGraphStack.top()->neighbors.size();i++)
{
   relax(topoGraphStack.top(),topoGraphStack.top()->neighbors[i]->destination,topoGraphStack.top()->neighbors[i]->weight); 
}

topoGraphStack.pop();

}

}
void dijkstraSP(int sourceNode)
{
vector<Node*> nodeSet;
vector<Node*> nodeQue;
Node* temp;
initSingleSource(sourceNode);

for (typename std::map<E, Node*>::iterator it = graph.begin(); it != graph.end(); it++)
{
    nodeQue.push_back(it->second);

}

buildHeap(nodeQue,nodeQue.size());

while(!nodeQue.empty())
{
temp = extractMin(nodeQue);
nodeSet.push_back(temp);
    for(int i = 0; i < temp->neighbors.size();i++)
    {
          relax(temp,temp->neighbors[i]->destination,temp->neighbors[i]->weight);
    }
    
	minHeapify(nodeQue,0,nodeQue.size()-1);
}
  
}


};//END GRAPH
#endif
