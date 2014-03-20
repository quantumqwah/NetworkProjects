/*
 * simplegraph.h
 *
 *  Created on: 26 Feb 2014
 *  Last updated 13/3/13
 *      Author: time
 */

#ifndef SIMPLEGRAPH_H_
#define SIMPLEGRAPH_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
//#include <set>

using namespace std;


class simplegraph {

	 /* Most of these variables should be private
	  * but you would then need to create appropriate
	  * methods to access them and that seems a waste of time.
	  */
	 public:

// Using a set makes sense to avoid multiple edges but it does not allow for random access
//	/*
//	 * vertex2vertex[i] is a set of neighbouring vertices.
//	 * vertex2vertex[i]
//	 */
//    vector<set<int>> v2vset;

	/*
	 * v2v[i] is a vector giving a list of the vertices neighbouring vertex i
	 * NOTE that the space between the > > may be critical on some (unix like) systems
	 */
	vector<vector<int> > v2v;

	// constructor
	simplegraph();
	
	void write();
	void write(char *);
	void write(ostream &);
	void write(ostream &, bool);

	int getNumberStubs();
	int getNumberEdges();
	int getNumberVertices();
	int getVertexDegree(int);
	void getDegreeDistribution(vector<int> &);

	int addVertex();

	void addEdge(int , int);
	int addEdgeSlowly(int , int );

	int getNeighbour(int , int );

	private:


};



#endif /* SIMPLEGRAPH_H_ */
