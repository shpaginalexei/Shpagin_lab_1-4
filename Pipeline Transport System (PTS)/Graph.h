#pragma once
#include <fstream>


struct Edge
{
	int source_ID;
    int sink_ID;
	int pipe_ID;

	Edge();
	Edge(const int, const int, const int);

	friend std::ostream& operator<< (std::ostream&, const Edge&);

	friend std::ifstream& operator>> (std::ifstream&, Edge&);
	friend std::ofstream& operator<< (std::ofstream&, const Edge&);
};
