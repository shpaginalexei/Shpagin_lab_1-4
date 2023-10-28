#include "PTS.h"
#include <iostream>
#include <fstream>

using namespace std;


bool check_pipe_by_name(const Pipe& p, const string substring) {
    return (p.get_name().find(substring) != string::npos);
}

bool check_pipe_by_status(const Pipe& p, const bool status) {
    return (p.get_status() == status);
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
    default:      { return ""; }
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
            cout << "id::"         << id 
                 << " | name - "   << pipes.at(id).get_name() 
                 << " | status - " << pipes.at(id).get_status_string() << endl;
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
    default :     { return unordered_set<int>{}; }
    }
}

void PTS::clear_system() {
    pipes.clear();
    stations.clear();
    Pipe::max_id = 0;
    Station::max_id = 0;
    changed = false;
    //file_name = "";
}

void PTS::save_to_file() {
    ofstream file;
    file.open(path + file_name, ios::out);
    if (file.is_open()) {
        size_t count_pipes = pipes.size();
        size_t count_stations = stations.size();
        file << count_pipes << " " << count_stations << endl;
        for (auto& [id, p] : pipes) {
            file << p;
        }
        for (auto& [id, s] : stations) {
            file << s;
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
    file.open(path + file_name, ios::in);
    if (file.is_open()) {
        Pipe new_pipe;
        Station new_station;
        int count_pipes = 0;
        int count_stations = 0;

        file >> count_pipes >> count_stations;
        for (int i = 0; i < count_pipes; i++) {
            file >> new_pipe;
            pipes.insert({ new_pipe.get_id(), new_pipe });
        }
        for (int i = 0; i < count_stations; i++) {
            file >> new_station;
            stations.insert({ new_station.get_id(), new_station });
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
