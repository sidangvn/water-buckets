/*functions of moving water of buckets*/

#ifndef BUCKETS_FUNCTION_HPP
#define BUCKETS_FUNCTION_HPP

#include <iostream>
#include <vector>

using namespace std;

/*dump water of buckets*/
vector<vector<int> > dump(vector<int> vertex, int numBuckets)	
{
	vector<vector<int> > val;			

	for(int i = 0; i < numBuckets; i++)		
	{
		vector<int> newVertex(vertex.begin(), vertex.end()); 

		if(vertex[i] > 0)			
		{
			newVertex[i] = 0; 			
			val.push_back(newVertex); 		
		}
	}
	
	return val;							
}

/*fill in water*/
vector<vector<int> > fill(vector<int> vertex, int numBuckets, vector<int> buckets)
{
	vector<vector<int> > val;			

	for(int i = 0; i < numBuckets; i++)			
	{
		vector<int> newVertex(vertex.begin(), vertex.end()); 

		if(vertex[i] < buckets[i])		
		{
			newVertex[i] = buckets[i];		
			val.push_back(newVertex); 	
		}
	}
	
	return val;		 	
}

/*tranfer water between buckets*/
vector<vector<int> > transfer(vector<int> vertex, int numBuckets, vector<int> buckets)
{
	vector<vector<int> > val;		
	vector<int> temp(numBuckets);									

	for(int i = 0; i < numBuckets; i++)	
	{
		if(vertex[i] > 0)																
		{
			for(int j = 0; j < numBuckets; j++)							
			{
				if((j != i) && (buckets[j] > vertex[j]))  		
				{			
					if(vertex[i] + vertex[j] < buckets[j])
					{
						temp[j] = vertex[j] + vertex[i];		
						temp[i] = 0;			

						for(int k = 0; k < numBuckets; k++)
						{
							if(k != i && k != j)
							{
								temp[k] = vertex[k];
							}
						}
						
						val.push_back(temp);
					}
					else					
					{
						int node = vertex[j];						
						temp[j] = buckets[j]; 					
						temp[i] = vertex[i] - (buckets[j] - node); 	

						for(int k = 0; k < numBuckets; k++)
						{
							if(k != i && k != j)
							{
								temp[k] = vertex[k];
							} 
						}
						
						val.push_back(temp);
					}
				}	
			}
		}
	}

	return val;			
}

/*store values in each function in the vector and combine them all into just one vector*/
vector<vector<int> > buildAdjList(vector<int> vertex, int numBuckets, vector<int> buckets)
{
	vector<vector<int> > val = dump(vertex, numBuckets);				
	vector<vector<int> > val1 = transfer(vertex, numBuckets, buckets);	 
	vector<vector<int> > val2 = fill(vertex, numBuckets, buckets);

	val.insert(val.end(), val1.begin(), val1.end());
	val.insert(val.end(), val2.begin(), val2.end());

	return val;
}

#endif
