#define _USE_MATH_DEFINES
#include "Pipe.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cmath>
#include <cfloat>
#include <algorithm>

using namespace std;


int Pipe::max_id = 0;
const int Pipe::valid_diameters[4] = {500, 700, 1000, 1400};

void Pipe::reset_max_id() {
    max_id = 0;
}

int Pipe::get_max_id() { 
    return max_id;
}

int Pipe::get_correct_diameter() {
    int diameter = GetCorrectNumber(cin, 500, 1400, "diameter (" + Pipe::get_valid_diameters_string() + ") (mm): ", "");
    while (count(begin(valid_diameters), end(valid_diameters), diameter) <= 0) {
        cout << "*Diameter must be " + Pipe::get_valid_diameters_string() + ", please repeat" << endl;
        diameter = GetCorrectNumber(cin, 500, 1400, "diameter (" + Pipe::get_valid_diameters_string() + ") (mm): ", "");
    }
    return diameter;
}

string Pipe::get_valid_diameters_string() {
    string res;
    if (size(valid_diameters) > 2) {
        for (std::size_t i = 0; i < size(valid_diameters) - 2; ++i) {
            res += std::to_string(valid_diameters[i]) + ", ";
        }
    }
    if (size(valid_diameters) > 1) {
        res += std::to_string(valid_diameters[size(valid_diameters) - 2]) + " or ";
    }   
    res += std::to_string(valid_diameters[size(valid_diameters) - 1]);
    return res;
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

int Pipe::get_diameter() const {
    return diameter;
}

bool Pipe::get_status() const {
    return status;
}

string Pipe::get_status_string() const {
    return status ? "work" : "in repair";
}

double Pipe::get_capasity() const {
    double L = lenght * 1000.0;      // lenght                  m
    double D = diameter / 1000.0;    // diameter                m
    double H = 0.015;                // pipe thickness          m
    double sigma = 500 * pow(10, 6); // steel strength          N/m^2
    int V_max = 25;                  // max permissible speed   m/s
    double h = 0.03 / 1000.0;        // roughness               m
    double R = 8.31;                 // gas constant            J/(mole * K)
    int T = 293;                     // temperature             K    
    double mu = 0.016;               // molar mass              kg/mole
    double N = pow(10, 6);           // surface concentration
    
    double capasity = (sigma * H / D) / 
        sqrt(pow((4 * R * T)/(mu * M_PI * pow(D, 2) * V_max) , 2) + (64 * L * N * R * T * pow(h, 2))/(pow(M_PI, 2) * mu * pow(D, 5)));

    return status ? capasity : 0.0; // kg/s
    //return status ? lenght : 0.0;
}

double Pipe::get_weight() const {
    return status ? lenght : DBL_MAX;
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
    InputLine(in, p.name);
    p.lenght = GetCorrectNumber(in, 0.000001, DBL_MAX,
        "lenght (km): ", "**The number must be positive, please repeat\n");
    p.diameter = Pipe::get_correct_diameter();
    p.status = GetCorrectNumber(in, 0, 1, "status (1 - work, 0 - in repair): ", "");   
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

void inputPipeWithoutDiameter(Pipe& p, const int d) {
    cout << "name: ";
    InputLine(cin, p.name);
    p.lenght = GetCorrectNumber(cin, 0.000001, DBL_MAX,
        "lenght (km): ", "**The number must be positive, please repeat\n");
    p.diameter = d;
    p.status = GetCorrectNumber(cin, 0, 1, "status (1 - work, 0 - in repair): ", "");   
}
