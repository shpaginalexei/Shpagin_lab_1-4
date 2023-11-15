#include "PTS.h"
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;


bool check_pipe_by_name(const Pipe& p, const string substring) {
    return (p.get_name().find(substring) != string::npos);
}

bool check_pipe_by_status(const Pipe& p, const bool status) {
    return (p.get_status() == status);
}

bool check_pipe_by_diameter(const Pipe& p, const int diameter) {
    return (count(begin(Pipe::valid_diameters), end(Pipe::valid_diameters), diameter) > 0) && (p.get_diameter() == diameter);
}

bool check_station_by_name(const Station& s, const string substring) {
    return (s.get_name().find(substring) != string::npos);
}

bool check_station_by_unactive_workshops(const Station& s, const double perc) {
    return (s.get_unused_workshops() >= perc);
}

string PTS::to_string(const PTS::ObjectType obj) const {
    switch (obj) {
    case PIPE:    { return "Pipe";    }
    case STATION: { return "Station"; }
    default:      { return "Unknown"; }
    }
}

void PTS::add(const ObjectType obj) {
    switch (obj) {
    case PIPE: {
        Pipe p;
        cin >> p;
        pipes.insert({ p.get_id(), p });
        break;
    }
    case STATION: {
        Station s;
        cin >> s;
        stations.insert({ s.get_id(), s });
        break;
    }
    default: {
        return;
    }
    }
    changed = true;
}

void PTS::remove(const ObjectType obj, const int ID) {
    switch (obj) {
    case PIPE: { 
        pipes.erase(ID); 
        break; 
    }
    case STATION: { 
        stations.erase(ID); 
        break; 
    }
    }
    changed = true;
}

void PTS::view(const ObjectType obj, const unordered_set<int>& IDs) const {
    switch (obj) {
    case PIPE: { 
        for (auto& id : IDs) { 
            cout << pipes.at(id);    
        } break; 
    }
    case STATION: { 
        for (auto& id : IDs) {
            cout << stations.at(id);
        } 
        break;
    }
    }
}

void PTS::short_view(const ObjectType obj, const unordered_set<int>& IDs) const {
    switch (obj) {
    case PIPE: {
        for (auto& id : IDs) {
            cout << "id::"           << id 
                 << " | name - "     << pipes.at(id).get_name()
                 << " | diameter - " << pipes.at(id).get_diameter() << " mm"
                 << " | status - "   << pipes.at(id).get_status_string() << endl;
        }
        break;
    }
    case STATION: {
        for (auto& id : IDs) {
            cout << "id::"       << id 
                 << " | name - " << stations.at(id).get_name() 
                 << " | "        << stations.at(id).get_ratio_workshops() << endl;
        }
        break;
    }
    }
}

void PTS::edit(const std::unordered_set<int>& IDs, const Pipe::EditStatusType type) {
    for (auto& id : IDs) {
        pipes.at(id).change_status(type);
    }
    changed = true;
}

void PTS::edit(const std::unordered_set<int>& IDs, const Station::EditWSType type) {
    for (auto& id : IDs) {
        stations.at(id).change_num_active_workshops(type);
    }
    changed = true;
}

unordered_set<int> PTS::get_ids_objects(const ObjectType obj) const {
    switch (obj) {
    case PIPE:    { return GetKeys(pipes);       }
    case STATION: { return GetKeys(stations);    }
    default:      { return unordered_set<int>{}; }
    }
}

unordered_set<int> PTS::get_free_pipes(const unordered_set<int>& IDs) const {
    unordered_set<int> free_IDs;
    for (auto& id : IDs) {
        if (!edges.contains(id)) {
            free_IDs.insert(id);
        }
    }
    return free_IDs;
}

void PTS::add_edge(const int sourceID, const int sinkID, const int pipe_diameter) {
    if (stations.contains(sourceID) && stations.contains(sinkID)) {
        auto pipeIDs = search(check_pipe_by_diameter, pipe_diameter);
        pipeIDs = get_free_pipes(pipeIDs);
        if (!pipeIDs.empty()) {
            auto pipeID = pipeIDs.begin();
            edges.insert({ *pipeID, Edge(sourceID, sinkID, *pipeID) });
        }
        else {
            cout << "\n*There are no free pipes with this diameter"
                 << "\nPlease, add new pipe with diameter equal to " << pipe_diameter << " mm" << endl;
            add(PIPE);
            add_edge(sourceID, sinkID, pipe_diameter);         
        }
    }
    changed = true;
}

bool PTS::hasCycle(int vertex, unordered_set<int>& visited, unordered_set<int>& recStack) const {
    visited.insert(vertex);
    recStack.insert(vertex);

    for (const auto& [pipe_id, edge] : edges) {
        if (edge.source_ID == vertex) {
            if (recStack.find(edge.sink_ID) != recStack.end()) {
                return true;
            }
            if (visited.find(edge.sink_ID) == visited.end() && hasCycle(edge.sink_ID, visited, recStack)) {
                return true;
            }
        }
    }

    recStack.erase(vertex);
    return false;
}

bool PTS::isDAG() const {
    unordered_set<int> visited;
    unordered_set<int> recStack;

    for (const auto& [pipe_id, edge] : edges) {
        int vertex = edge.source_ID;
        if (visited.find(vertex) == visited.end() && hasCycle(vertex, visited, recStack)) {
            return false;
        }
    }

    return true;
}

void PTS::dfsTopologicalSort(int v, vector<bool>& visited, vector<int>& result, vector<vector<int>>& adj) const {
    visited[v] = true;
    size_t V = stations.size();
    for (int u = 0; u < V; u++) {
        if (adj[v][u] == 1 && !visited[u])
            dfsTopologicalSort(u, visited, result, adj);
    }
    result.push_back(v + 1);
}

vector<int> PTS::TopologicalSort() const {
    if (!isDAG()) {
        cout << "\n**The graph contains a cycle. Topological sorting is not possible" << endl;
        return vector<int>();
    }

    vector<bool> visited;
    vector<int> result;
    size_t V = stations.size();

    vector<vector<int>> adj;
    adj.resize(V, vector<int>(V, 0));
    for (auto& [pipe_id, edge] : edges) {
        adj[edge.source_ID - 1][edge.sink_ID - 1] = 1;
    }

    visited.assign(V, false);
    result.clear();
    for (int i = 0; i < V; ++i) {
        if (!visited[i])
            dfsTopologicalSort(i, visited, result, adj);
    }
    reverse(result.begin(), result.end());

    return result;
}

void PTS::clear_system() {
    pipes.clear();
    stations.clear();
    edges.clear();
    Pipe::reset_max_id();
    Station::reset_max_id();
    changed = false;
}

bool PTS::empty() const {
    return pipes.size() == 0 && stations.size() == 0;
}

bool PTS::saved() const {
    return !changed;
}

bool PTS::has_saved_file() const {
    return file_name != "";
}

void PTS::set_save_directory(const std::string dir) {
    directory = dir;
}

void PTS::set_filename(const string fn) {
    file_name = fn;
}

void PTS::save_to_file() {
    ofstream file;
    file.open(directory + file_name, ios::out);
    if (file.is_open()) {
        size_t count_pipes = pipes.size();
        size_t count_stations = stations.size();
        size_t count_edges = edges.size();
        file << count_pipes << " " << count_stations << " " << count_edges << endl;
        for (auto& [id, p] : pipes) {
            file << p;
        }
        for (auto& [id, s] : stations) {
            file << s;
        }
        for (auto& [id, e] :edges) {
            file << e;
        }
        cout << file_name << ": " << count_pipes << " Pipes and "
             << count_stations << " Stations saved successfully!" << endl;
        changed = false;
    }
    else { 
        cout << "**No such file in directory\n";
        file_name = "";
    }
    file.close();   
}

void PTS::load_from_file() {
    clear_system();

    ifstream file;
    file.open(directory + file_name, ios::in);
    if (file.is_open()) {
        Pipe new_pipe;
        Station new_station;
        Edge new_edge;
        int count_pipes;
        int count_stations;
        int count_edges;

        file >> count_pipes >> count_stations >> count_edges;
        for (int i = 0; i < count_pipes; i++) {
            file >> new_pipe;
            pipes.insert({ new_pipe.get_id(), new_pipe });
        }
        for (int i = 0; i < count_stations; i++) {
            file >> new_station;
            stations.insert({ new_station.get_id(), new_station });
        }
        edges.reserve(count_edges);
        for (int i = 0; i < count_edges; i++) {
            file >> new_edge;
            edges.insert({ new_edge.pipe_ID, new_edge });
        }

        cout << file_name << ": " << count_pipes << " Pipes and "
             << count_stations << " Stations loaded successfully!" << endl;
        changed = false;
    }
    else { 
        cout << "**No such file in directory\n";
        file_name = "";
    }
    file.close();    
}
