#pragma once
#include <fstream>


struct Edge
{
	int source;
    int sink;

	Edge();
	Edge(const int, const int);

	friend std::ostream& operator<< (std::ostream&, const Edge&);

	friend std::ifstream& operator>> (std::ifstream&, Edge&);
	friend std::ofstream& operator<< (std::ofstream&, const Edge&);
};
