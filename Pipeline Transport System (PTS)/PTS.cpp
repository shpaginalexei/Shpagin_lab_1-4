#include "PTS.h"
//#include "Pipe.h"
//#include "Station.h"
//#include "Utilities.h"
#include <iostream>
#include <fstream>
//#include <string>
//#include <set>
//#include <unordered_set>

using namespace std;


bool check_pipe_by_name(Pipe& p, string substring) {
    return (p.get_name().find(substring) != string::npos);
}

bool check_pipe_by_status(Pipe& p, bool status) {
    return (p.status == status);
}

bool check_station_by_name(Station& s, string substring) {
    return (s.get_name().find(substring) != string::npos);
}

bool check_station_by_unactive_workshops(Station& s, double perc) {
    return (s.get_unused_workshops() >= perc);
}

//unordered_set<int> App::get_pipes_by_filter() {
//    if (!pipes_is_empty()) {
//        unordered_set<int> IDs;
//        int search_choice = GetCorrectNumValue("Parameter (1 - by name, 2 - by status, 3 - all): ", 0, 3,
//                                               "**The number must be in the range 0..2, please repeat\n");
//        switch (search_choice) {
//        case 1: {
//            cout << "Name: ";
//            string str;
//            getline(cin, str);
//            unordered_set<int> unordered_IDs = SearchByFilter(pipes, check_by_name, str);
//            set<pair<string, int>> name_id_set;
//            for (auto& id : unordered_IDs) {
//                name_id_set.insert({ pipes.at(id).get_name(), id });
//            }
//            for (auto& [name, id] : name_id_set) {
//                IDs.insert(id);
//            }
//            break;
//        }
//        case 2: {
//            bool status = GetCorrectNumValue("Status (1 - work, 0 - in repair): ", -1, 1, 
//                                             "**The number must be 0 or 1, please repeat\n");
//            unordered_set<int> unordered_IDs = SearchByFilter(pipes, check_by_status, status);
//            set<pair<bool, int>> status_id_set;
//            for (auto& id : unordered_IDs) {
//                status_id_set.insert({ pipes.at(id).status, id});
//            }
//            for (auto& [status, id] : status_id_set) {
//                IDs.insert(id);
//            }
//            break;
//        }
//        case 3: {
//            for (auto& [id, p] : pipes) {
//                IDs.insert(id);
//            }
//            break;
//        }
//        default: {
//            return unordered_set<int>{};
//        }
//        }
//        return IDs;
//    }
//    else {
//        return unordered_set<int>{};
//    }
//}
//
//unordered_set<int> App::get_stations_by_filter() {
//    if (!stations_is_empty()) {
//        unordered_set<int> IDs;
//        int search_choice = GetCorrectNumValue("Parameter (1 - by name, 2 - by percentage of unworking workshops, 3 - all): ", 0, 3,
//                                               "**The number must be in the range 0..2, please repeat\n");
//        switch (search_choice) {
//        case 1: {
//            cout << "Name: ";
//            string str;
//            getline(cin, str);
//            unordered_set<int> unordered_IDs = SearchByFilter(stations, check_by_name, str);
//            set<pair<string, int>> name_id_set;
//            for (auto& id : unordered_IDs) {
//                name_id_set.insert({ stations.at(id).get_name(), id });
//            }
//            for (auto& [name, id] : name_id_set) {
//                IDs.insert(id);
//            }
//            break;
//        }
//        case 2: {
//            double perc = GetCorrectNumValue("Enter percentage of unworking workshops: ", 0, 100,
//                                                     "**The number must be in range 0..100, please repeat\n");
//            unordered_set<int> unordered_IDs = SearchByFilter(stations, check_by_unworking_workshops, perc);
//            set<pair<double, int>, greater<pair<double, int>>> perc_id_set;
//            for (auto& id : unordered_IDs) {
//                perc_id_set.insert({ stations.at(id).get_unused(), id });
//            }
//            for (auto& [perc, id] : perc_id_set) {
//                IDs.insert(id);
//            }
//            break;
//        }
//        case 3: {
//            for (auto& [id, s] : stations) {
//                IDs.insert(id);
//            }
//            break;
//        }
//        default: {
//            return unordered_set<int>{};
//        }
//        }
//        return IDs;
//    }
//    else {
//        return unordered_set<int>{};
//    }
//}

//void App::short_view_pipes() const {
//    if (!pipes_is_empty()) {
//        set<pair<bool, int>> status_id_set;
//        for (auto& [id, p] : pipes) {
//            status_id_set.insert({ p.status, id });
//        }
//        for (auto& [status, id] : status_id_set) {
//            cout << "id::" << id 
//                 << " | name - " << pipes.at(id).get_name() 
//                 << " | status - " << pipes.at(id).get_status() << endl;
//        }
//        cout << "\n";
//    }
//}
//
//void App::short_view_pipes(const unordered_set<int>& IDs) const {
//    if (!pipes_is_empty()) {
//        for (auto& id : IDs) {
//            cout << "id::" << id 
//                 << " | name - " << pipes.at(id).get_name() 
//                 << " | status - " << pipes.at(id).get_status() << endl;
//        }
//        cout << "\n";
//    }
//}
//
//void App::short_view_stations() const {
//    if (!stations_is_empty()) {
//        set<pair<double, int>, greater<pair<double, int>>> perc_id_set;
//        for (auto& [id, s] : stations) {
//            perc_id_set.insert({ s.get_unused(), id });
//        }
//        for (auto& [perc, id] : perc_id_set) {
//            cout << "id::" << id 
//                 << " | name - " << stations.at(id).get_name()
//                 << " | " << stations.at(id).get_ratio_workshops_in_work()
//                 << " (" << perc << "% unused)" << endl;
//        }
//        cout << "\n";
//    }
//}
//
//void App::short_view_stations(const unordered_set<int>& IDs) const {
//    if (!stations_is_empty()) {
//        for (auto& id : IDs) {
//            cout << "id::" << id
//                << " | name - " << stations.at(id).get_name()
//                << " | " << stations.at(id).get_ratio_workshops_in_work()
//                << " (" << stations.at(id).get_unused() << "% unused)" << endl;
//        }
//        cout << "\n";
//    }
//}

//void App::edit_one_pipe() {
//    if (!pipes_is_empty()) {
//        cout << "\nExisting Pipes:\n\n";
//        short_view_pipes();
//        int ID = GetCorrectID(pipes);
//        auto& p = pipes.at(ID);
//        cout << p;
//        bool agree = GetCorrectYesNoValue<bool>("Want to change the status of this pipe? (Y/n): ");
//        if (agree) {
//            p.change_status();
//            cout << p;
//        }
//        changed = true;
//    }
//}
//
//void App::edit_one_station() {
//    if (!stations_is_empty()) {
//        cout << "\nExisting Stations:\n\n";
//        short_view_stations();
//        int ID = GetCorrectID(stations);
//        auto& s = stations.at(ID);
//        cout << s;
//        int choice = GetCorrectNumValue("Want to start(1) or stop(0) the workshop?: ", -1, 1,
//                                        "**The number must be 0 or 1, please repeat\n");
//        switch (choice) {
//        case 0: {
//            s.stop_workshop();
//            break;
//        }
//        case 1: {
//            s.start_workshop();
//            break;
//        }
//        default: {
//            return;
//        }
//        }
//        cout << s;
//        changed = true;
//    }
//}

//void App::edit_mult_pipes() {
//    if (!pipes_is_empty()) {
//        auto IDs = get_pipes_by_filter();
//        if (IDs.empty()) {
//            cout << "\n*There are no such pipes\n";
//            return;
//        }
//        cout << "\nSelected Pipes:\n\n";
//        short_view_pipes(IDs);
//
//        int choice1 = GetCorrectNumValue("Do you want to edit all(1) or just some(0)?: ", -1, 1,
//                                         "**The number must be 0 or 1, please repeat\n");
//        unordered_set<int> selected_IDs;
//        if (choice1 == 1) selected_IDs = IDs;
//        else {
//            cout << "Select some IDs: ";
//            int id = -1;
//            while (cin.peek() != '\n') {
//                cin >> id;
//                if (pipes.contains(id)) {
//                    selected_IDs.insert(id);
//                }
//                else {
//                    cout << "id::" << id << " *No such id exists\n";
//                }
//            }
//            cout << "\n";
//            short_view_pipes(selected_IDs);
//        }
//
//        if (selected_IDs.empty()) return;
//
//        int choice2 = GetCorrectNumValue("Want to change all statuses to \"in work\"(1), to \"in repair\"(-1) or to reverse(0)?: ", -2, 1,
//                                         "**The number must be -1, 0 or 1, please repeat\n");
//        switch (choice2) {
//        case -1: {
//            for (auto& id : selected_IDs) {
//                pipes.at(id).status = false;
//            }
//            break;
//        }
//        case 0: {
//            for (auto& id : selected_IDs) {
//                pipes.at(id).change_status();
//            }
//            break;
//        }
//        case 1: {
//            for (auto& id : selected_IDs) {
//                pipes.at(id).status = true;
//            }
//            break;
//        }
//        default: {
//            break;
//        }
//        }
//        cout << "\n";
//        short_view_pipes(IDs);
//        changed = true;
//    }
//}
//
//void App::edit_mult_stations() {
//    if (!stations_is_empty()) {
//        auto IDs = get_stations_by_filter();
//        if (IDs.empty()) {
//            cout << "\n*There are no such stations\n";
//            return;
//        }
//        cout << "\nSelected Stations:\n\n";
//        short_view_stations(IDs);
//
//        int choice1 = GetCorrectNumValue("Do you want to edit all(1) or just some(0)?: ", -1, 1,
//                                         "**The number must be 0 or 1, please repeat\n");
//        unordered_set<int> selected_IDs;
//        if (choice1 == 1) selected_IDs = IDs;
//        else {
//            cout << "Select some IDs: ";
//            int id = -1;
//            while (cin.peek() != '\n') {
//                cin >> id;
//                if (stations.contains(id)) {
//                    selected_IDs.insert(id);
//                }
//                else {
//                    cout << "id::" << id << " **No such id exists\n";
//                }
//            }
//            cout << "\n";
//            short_view_stations(selected_IDs);
//        }
//
//        if (selected_IDs.empty()) return;
//
//        int choice2 = GetCorrectNumValue("Want to start(1) or stop(0) the workshop?: ", -1, 1,
//                                         "**The number must be -1, 0 or 1, please repeat\n");
//        switch (choice2) {
//        case 0: {
//            for (auto& id : IDs) {
//                stations.at(id).stop_workshop();
//            }
//            break;
//        }
//        case 1: {
//            for (auto& id : IDs) {
//                stations.at(id).start_workshop();
//            }
//            break;
//        }
//        default: {
//            return;
//        }
//        }
//        cout << "\n";
//        short_view_stations(IDs);
//        changed = true;
//    }
//}

//void App::remove_pipe() {
//    if (!pipes_is_empty()) {
//        cout << "\nExisting Pipes:\n\n";
//        short_view_pipes();
//        int ID = GetCorrectID(pipes);
//        cout << pipes.at(ID);
//        bool agree = GetCorrectYesNoValue<bool>("Want to remove this pipe? (Y/n): ");
//        if (agree) {
//            pipes.erase(ID);
//            cout << "\n*Pipe was deleted\n";
//        }
//        changed = true;
//    }
//}
//
//void App::remove_station() {
//    if (!stations_is_empty()) {
//        cout << "\nExisting Stations:\n\n";
//        short_view_stations();
//        int ID = GetCorrectID(stations);
//        cout << stations.at(ID);
//        bool agree = GetCorrectYesNoValue<bool>("Want to remove this station? (Y/n): ");
//        if (agree) {
//            stations.erase(ID);
//            cout << "\n*Station was deleted\n";
//        }
//        changed = true;
//    }
//}

//void App::edit_pipes() {
//    if (!pipes_is_empty()) {
//        cout << "\n";
//        int choice = GetCorrectNumValue("Parameter (1 - edit one pipe, 2 - batch editing, 0 - remove): ", -1, 2,
//            "**The number must be 0, 1 or 2, please repeat\n");
//        switch (choice) {
//        case 0: {
//            remove_pipes;
//            break;
//        }
//        case 1: {
//            edit_one_pipe;
//            break;
//        }
//        case 2: {
//            edit_mult_pipes;
//            break;
//        }
//        default: {
//            return;
//        }
//        }
//        changed = true;
//    }
//}
//
//void App::edit_stations() {
//    if (!stations_is_empty()) {
//        cout << "\n";
//        int choice = GetCorrectNumValue("Parameter (1 - edit one station, 2 - batch editing, 0 - remove): ", -1, 2,
//            "**The number must be 0, 1 or 2, please repeat\n");
//        switch (choice) {
//        case 0: {
//            remove_stations;
//            break;
//        }
//        case 1: {
//            edit_one_station;
//            break;
//        }
//        case 2: {
//            edit_mult_stations;
//            break;
//        }
//        default: {
//            return;
//        }
//        }
//        changed = true;
//    }
//}

//void App::search_pipes() {
//    if (!pipes_is_empty()) {
//        cout << "\n";
//        unordered_set<int> IDs = get_objs_by_filter(pipes);
//        if (!IDs.empty()) {
//            for (auto& id : IDs) {
//                cout << pipes.at(id);
//            }
//        }
//        else {
//            cout << "\n*There are no such pipes*\n";
//        }
//    }
//}
//
//void App::search_stations() {
//    if (!stations_is_empty()) {
//        cout << "\n";
//        unordered_set<int> IDs = get_objs_by_filter(stations);
//        if (!IDs.empty()) {
//            for (auto& id : IDs) {
//                cout << stations.at(id);
//            }
//        }
//        else {
//            cout << "\n*There are no such stations\n";
//        }
//    }
//}

string to_string(PTS::GroupType group) {
    switch (group) {
    case PTS::GroupType::PIPES:    { return "Pipe";    }
    case PTS::GroupType::STATIONS: { return "Station"; }
    }
    return "Unknown";
}

void PTS::add_to(const GroupType group) {
    switch (group) {
    case PIPES: {
        Pipe p;
        cin >> p;
        pipes.insert({ p.get_id(), p });
        break;
    }
    case STATIONS: {
        Station s;
        cin >> s;
        stations.insert({ s.get_id(), s });
        break;
    }
    }
    empty = false;
    changed = true;
}

void PTS::remove_from(const GroupType group, const int ID) {
    switch (group) {
    case PIPES:    { pipes.erase(ID); break; }
    case STATIONS: { stations.erase(ID); break; }
    }
    changed = true;
}

void PTS::view(const GroupType group, const unordered_set<int>& IDs) const {
    switch (group) {
    case PIPES:    { for (auto& id : IDs) { cout << pipes.at(id);    } break; }
    case STATIONS: { for (auto& id : IDs) { cout << stations.at(id); } break; }
    }
}

void PTS::short_view(const GroupType group, const unordered_set<int>& IDs) const {
    switch (group) {
    case PIPES: {
        for (auto& id : IDs) {
            cout << "id::" << id << " | name - " << pipes.at(id).get_name() << " | status - " << pipes.at(id).get_status() << endl;
        }
        break;
    }
    case STATIONS: {
        for (auto& id : IDs) {
            cout << "id::" << id << " | name - " << stations.at(id).get_name() << " | " << stations.at(id).get_ratio_workshops() << endl;
        }
        break;
    }
    }
}

unordered_set<int> PTS::get_group_ids(GroupType group) const {
    switch (group) {
    case PIPES:    return GetKeys(pipes);
    case STATIONS: return GetKeys(stations);
    }
    return unordered_set<int>{};
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
        cout << count_pipes << " Pipes and " 
             << count_stations << " Stations saved successfully!" << endl;
        saved = true;
        changed = false;
    }
    else { cout << "\n**No such file in directory\n"; }
    file.close();    
}

void PTS::load_from_file() {
    ifstream file;
    file.open(path + file_name, ios::in);
    if (file.is_open()) {
        pipes.clear();
        stations.clear();
        Pipe new_pipe;
        Station new_station;
        Pipe::max_id = 0;
        Station::max_id = 0;
        int count_pipes = 0;
        int count_stations = 0;

        file >> count_pipes >> count_stations;
        for (int i = 0; i < count_pipes; i++) {
            file >> new_pipe;
            pipes.insert({ new_pipe.get_id(), new_pipe });
            if (Pipe::max_id < new_pipe.get_id())
                Pipe::max_id = new_pipe.get_id();
        }
        for (int i = 0; i < count_stations; i++) {
            file >> new_station;
            stations.insert({ new_station.get_id(), new_station });
            if (Station::max_id < new_station.get_id())
                Station::max_id = new_station.get_id();
        }

        cout << count_pipes << " Pipes and "
             << count_stations << " Stations loaded successfully!" << endl;

        saved = true;
        changed = false;
    }
    else { cout << "\n**No such file in directory\n"; }
    file.close();    
}
