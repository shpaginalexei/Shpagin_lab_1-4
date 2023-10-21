#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int Station::max_id = 0;

Station::Station() {
    id = ++max_id;
}

int Station::get_id() const {
    return id;
}

string Station::get_name() const {
    return name;
}

//int Station::get_workshops() const {
//    return workshops;
//}
//
//int Station::get_workshops_in_work() const {
//    return workshops_in_work;
//}

double Station::get_unused() const {
    return (1.0 - (double)workshops_in_work / (double)workshops) * 100.0;
}

string Station::get_ratio_workshops_in_work() const {
    return to_string(workshops_in_work) + "/" + to_string(workshops) + " workshops in work";
}

void Station::start_workshop() {
    if (0 <= workshops_in_work && workshops_in_work < workshops) {
        workshops_in_work++;
    }
    else {
        cout << "id::" << id << " **Failed to start the workshop, all workshops are running\n";
    }
}

void Station::stop_workshop() {
    if (0 < workshops_in_work && workshops_in_work <= workshops) {
        workshops_in_work--;
    }
    else {
        cout << "id::" << id << "**Failed to stop the workshop, all workshops are stopped\n";
    }
}

istream& operator>> (istream& in, Station& s) {
    cout << "\nname: ";
    getline(in, s.name);
    s.workshops = GetCorrectNumValue("number workshops: ", 0, INT_MAX,
        "**The number must be positive, please repeat\n");
    s.workshops_in_work = GetCorrectNumValue("workshops in work: ", -1, s.workshops,
        "**The number must be in the range 0.." + to_string(s.workshops) + ", please repeat\n");
    s.efficiency = GetCorrectNumValue("efficiency (%): ", 0.0, 100.0,
        "**The number must be in the range 0..100, please repeat\n");

    return in;
}

ostream& operator<< (ostream& out, const Station& s) {
    out << "\n\tStation id::" << s.id << endl
        << "name - " << s.name << endl
        << "workshops - " << s.workshops << endl
        << "workshops in work - " << s.workshops_in_work << endl
        << "efficiency - " << s.efficiency << "%" << endl;
    out << "\n";

    return out;
}

ifstream& operator>> (ifstream& fin, Station& s) {
    fin >> s.id;
    getline(fin, s.name);
    fin >> s.workshops;
    fin >> s.workshops_in_work;
    fin >> s.efficiency;

    return fin;
}

ofstream& operator<< (ofstream& fout, const Station& s) {
    fout << s.id << endl
        << s.name << endl
        << s.workshops << endl
        << s.workshops_in_work << endl
        << s.efficiency << endl;

    return fout;
}
