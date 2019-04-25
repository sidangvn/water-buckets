/*Main function where reading the input from input.txt file and output to output.txt file*/

#include "bucket.hpp"
#include "bucketsFunction.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define SIZE 999999

using namespace std;

int main()
{
	/*Declaration*/
	int mostDiffAmount = 0; /*most difficult amount water*/
	int longestMove = 0; /*longest move*/
	int numBuckets;
	int numE = 0; /*number of edges*/
	int numVert = 1; /*number of vertices*/				
	int getBuckets;
								 
	vector<int> buckets; /*holding buckets*/
	vector<int> vertexNode;	/*holding vertices in the NODE*/									
	vector<vector<int> > vertices; 	/*Holding vertices*/			
	
	/*input and output file declaration*/
	ifstream inFile;
	ofstream outFile;
	
	inFile.open("input.txt");
	outFile.open("output.txt");
	
	/*checking valid input file*/	
	if(!inFile.is_open())		
	{
		cout << "Error openning file" << endl;
		return 0;
	}

	inFile >> numBuckets;	/*reading the first line in the input file = number of buckets*/

	/*put buckest into the buckets vector*/
	for(int i = 0; i < numBuckets; i++)
	{
		inFile >> getBuckets; 	
		buckets.push_back(getBuckets);			
	}
	
	/*finding size for the graph*/
	for(int i = 0; i < SIZE; i++)
	{
		graphVal[i] = SIZE;
    	}
	
	/*store values into vertexNode vector*/
	for(unsigned int i = 0; i < buckets.size(); i++)	
	{
		numVert *= (buckets[i] + 1);
		vertexNode.push_back(0);		
	}

	/*steps of finding number of vertices*/
	while(vertexNode[0] <= buckets[0])			
	{
		vertices.push_back(vertexNode);				
		int index = buckets.size() - 1;		

		while(vertexNode[index] >= buckets[index])	
		{
			vertexNode[index] = 0;						
			index--;					

			if(index < 0)									
			{
				break;
			}
		}
		
		if(index < 0)				
		{
			break;
		}
		
		vertexNode[index]++;	
	}

	/*graph struct declaration*/
	int size = vertices.size();
	GRAPH graph(size);
	graphVal[0] = 0;
	graphVertex[0] = 1;
	graph.listNode(vertices);
	graph.bucketsGraph(buckets);
	
	for(unsigned int i = 0; i < buckets.size(); i++) 
	{	
		int node = 1;							
		for(unsigned int j = i + 1; j < buckets.size(); j++)
		{
			node *= buckets[j] + 1;
	    	}

		bucketVal[i] = node;
	}

	/*store values into graph*/
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		vector<int> test = vertices[i];
		vector<vector<int> > ADJLIST = buildAdjList(test, numBuckets, buckets);		

		for(unsigned int j = 0; j < ADJLIST.size(); j++)
		{
			int address = 0;
			
			for(unsigned int k = 0; k < buckets.size(); k++)
			{
				address += ADJLIST[j][k] * bucketVal[k];
            		}
            
			graph.listEdge(i, ADJLIST[j], address);
			numE++;
		}
	}
	
	graph.bfs();						

	/*getting the max and min moves*/ 
	for(int i = 0; i < SIZE; i++) 
	{								
		if((graphVal[i] != SIZE) && (longestMove < graphVal[i]))
		{
			longestMove = graphVal[i];
			mostDiffAmount = i;
		}
	}

	int numV = vertices.size();

	/*Output the resul to the output.txt file*/
	outFile << numV;
	outFile << " ";
	outFile << numE;
	outFile << " ";
	outFile << mostDiffAmount;
	outFile << " ";
	outFile << longestMove << endl;

	/*Closing io file*/
    	inFile.close();
    	outFile.close();

	return 0;
}

