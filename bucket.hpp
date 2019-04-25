/*Header file where node list, adjacency list and graph stored*/

#ifndef BUCKET_HPP
#define BUCKET_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define SIZE 999999

using namespace std;

int graphVal[SIZE];
int bucketVal[SIZE];
int graphVertex[SIZE];

/*node list*/
struct NODE
{
	int address, travel;
	vector<int> vertexNode;
	struct NODE* next;
};

/*adjacency list*/
struct ADJLIST
{
	struct NODE* head;
};

/*build the graph*/
class GRAPH
{
	private:
		int sumVertex;
		struct ADJLIST* adjHolder; 
		vector<int> bucketHolder;
		
	public:
		GRAPH(int sumVertex)
		{
			this -> sumVertex = sumVertex;
			adjHolder = new ADJLIST[sumVertex];

			for(int i = 0; i < sumVertex; i++)
			{
				adjHolder[i].head = NULL;
			}
		}
		
		NODE* newNode(vector<int> vertex)
		{
			NODE* node = new NODE;
			node -> vertexNode = vertex;
			node -> next = NULL;

			return node;
		}
		
		void bucketsGraph(vector<int> getBuckets) 
		{
			this -> bucketHolder = getBuckets;
		}
		
		void listNode(vector<vector<int> > myVertices)
		{
			for(unsigned int i = 0; i < myVertices.size(); i++)
			{
				adjHolder[i].head = newNode(myVertices[i]); 
			}
		}
		
		void listEdge(int source, vector<int> stop, int address)	
		{
			NODE* temp = newNode(stop); 
			temp -> address = address;
			
			NODE* temp1 = adjHolder[source].head;
			NODE* temp2 = temp1 -> next;
						
			temp1 -> next = temp;
			temp1 -> next -> next = temp2;
		}
		
		void buildGraph()
		{								
			NODE* newNode;
			for(int i = 0; i < sumVertex; i++)
			{
				newNode = adjHolder[i].head;
				newNode = newNode -> next;
				
				while(newNode) 
				{
					newNode = newNode -> next;
				}
			}
		}
		
		int sumNode(NODE *NODE) 
		{							
			int sum = 0;
			int count = NODE -> vertexNode.size();

			for(int i = 0; i < count; i++)
			{
				sum += NODE -> vertexNode[i];
        		}

			return sum;
		}
	
		/*doing BFS*/ 
		void bfs() 
		{							
			int sum;
			int address;
			int travel;
		
			NODE *newNode;
			queue<int> storage;
			storage.push(0);
													
			adjHolder[0].head -> travel = 0;							

			while(!storage.empty()) 
			{
				address = storage.front();						
				storage.pop();										

				newNode = adjHolder[address].head -> next;				
				travel = adjHolder[address].head -> travel;
								
				while(newNode) 
				{									
					if(graphVertex[newNode -> address] == 0) 
					{	
						sum = sumNode(newNode);			
						storage.push(newNode -> address);
										
						graphVertex[newNode -> address] = 1;		
						newNode -> travel = adjHolder[newNode -> address].head -> travel = travel + 1;

						if(graphVal[sum] > (newNode -> travel))
						{
							graphVal[sum] = newNode -> travel;
						}
					}
				
					newNode = newNode -> next;
				}
			}
		}	
};

#endif
