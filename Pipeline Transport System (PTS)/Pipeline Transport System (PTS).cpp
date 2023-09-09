#include <iostream>
#include <vector>

using namespace std;

struct Pipe {
    string name;
    double lenght;
    int diameter;
    bool in_repair;
};

struct Station {
    string name;
    int num_workshops;
    int workshops_in_operation;
    double efficiency;
};

int main()
{
    vector<Pipe> pipes = {};
    vector<Station> stations = {};
    return 0;
}
