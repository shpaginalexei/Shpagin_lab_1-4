#include "Graph.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <queue>

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

int GetValueByIndex(set<int> S, int I) {
    auto it = S.begin();
    advance(it, I);
    return *it;
}

int GetIndexByValue(set<int> S, int K) {
    int Index = 0;
    for (auto u : S) {
        if (u == K) {
            return Index;
        }
        Index++;
    }
    return -1;
}

Graph::Graph(const unordered_map<int, Edge>& edges, const unordered_map<int, Pipe>& pipes) : edges(edges) {
    for (const auto& [pipe_id, e] : edges) {
        vertices.insert(e.source);
        vertices.insert(e.sink);
    }
    V = vertices.size();
    capacity.resize(V, vector<double>(V, 0.0));
    weight.resize(V, vector<double>(V, 0.0));
    adj.resize(V, vector<bool>(V, 0.0));
    for (auto& [pipe_id, e] : edges) {
        auto i = GetIndexByValue(vertices, e.source);
        auto j = GetIndexByValue(vertices, e.sink);
        capacity[i][j] = pipes.at(pipe_id).get_capasity();
        weight[i][j] = pipes.at(pipe_id).get_weight();
        adj[i][j] = true;
    }
}

bool Graph::hasCycle(int vertex, unordered_set<int>& visited, unordered_set<int>& recStack) const {
    visited.insert(vertex);
    recStack.insert(vertex);

    for (const auto& [pipe_id, edge] : edges) {
        if (edge.source == vertex) {
            if (recStack.find(edge.sink) != recStack.end()) {
                return true;
            }
            if (visited.find(edge.sink) == visited.end() && hasCycle(edge.sink, visited, recStack)) {
                return true;
            }
        }
    }

    recStack.erase(vertex);
    return false;
}

bool Graph::isDAG() const {
    unordered_set<int> visited;
    unordered_set<int> recStack;

    for (const auto& [pipe_id, edge] : edges) {
        int vertex = edge.source;
        if (visited.find(vertex) == visited.end() && hasCycle(vertex, visited, recStack)) {
            return false;
        }
    }

    return true;
}

void Graph::dfsTopologicalSort(int v, vector<bool>& visited, vector<int>& result) const {
    visited[v] = true;
    for (int u = 0; u < capacity[v].size(); u++) {
        if (adj[v][u] && !visited[u]) {
            dfsTopologicalSort(u, visited, result);
        }
    }

    result.push_back(GetValueByIndex(vertices, v));
}

vector<int> Graph::TopologicalSort() const {
    if (edges.empty()) {
        cout << "**Graph has no Edges. Topological sorting is not possible" << endl;
        return vector<int>();
    }
    else if (!isDAG()) {
        cout << "**The graph contains a cycle. Topological sorting is not possible" << endl;
        return vector<int>();
    }

    vector<bool> visited(V, false);
    vector<int> result;

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfsTopologicalSort(i, visited, result);
        }
    }
    reverse(result.begin(), result.end());

    return result;
}

bool Graph::bfsMaxFlow(vector<vector<double>>& capacity, int source, int sink, vector<int>& parent) const {
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && capacity[u][v] > 0) {

                if (v == sink) {
                    parent[v] = u;
                    return true;
                }

                parent[v] = u;
                visited[v] = true;
                q.push(v);

            }
        }
    }
    return false;
}

double Graph::MaxFlow(const int source, const int sink) const {
    if (edges.empty()) {
        cout << "**System has no Edges. Topological sorting is not possible" << endl;
        return -1;
    }

    if (!(vertices.contains(source) && vertices.contains(sink))) {
        cout << "\n**There are no vertices with such IDs\n";
        return -1;
    }
    int s = GetIndexByValue(vertices, source);
    int t = GetIndexByValue(vertices, sink);
    vector<vector<double>> cap = capacity;

    // Ford Fulkerson algorithm
    double maxFlow = 0.0;
    vector<int> parent(V, -1);

    while (bfsMaxFlow(cap, s, t, parent)) {
        double pathFlow = DBL_MAX;

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            cap[u][v] -= pathFlow;
            cap[v][u] += pathFlow;

        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}
