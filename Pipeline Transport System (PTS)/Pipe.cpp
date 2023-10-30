#include "Pipe.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;


int Pipe::max_id = 0;

void Pipe::reset_max_id() {
    max_id = 0;
}

Pipe::Pipe() {
    id = ++max_id;
}

int Pipe::get_id() const {
    return id;
}

string Pipe::get_name() const {
    return name;
}

bool Pipe::get_status() const {
    return status;
}

string Pipe::get_status_string() const {
    return status ? "work" : "in repair";
}

void Pipe::change_status(const EditStatusType type) {
    switch (type) {
    case SET_WORK:      { status = true;    return; }
    case SET_IN_REPAIR: { status = false;   return; }
    case SET_OPPOSITE:  { status = !status; return; }
    default:            {                   return; }
    }
}

istream& operator>> (istream& in, Pipe& p) {
    cout << "name: ";
    in >> ws;
    getline(in, p.name);
    p.lenght = GetCorrectNumber(in, 0.000001, DBL_MAX,
        "lenght (km): ", "**The number must be positive, please repeat\n");
    p.diameter = GetCorrectNumber(in, 1, INT_MAX,
        "diameter (mm): ", "**The number must be positive, please repeat\n");
    p.status = GetCorrectNumber(in, 0, 2,
        "status (1 - work, 0 - in repair): ", "**The enter must be 0 or 1, please repeat\n");   
    return in;
}

ostream& operator<< (ostream& out, const Pipe& p) {
    out << "\n\tPipe id::" << p.id << endl
        << "name - "       << p.name << endl
        << "lenght - "     << p.lenght << " km" << endl
        << "diameter - "   << p.diameter << " mm" << endl
        << "status - "     << p.get_status_string() << endl;
    return out;
}

ifstream& operator>> (ifstream& fin, Pipe& p) {
    fin >> p.id;
    fin >> ws;
    getline(fin, p.name);
    fin >> p.lenght;
    fin >> p.diameter;
    fin >> p.status;
    Pipe::max_id = (Pipe::max_id < p.id) ? p.id : Pipe::max_id;
    return fin;
}

ofstream& operator<< (ofstream& fout, const Pipe& p) {
    fout << p.id << endl
         << p.name << endl
         << p.lenght << endl
         << p.diameter << endl
         << p.status << endl;
    return fout;
}
