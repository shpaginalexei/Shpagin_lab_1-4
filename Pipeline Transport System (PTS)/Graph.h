#pragma once
#include "Pipe.h"
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>


struct Edge
{
public:
	int source;
    int sink;

	Edge();
	Edge(const int, const int);

	friend std::ostream& operator<< (std::ostream&, const Edge&);

	friend std::ifstream& operator>> (std::ifstream&, Edge&);
	friend std::ofstream& operator<< (std::ofstream&, const Edge&);
};

struct Graph
{
public:
	Graph(const std::unordered_map<int, Edge>&, const std::unordered_map<int, Pipe>&);

	std::vector<int> TopologicalSort() const;
	double MaxFlow(const int, const int) const;
	std::vector<int> ShortestPath(const int, const int) const;
	double ShortestPathLength(const std::vector<int>&) const;

private:

	size_t V;
	std::set<int> vertices;
	const std::unordered_map<int, Edge> edges;
	std::vector<std::vector<double>> weight;
	std::vector<std::vector<double>> capacity;
	std::vector<std::vector<bool>> adj;

	bool hasCycle(int, std::unordered_set<int>&, std::unordered_set<int>&) const;
	bool isDAG() const;
	void dfsTopologicalSort(int, std::vector<bool>&, std::vector<int>&) const;
	bool bfsMaxFlow(std::vector<std::vector<double>>&, int, int, std::vector<int>&) const;
};
