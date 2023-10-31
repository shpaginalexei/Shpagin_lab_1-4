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

double Station::get_unused_workshops() const {
    return (1.0 - (double)active_workshops / (double)workshops) * 100.0;
}

string Station::get_ratio_workshops() const {
    return to_string(active_workshops) + "/" + to_string(workshops) + " active workshops";
}

//void Station::start_workshop() {
//    if (0 <= active_workshops && active_workshops < workshops) {
//        active_workshops++;
//    }
//    else {
//        cout << "id::" << id << " **Failed to start the workshop, all workshops are running\n";
//    }
//}
//
//void Station::stop_workshop() {
//    if (0 < active_workshops && active_workshops <= workshops) {
//        active_workshops--;
//    }
//    else {
//        cout << "id::" << id << "**Failed to stop the workshop, all workshops are stopped\n";
//    }
//}

void Station::change_num_active_workshops(WhatDo whatDo) {
    switch (whatDo) {
    case WhatDo::START: {
        if (0 <= active_workshops && active_workshops < workshops) { active_workshops++; }
        return;
    }
    case WhatDo::STOP: {
        if (0 < active_workshops && active_workshops <= workshops) { active_workshops--; }
        return;
    }
    }
}

istream& operator>> (istream& in, Station& s) {
    cout << "name: ";
    in >> ws;
    getline(in, s.name);
    s.workshops = GetCorrectNumber(in, -1, INT_MAX,
        "workshops: ", "**The number must be positive, please repeat\n");
    s.active_workshops = GetCorrectNumber(in, -1, s.workshops + 1,
        "workshops in work: ", "**The number must be in the range 0.." + to_string(s.workshops) + ", please repeat\n");
    s.efficiency = GetCorrectNumber(in, 0.0, 100.0,
        "efficiency (%): ", "**The number must be in the range 0..100, please repeat\n");

    return in;
}

ostream& operator<< (ostream& out, const Station& s) {
    out << "\n\tStation id::" << s.id << endl
        << "name - " << s.name << endl
        << "workshops - " << s.workshops << endl
        << "workshops in work - " << s.active_workshops << endl
        << "efficiency - " << s.efficiency << "%" << endl;
    out << "\n";

    return out;
}

ifstream& operator>> (ifstream& fin, Station& s) {
    fin >> s.id;
    fin >> ws;
    getline(fin, s.name);
    fin >> s.workshops;
    fin >> s.active_workshops;
    fin >> s.efficiency;

    return fin;
}

ofstream& operator<< (ofstream& fout, const Station& s) {
    fout << s.id << endl
         << s.name << endl
         << s.workshops << endl
         << s.active_workshops << endl
         << s.efficiency << endl;

    return fout;
}
