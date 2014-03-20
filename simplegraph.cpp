/*
 * simplegraph.cpp
 *
 *  Created on: 26 Feb 2014
 *      Author: time
 */

#include "simplegraph.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
//#include <set>

using namespace std;

// Constructor
simplegraph::simplegraph(){
	}

	/*
	 * Adds a new vertex with no stubs.  
	 * Vertices are given an index starting from 0
	 * with the last vertex being index (N-1) if there
	 * are N vertices in total.
	 * Returns the index of new vertex (= number of vertices -1)
	 */
	int
	simplegraph::addVertex(){
	    //v2v.push_back(set<int>());
		//vector<int> blankvector;
		v2v.push_back(vector<int>() );
		return v2v.size()-1;
	}

	

	/**
	 * Adds a new edge from existing vertices s and t.
	 * No checks on vertex indices performed.
	 * No check for multiple edges of self-loops.
	 */
	void
	simplegraph::addEdge(int s, int t){
		v2v[s].push_back(t);
		v2v[t].push_back(s);
		// This version is for set based structure
		//		v2v[s].insert(t);
		//		v2v[t].insert(s);
	}

	
	/**
	 * Adds a new edge from existing vertices s and t.
	 * Checks on vertex indices and increases size if needed.
	 * Will not add self-loops.
	 * Multiple edges may be added depending on behaviour of addedge(s,t) method.
	 * Returns negative if self-loop attempted, or negative vertex index given, 0 if OK.
	 */
	int
	simplegraph::addEdgeSlowly(int s, int t){
		if (s==t) return -1;
		if ((s<0) || (t<0) ) return -2;
	    unsigned int maxSize=max(s,t)+1;
		if (v2v.size()<maxSize){
			v2v.resize(maxSize);
		}
		addEdge(s,t);
		return 0;
	}
	/**
	 * Fetches the n-th neighbour of vertices s
	 * Input
	 * s index of vertex whose neighbour is required
	 * n require n-th neighbour
	 * No checks on legality of inputs
	 * Returns
	 * index of neighbour
	 */
	int
	simplegraph::getNeighbour(int s, int n){
		return v2v[s][n]; // is notation correct?
	};

	/**
	 * Returns the total number of stubs.
	 * Stubs are one end of a vertex so this is double the number of edges.
	 * Note that this is currently slow as it sums the degrees.
	 * Would be better to maintain a running total updated when addedge is called.
	 */
	int
	simplegraph::getNumberStubs(){
		int stubs=0;
		for (int v=0; v<v2v.size(); v++) stubs+=getVertexDegree(v);
		return stubs;
	};

	/**
	 * Returns the total number of edges.
	 * Note that this is currently slow as it sums the degrees.
	 * Would be better to maintain a running total updated when addedge is called.
	 */
	int
	simplegraph::getNumberEdges(){
		return getNumberStubs()/2;
	};

	/**
	 * Returns number of vertices.
	*/
	int
	simplegraph::getNumberVertices(){
		return v2v.size();
	};

	/**
		 * Returns the degree of vertex s
		 * Input
		 * s index of vertex whose neighbour is required
		 * Returns
		 * degree of vertex
		 */
	int
	simplegraph::getVertexDegree(int s){
		return v2v[s].size();
	};

	/**
	* Returns a vector if integers with the degree distribution.
	* So if we call with
	* vector<int> dd=getDegreeDistribution()
	* then dd[k] is the number of vertices of degree[k]
	* and (dd.size()-1) is the largest degree in the network
	*/
	void
	simplegraph::getDegreeDistribution(vector<int>  & dd){
		//vector<int> dd;
		for (int v=0; v<getNumberVertices(); v++){	
			int k= getVertexDegree(v);
			if (dd.size()<=k){
				dd.resize(k+1); // vector must have size equal to maximum degree stored +1 as starts from k=0
			}
			dd[k]++;
		}
		//return dd;
	}

	/**
	 * Outputs a list of edges to file.
	 * No header line, tab separated file, one edge per line
	 * Input a string containing the name of the file (with any directories included)
	 */
	void
	simplegraph::write(char *outFile) {
	  ofstream fout(outFile);
	  if (!fout) {
	      cerr << "Can't open output file " << outFile << endl;
	      exit(1);
	  }
	  write(fout) ;
	  fout.close();
	}

	/**
	 * Output tab separated edge list of graph with no header line.
	 * Useful for some packages.
	 */
	void
	simplegraph::write(ostream & fout) {write(fout, false);}

	/**
	 * Output tab separated edge list of graph with optional header line.
	 * Needs ostream for output (e.g. cout) and true (false) if want header line
	 */
	void
	simplegraph::write(ostream & fout, bool labelOn) {
		if (labelOn) {
			fout << "v1 \t v2" << endl;
		}
		int source,target=-1;
		for (int source=0; source<getNumberVertices(); source++)
			for (int n=0; n<getVertexDegree(source); n++)
			{
				target = getNeighbour(source, n); 
				if (source<target) {
					fout << source << "\t" << target << endl;
				}
			}
	}
