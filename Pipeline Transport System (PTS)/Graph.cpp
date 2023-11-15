#include "Graph.h"
#include "Pipe.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>

using namespace std;


Edge::Edge() : source_ID(0), sink_ID(0), pipe_ID(0) {}

Edge::Edge(const int sourceID, const int sinkID, const int pipeID) 
	: source_ID(sourceID), sink_ID(sinkID), pipe_ID(pipeID) {}

//istream& operator>> (istream& in, Edge& e) {
//	e.source_ID = GetCorrectNumber(in, 1, Station::get_max_id(), "source station id: ", "");
//	e.sink_ID = GetCorrectNumber(in, 1, Station::get_max_id(), "sink station id: ", "");
//	int diameter = GetCorrectNumber(in, 500, 1400, "diameter (500, 700, 1000 or 1400) (mm): ", "");
//	while (count(begin(Pipe::valid_diameters), end(Pipe::valid_diameters), diameter) <= 0) {
//		cout << "*Diameter must be 500, 700, 1000 or 1400, please repeat" << endl;
//		diameter = GetCorrectNumber(cin, 500, 1400, "diameter (500, 700, 1000 or 1400) (mm): ", "");
//	}
//	return in;
//}

ostream& operator<< (ostream& out, const Edge& e) {
	out << e.source_ID << " | " << e.sink_ID << " | " << e.pipe_ID << endl;
	return out;
}

ifstream& operator>> (ifstream& fin, Edge& e) {
	fin >> e.source_ID >> e.sink_ID >> e.pipe_ID;
	return fin;
}

ofstream& operator<< (ofstream& fout, const Edge& e) {
	fout << e.source_ID << " " << e.sink_ID << " " << e.pipe_ID << endl;
	return fout;
}
