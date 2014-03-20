/*
 * test.cpp
 *
 * Tests simplegraph and illustrates how to do basic network operations.
 * Generates a basic ER G(N,p) type of random graph to show how to add vertices and edges.
 * Uses basic (rubiish) random number generator built into C++ but that 
 * might be good enough.
 *
 *  Created on: 28 Feb 2014
 *      Author: time
 */
#include "simplegraph.h"
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <iomanip>
#include <fstream> /* Needed for file output */
#include <string>
//#include <set>

using namespace std;


void PreferentialTreatment( simplegraph g,  double& Kexp, int& N, bool& debugon)
{

	for( int maxtime=100; maxtime <=1000000; maxtime*=10)
	{
	int m=3;
		   // start by defining an empty graph 
	    simplegraph g;
		ofstream degreedis("degree distribution for size n= " + to_string(maxtime)+ " .txt");
	//	int maxtime=10000;

    // find the necessary probability we are creating a G(N,p) type of random graph
	double p = Kexp/(N-1);
	double numberedges = N*Kexp/2.0; // always use floating point for constants including 1 and 0 unless want integer arithmetic 
	
	for (int v=0; v<N; v++)
	{	
		g.addVertex();
	}
	
	if (debugon)
	{
		cout << " adding edges " << endl;
	}
	
	vector<int> list(2,0);
	g.addEdge(0,1);
	list[0]=0;
	list[1]=1;


	for (int t=2;t<maxtime; t++)
	{
		g.addVertex();
		int previndex=0;
			
		for (int e=0; e< m; e++)
			{
				int index = rand() % (list.size());
					if(previndex==index)
					{
						index= rand()%(list.size());
					}
				int previndex=index;

			
				g.addEdgeSlowly(t,list[index]);
				list.push_back(t);
				list.push_back(list[index]);

				}
	}


	int maxindex=0;
for ( int index=0; index< g.getNumberVertices() ; index++)
{
	int currentindex=g.getVertexDegree(index);
	if(currentindex > maxindex)
	{
		maxindex=currentindex;
	}
}

int numberk=0;
for( int k=1; k < maxindex ; k++)
{

	for (int i=0; i < g.getNumberVertices(); i++)
	{
	   if( k ==g.getVertexDegree(i))
	   {
		   numberk++;
	   }

	   degreedis << k << '\t' << numberk << endl;
     }


}
	}
}
int main(int argc, char *argv[]) {

	cout << "Arguments are: N <k> (d) where arguments are separated by spaces and put after command name" << endl; 
	cout << "               N  = number of vertices" << endl; 
	cout << "              <k> = average degree" << endl; 
	cout << "               d  = if letter d is third argument then debugging options will be turned on" << endl; 
	cout << endl;

// *************************************************************
// User defined variables - default values then command line values are processed

    // Number of vertices for the initial network
	int N=2;

    // Average degree required
	double Kexp=3.0;

    // if true, then some extra debugging stuff is switched on.
    // First random numbers will always be the same every time you run it (fixed seed).
    // Also produces some output on screen, use only for small networks.
    bool debugon = true;

// End of user defined section
// *************************************************************

// First process command line

	for (int a=1; a<argc; a++){
		switch (a) {
		case 1: 
            N=atoi(argv[1]);
			break;
		case 2:
			Kexp=atoi(argv[2]);
			break;
		case 3: 
			debugon= (*argv[3] == 'd');
			break;
		default:
			cout << " Too many arguments" << endl;
		}
	}
	/* initialize random seed: */
	if (debugon){
		srand(0); // use the fixed seed for debugging
	}
	else{
		srand (time(NULL)); // Use the time version for real runs
	}
	

	simplegraph g;
PreferentialTreatment( g, Kexp , N , debugon);



	// Write out list of edges to file if you want
	// WARNING with file names and all strings in C++ \ has a special meaning.
	// so for directories on Windows use either \\ for a single backslash or forwards slash / may work
	//g.write("c:/DATA/CandN/edgelist.txt");
	//g.write("c:\\DATA\\CandN\\edgelist.txt");
    // Thie output files will appear in same directory as source code (this file) if you give no directories in filename

	}
	





