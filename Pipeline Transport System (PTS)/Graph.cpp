#include "Graph.h"
#include "Pipe.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>

using namespace std;


Edge::Edge() : source(0), sink(0) {}

Edge::Edge(const int sourceID, const int sinkID) : source(sourceID), sink(sinkID) {}

ostream& operator<< (ostream& out, const Edge& e) {
	out << "source - " << e.source << " | sink - " << e.sink;
	return out;
}

ifstream& operator>> (ifstream& fin, Edge& e) {
	fin >> e.source >> e.sink;
	return fin;
}

ofstream& operator<< (ofstream& fout, const Edge& e) {
	fout << e.source << " " << e.sink;
	return fout;
}
