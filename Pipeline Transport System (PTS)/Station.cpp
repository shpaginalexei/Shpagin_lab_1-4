#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int Station::max_id = 1;

Station::Station() {
    id = ++max_id;
}

int Station::get_id() const {
    return id;
}

int Station::get_workshop() const {
    return workshops;
}

int Station::get_workshop_in_work() const {
    return workshops_in_work;
}

void Station::start_workshop() {
    if (0 <= workshops_in_work < workshops) {
        workshops_in_work++;
    }
}

void Station::stop_workshop() {
    if (0 < workshops_in_work <= workshops) {
        workshops_in_work--;
    }
}

istream& operator>> (istream& in, Station& s) {
    cout << "\nname: ";
    getline(in, s.name);
    s.workshops = GetCorrectNumValue<int>("number workshops: ", 0, INT_MAX,
        "**The number must be positive, please repeat\n");
    s.workshops_in_work = GetCorrectNumValue<int>("workshops in work: ", -1, s.workshops,
        "**The number must be in the range 0.." + std::to_string(s.workshops) + ", please repeat\n");
    s.efficiency = GetCorrectNumValue<double>("efficiency (%): ", 0.0, 100.0,
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
    fin.ignore();
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
