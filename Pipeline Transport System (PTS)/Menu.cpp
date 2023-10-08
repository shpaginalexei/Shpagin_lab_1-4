#include "Pipe.h"
#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>

using namespace std;


//vector<Pipe> pipes{};
//vector<Station> stations{};


void ViewText(const string menu[], const int size) {
    for (size_t i{}; i < size; i++) {
        cout << menu[i] << endl;
    }
    cout << '\n';
}

void BackToMenu() {
    cout << "\nPlease, press Enter to return to menu...";
    while (_getch() != 13) {
        continue;
    }
    system("cls");
}

void AddPipe(vector<Pipe>& pipes) {
    cout << "-> Add Pipe" << endl;
    Pipe p;    
    cin >> p;
    pipes.push_back(p);
    cout << '\n';
}

void AddStation(vector<Station>& stations) {
    cout << "-> Add Station" << endl;
    Station s;    
    cin >> s;    
    stations.push_back(s);
    cout << '\n';
}

void ViewPipes(vector<Pipe>& pipes) {
    cout << "-> View Objects" << endl
        << "     -> Pipes" << endl;

    if (pipes.size() == 0) {
        cout << "\n*The system hasn't pipes\n\n";
        return;
    }

    for (auto p : pipes) {
        cout << p;
    }
    cout << '\n';
}

void ViewStations(vector<Station>& stations) {
    cout << "-> View Objects" << endl
        << "     -> Stations" << endl;

    if (stations.size() == 0) {
        cout << "\n*The system hasn't stations\n\n";
        return;
    }

    for (auto s : stations) {
        cout << s;
    }
    cout << '\n';
}

void ViewAll(vector<Pipe>& pipes, vector<Station>& stations) {
    ViewPipes(pipes);
    ViewStations(stations);
}

void EditPipe(vector<Pipe>& pipes) {
    cout << "-> Edit Pipe" << endl;

    if (pipes.size() == 0) {
        cout << "\n*The system hasn't pipes\n\n";
        return;
    }

    cout << '\n';
    int x = -1;
    if (pipes.size() == 1) {
        cout << "*Only one Pipe in system\n" << endl;
        if (GetCorrectYesNoValue<double>("Do you want to edit this Pipe (Y/n)?: "))
            x = 0;
        else {
            cout << '\n';
            return;
        }
    }
    else
        x = GetCorrectNumValue<int>("What Pipe do you want to edit (1-" + std::to_string(pipes.size()) + ")?: ", 0, pipes.size(),
            "**The number must be in the range 1.." + std::to_string(pipes.size()) + ", please repeat\n") - 1;
    Pipe& p = pipes[x];

    cout << "\n\tPipe " << p.get_id() << endl
        << "..." << endl
        << "status - " << p.get_status() << endl;

    bool confirm = GetCorrectYesNoValue<double>("Are you sure to change this parameter (Y/n)?: ");
    if (confirm) {
        p.change_status();
    }

    cout << "\n\tPipe " << p.get_id() << endl
        << "..." << endl
        << "status - " << p.get_status() << endl;
}

void EditStation(vector<Station>& stations) {
    cout << "-> Edit Station" << endl;

    if (stations.size() == 0) {
        cout << "\n*The system hasn't stations\n\n";
        return;
    }

    cout << '\n';
    int x = -1;
    if (stations.size() == 1) {
        cout << "*Only one Station in system\n" << endl;
        if (GetCorrectYesNoValue<double>("Do you want to edit this Station (Y/n)?: "))
            x = 0;
        else {
            cout << '\n';
            return;
        }
    }
    else
        x = GetCorrectNumValue<int>("What Station do you want to edit (1-" + std::to_string(stations.size()) + ")?: ", 0, stations.size(),
            "**The number must be in the range 1.." + std::to_string(stations.size()) + ", please repeat\n") - 1;
    Station& s = stations[x];

    cout << "\n\tStation " << x + 1 << endl
        << "..." << endl
        << "workshops - " << s.get_workshop() << endl
        << "workshops in work - " << s.get_workshop_in_work() << '\n' << endl;

    bool confirm = GetCorrectYesNoValue<double>("Are you sure to change this parameter (Y/n)?: ");
    if (confirm) {
        if (0 < s.get_workshop_in_work() < s.get_workshop()) {
            int count = GetCorrectNumValue("Start (1) or stop (0) the workshop?: ", -1, 1,
                "**The number must be in the range 0..1, please repeat\n");
            count == 1 ? s.start_workshop() : s.stop_workshop();
        }
        else if (s.get_workshop_in_work() == 0) {
            if (GetCorrectYesNoValue<double>("Start one workshop (Y/n)?: "))
                s.start_workshop();
        }
        else if ((int)s.get_workshop_in_work() == (int)s.get_workshop()) {
            if (GetCorrectYesNoValue<double>("Stop one workshop (Y/n)?: "))
                s.stop_workshop();
        }
    }
    cout << "\n\tStation " << x + 1 << endl
        << "..." << endl
        << "workshops - " << s.get_workshop() << endl
        << "workshops in work - " << s.get_workshop_in_work() << '\n' << endl;
}

void SaveToFile(const string& file_name, vector<Pipe>& pipes, vector<Station>& stations) {
    cout << "-> Save" << endl;

    ofstream file;
    file.open(file_name, ios::out);
    if (file.is_open()) {
        int count_pipes = pipes.size();
        int count_stations = stations.size();

        file << count_pipes << " " << count_stations << endl;
        for (Pipe p : pipes) {
            file << p;
        }
        for (Station s : stations) {
            file << s;
        }
        cout << '\n' << count_pipes << " Pipes saved successfully!" << endl
                     << count_stations << " Stations saved successfully!\n" << endl;
    }
    file.close();
}

void LoadFromFile(const string& file_name, vector<Pipe>& pipes, vector<Station>& stations) {
    cout << "-> Load" << endl;
    pipes.clear();
    stations.clear();
    
    ifstream file;
    file.open(file_name, ios::in);
    if (file.is_open()) {
        Pipe new_pipe;
        Station new_station;
        Pipe::max_id = 0;
        Station::max_id = 0;
        int count_pipes = 0;
        int count_stations = 0;

        file >> count_pipes >> count_stations;
        for (int i = 0; i < count_pipes; i++) {
            file >> new_pipe;
            pipes.push_back(new_pipe);
            if (Pipe::max_id < new_pipe.get_id())
                Pipe::max_id = new_pipe.get_id();
        }
        for (int i = 0; i < count_stations; i++) {
            file >> new_station;
            stations.push_back(new_station);
            if (Station::max_id < new_station.get_id())
                Station::max_id = new_station.get_id();
        }

        cout << '\n' << count_pipes << '/' << pipes.size() << " Pipes loaded successfully!" << endl
            << count_stations << '/' << stations.size() << " Stations loaded successfully!\n" << endl;
    }
    file.close();
}
