#include "PTS.h"
#include <iostream>
#include <fstream>
//#include <set>
//#include <queue>


using namespace std;


bool check_pipe_by_name(const Pipe& p, const string substring) {
    return (p.get_name().find(substring) != string::npos);
}

bool check_pipe_by_status(const Pipe& p, const bool status) {
    return (p.get_status() == status);
}

bool check_pipe_by_diameter(const Pipe& p, const int diameter) {
    return (p.get_diameter() == diameter);
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
        if (pipes.contains(ID)) {
            pipes.erase(ID);
        }        
        if (edges.contains(ID)) {
            cout << "*Edge " << edges.at(ID) << " | pipe - " << ID << " was deleted\n";
            edges.erase(ID);
        }
        break; 
    }
    case STATION: { 
        if (stations.contains(ID)) {
            stations.erase(ID);
        }
        auto it = edges.cbegin();
        while (it != edges.cend()) {
            if (it->second.source == ID || it->second.sink == ID) {
                cout << "*Edge " << it->second << " | pipe - " << it->first << " was deleted\n";
                it = edges.erase(it);
            }
            else {
                ++it;
            }
        }
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

void PTS::add_edge(const int source, const int sink, const int diameter) {
    if (stations.contains(source) && stations.contains(sink)) {
        auto pipeIDs = search(check_pipe_by_diameter, diameter);
        pipeIDs = get_free_pipes(pipeIDs);
        if (!pipeIDs.empty()) {
            auto pipeID = pipeIDs.begin();
            edges.insert({ *pipeID, Edge(source, sink) });
        }
        else {
            cout << "\n*There are no free pipes with this diameter"
                 << "\nPlease, add new pipe with diameter equal to " << diameter << " mm" << endl;
            Pipe p;
            inputPipeWithoutDiameter(p, diameter);
            pipes.insert({ p.get_id(), p });
            edges.insert({ p.get_id(), Edge(source, sink)});         
        }
        changed = true;
    }
    else {
        cout << "\n**It's impossible to create an edge with such vertices\n";
    }
    
}

void PTS::view_edges() const {
    if (!edges.empty()) {
        for (const auto& [pipe_id, e] : edges) {
            cout << e << " | pipe - " << pipe_id << endl;
        }
    }
    else {
        cout << "*System has no Edges\n";
    }
}

void PTS::remove_edge(const int pipe_id) {
    if (edges.contains(pipe_id)) {
        edges.erase(pipe_id);
    }
}

Graph PTS::init_graph() const {
    return Graph(edges, pipes);
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
        for (auto& [pipe_id, e] :edges) {
            file << e << " " << pipe_id << endl;
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
        int count_edges; int pipe_id;

        file >> count_pipes >> count_stations >> count_edges;
        for (int i = 0; i < count_pipes; i++) {
            file >> new_pipe;
            pipes.insert({ new_pipe.get_id(), new_pipe });
        }
        for (int i = 0; i < count_stations; i++) {
            file >> new_station;
            stations.insert({ new_station.get_id(), new_station });
        }
        for (int i = 0; i < count_edges; i++) {
            file >> new_edge;
            file >> pipe_id;
            edges.insert({ pipe_id, new_edge });
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
