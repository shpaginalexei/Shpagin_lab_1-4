#include "Pipe.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int Pipe::max_id = 1;

Pipe::Pipe() {
    id = ++max_id;
}

int Pipe::get_id() const {
    return id;
}

string Pipe::get_status() const {
    return status ? "work" : "in repair";
}

void Pipe::change_status() {
    status = !status;
}


istream& operator>> (istream& in, Pipe& p) {
    cout << "\nname: ";
    getline(in, p.name);
    p.lenght = GetCorrectNumValue<double>("lenght (km): ", 0.0, DBL_MAX,
        "**The number must be positive, please repeat\n");
    p.diameter = GetCorrectNumValue<int>("diameter (mm): ", 0, INT_MAX,
        "**The number must be positive, please repeat\n");
    p.status = GetCorrectYesNoValue<double>("in repair? (Y/n): ");
    
    return in;
}

ostream& operator<< (ostream& out, const Pipe& p) {
    out << "\n\tPipe id::" << p.id << endl
        << "name - " << p.name << endl
        << "lenght - " << p.lenght << " km" << endl
        << "diameter - " << p.diameter << " mm" << endl
        << "status - " << p.get_status() << endl;
    out << "\n";

    return out;
}

ifstream& operator>> (ifstream& fin, Pipe& p) {
    fin >> p.id;
    fin.ignore();
    getline(fin, p.name);
    fin >> p.lenght;
    fin >> p.diameter;
    fin >> p.status;

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
