#include "Menu.h"
#include "PTS.h"
#include "Pipe.h"
#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;


void Print(const string menu[], const int size) {
    for (size_t i{}; i < size; i++) {
        cout << menu[i] << endl;
    }
    cout << "\n";
}

void BackToMenu() {
    cout << "\n\nPlease, press Enter to return to menu...";
    while (_getch() != 13) { continue; }
    system("cls");
}

bool SystemHasObjects(PTS& pts, const PTS::ObjectType obj) {
    auto IDs = pts.get_ids_objects(obj);
    if (!IDs.empty()) {
        return true;
    }
    else {
        cout << "*System has no " << pts.to_string(obj) << "s\n";
        return false;
    }
}

void ViewObjects(PTS& pts, const PTS::ObjectType obj) {
    cout << "-> View Objects" << endl
        << "     -> " << pts.to_string(obj) << "s" << endl;

    if (SystemHasObjects(pts, obj)) {
        pts.view(obj, pts.get_ids_objects(obj));
    }    
}

void ViewMenu(PTS& pts) {
    const int view_menu_size = 5;
    const std::string view_menu[view_menu_size] = {
    "-> View Objects",
    "     1. View Pipes",
    "     2. View Stations",
    "     3. View All",
    "     0. Return"
    };
    Print(view_menu, view_menu_size);
    int view = GetCorrectNumber(cin, 0, 3, ">> ", "");
    system("cls");
    switch (view) {
    case 1:
    {
        ViewObjects(pts, PTS::PIPE);
        BackToMenu();
        break;
    }
    case 2:
    {
        ViewObjects(pts, PTS::STATION);
        BackToMenu();
        break;
    }
    case 3:
    {
        ViewObjects(pts, PTS::PIPE);
        cout << "\n";
        ViewObjects(pts, PTS::STATION);
        BackToMenu();
        break;
    }
    case 0:
    default: 
    { 
        system("cls"); 
        break; 
    }
    }
}

unordered_set<int> SelectSpecificIDs(const unordered_set<int>& IDs, const int max_id) {
    int select = GetCorrectNumber(cin, 0, 1, "Select (0 - all, 1 - some): ", "");
    switch (select) {
    case 1:
    {
        cout << "Select IDs ('0' - end):\n";
        auto spec_IDs = SelectIDs(IDs, max_id);
        return spec_IDs;
    }
    case 0: 
    default: { return IDs; }
    }
}

unordered_set<int> SearchByName(PTS& pts, const PTS::ObjectType obj) {
    cout << "name: ";
    string name;
    InputLine(cin, name);
    switch (obj) {
    case PTS::PIPE: { 
        return pts.search(check_pipe_by_name, name);
    }
    case PTS::STATION: { 
        return pts.search(check_station_by_name, name);
    }
    default: { 
        return unordered_set<int>{};
    }
    }
}

unordered_set<int> SearchPipes(PTS& pts) {
    unordered_set<int> IDs;
    int search = GetCorrectNumber(cin, 0, 2, "Select option (0 - name, 1 - status, 2 - all(no filter)): ", "");
    switch (search) {
    case 0: 
    {
        IDs = SearchByName(pts, PTS::PIPE);
        break;
    }
    case 1: 
    {
        bool status = GetCorrectNumber(cin, 0, 1, "status(1 - work, 0 - in repair): ", "");
        IDs = pts.search(check_pipe_by_status, status);
        break;
    }
    case 2: 
    { 
        IDs = pts.get_ids_objects(PTS::PIPE);
        break; 
    }
    }
    return IDs;
}

unordered_set<int> SearchStations(PTS& pts) {
    unordered_set<int> IDs;
    int search = GetCorrectNumber(cin, 0, 2, "Select option (0 - name, 1 - % unactive workshops, 2 - all(no filter)): ", "");
    switch (search) {
    case 0:
    {
        IDs = SearchByName(pts, PTS::STATION);
        break;
    }
    case 1:
    {
        double perc = GetCorrectNumber(cin, 0.0, 100.0, "% unactive workshops: ", "");
        IDs = pts.search(check_station_by_unactive_workshops, perc);
        break;
    }
    case 2:
    {
        IDs = pts.get_ids_objects(PTS::STATION);
        break;
    }
    }
    return IDs;
}

unordered_set<int> SearchObjects(PTS& pts, const PTS::ObjectType obj) {
    switch (obj) {
    case PTS::PIPE: { 
        return SearchPipes(pts);
    }
    case PTS::STATION: { 
        return SearchStations(pts);
    }
    }
}

void Edit(PTS& pts, const PTS::ObjectType obj, const unordered_set<int>& IDs) {
    switch (obj) {
    case PTS::PIPE:
    {
        int edit = GetCorrectNumber(cin, 0, 2, "Select option (1 - work, 0 - in repair, 2 - opposite): ", "");

        switch (edit) {
        case 0: { pts.edit(IDs, Pipe::SET_IN_REPAIR); break; }
        case 1: { pts.edit(IDs, Pipe::SET_WORK);      break; }
        case 2: { pts.edit(IDs, Pipe::SET_OPPOSITE);  break; }
        }
        return;
    }
    case PTS::STATION:
    {
        int edit = GetCorrectNumber(cin, 0, 1, "Select option (1 - start workshop, 0 - stop workshop): ", "");

        switch (edit) {
        case 0: { pts.edit(IDs, Station::STOP_ONE_WS);  break; }
        case 1: { pts.edit(IDs, Station::START_ONE_WS); break; }
        }
        return;
    }
    }
}

void EditOneObject(PTS& pts, const PTS::ObjectType obj, bool remove = false) {
    auto all_IDs = pts.get_ids_objects(obj);
    pts.short_view(obj, all_IDs);

    int selected_ID = GetCorrectNumber(cin, 1, INT_MAX, "Select ID: ", "**The number must be more 1, please repeat\n");

    if (!all_IDs.contains(selected_ID)) {
        cout << "id::" << selected_ID << " *No such id exists\n";
    }
    else if (!remove) { 
        Edit(pts, obj, { selected_ID });
        pts.short_view(obj, all_IDs);
    }
    else { 
        pts.remove(obj, selected_ID);
        cout << "id::" << selected_ID << " " << pts.to_string(obj) << " was removed\n";
    }
}

void BatchEditing(PTS& pts, const PTS::ObjectType obj) {
    auto IDs = SearchObjects(pts, obj);
    if (IDs.empty()) {
        cout << "*No valid IDs selected\n";
        return;
    }
    pts.short_view(obj, IDs);

    int max_id = obj == PTS::PIPE ? Pipe::get_max_id() : Station::get_max_id();
    IDs = SelectSpecificIDs(IDs, max_id);

    if (!IDs.empty()) {
        pts.short_view(obj, IDs);
        Edit(pts, obj, IDs);
        pts.short_view(obj, IDs);
    }
    else { cout << "*No valid IDs selected\n"; }
}

void EditMenu(PTS& pts, const PTS::ObjectType obj) {
    cout << "-> Edit " << pts.to_string(obj) << "s" << endl;
    
    if (!SystemHasObjects(pts, obj)) {
        BackToMenu();
        return;
    }

    const int edit_menu_size = 4;
    const std::string edit_menu[edit_menu_size] = {
    "     1. Edit " + pts.to_string(obj),
    "     2. Banch editing " + pts.to_string(obj) + "s",
    "     3. Remove " + pts.to_string(obj),
    "     0. Return"
    };
    Print(edit_menu, edit_menu_size);
    int view = GetCorrectNumber(cin, 0, 3, ">> ", "");
    system("cls");
    cout << "-> Edit " << pts.to_string(obj) << "s" << endl;

    switch (view) {
    case 1:
    {
        cout << "     -> One " << pts.to_string(obj) << endl;
        EditOneObject(pts, obj);
        BackToMenu();
        break;
    }
    case 2:
    {
        cout << "     -> Banch editing" << endl;
        BatchEditing(pts, obj);
        BackToMenu();
        break;
    }
    case 3:
    {
        cout << "     -> Remove " << pts.to_string(obj) << endl;
        EditOneObject(pts, obj, true);
        BackToMenu();
        break;
    }
    case 0:
    default: 
    { 
        system("cls");
        break;
    }
    }
}

void AddEdge(PTS& pts) {

    if (!SystemHasObjects(pts, PTS::STATION)) {
        return;
    }

    cout << "Free Pipes:\n";
    if (!pts.get_free_pipes(pts.get_ids_objects(PTS::PIPE)).empty()) {
        pts.short_view(PTS::PIPE, pts.get_free_pipes(pts.get_ids_objects(PTS::PIPE)));
    }
    else {
        cout << "*No free Pipes" << endl;
    }
    cout << "Stations:\n";
    pts.short_view(PTS::STATION, pts.get_ids_objects(PTS::STATION));

    int source = GetCorrectNumber(cin, 1, Station::get_max_id(), "source station id: ", "");
    int sink = GetCorrectNumber(cin, 1, Station::get_max_id(), "sink station id: ", "");
    int diameter = Pipe::get_correct_diameter();
    pts.add_edge(source, sink, diameter);
}

void RemoveEdge(PTS& pts) {
    if (!SystemHasObjects(pts, PTS::STATION)) {
        return;
    }
    pts.view_edges();
    int pipe_id = GetCorrectNumber(cin, 1, Pipe::get_max_id(), "Select edge (by pipe ID): ", "");
    pts.remove_edge(pipe_id);
}

void GraphMenu(PTS& pts) {
    cout << "-> Graph " << endl;

    const int graph_menu_size = 5;
    const std::string graph_menu[graph_menu_size] = {
    "     1. Add Edge",
    "     2. View Edges",
    "     3. Remove Edge",
    "     4. Topological Sorting",
    "     0. Return"
    };
    Print(graph_menu, graph_menu_size);
    int graph = GetCorrectNumber(cin, 0, 4, ">> ", "");
    system("cls");
    cout << "-> Graph " << endl;
    switch (graph) {
    case 1:
    {
        cout << "     -> Add Edge" << endl;
        AddEdge(pts);
        BackToMenu();
        break;
    }    
    case 2:
    {
        cout << "     -> View Edges" << endl;
        pts.view_edges();
        BackToMenu();
        break;
    }
    case 3:
    {
        cout << "     -> Remove Edge" << endl;
        RemoveEdge(pts);
        BackToMenu();
        break;
    }
    case 4:
    {
        cout << "     -> Topological Sorting" << endl;
        auto vec = pts.TopologicalSort();
        if (!vec.empty()) {
            cout << "Result: ";
            for (auto& i : vec) {
                cout << i << " ";
            }
            cout << "\n";
        }
        BackToMenu();
        break;
    }
    case 0:
    default:
    {
        system("cls");
        break;
    }
    }
}

void InputFileName(PTS& pts) {
    cout << "Entry name of the file: ";
    string fn;
    InputLine(cin >> ws, fn);
    pts.set_filename(fn);
}

bool CheckBeforeSave(PTS& pts) {
    if (pts.saved()) {
        if (pts.has_saved_file()) { 
            cout << "*There are no unsaved changes in the system\n"; 
            return false; 
        }
        else if (pts.empty()) {
            cout << "*System is empty\n";
            if (GetCorrectNumber(cin, 0, 1, "Do you want to save an empty file? (1 - yes, 0 - no): ", "") == 0) {
                return false; 
            }
        }
    }
    else if (pts.has_saved_file()) {
        if (GetCorrectNumber(cin, 0, 1, "Do you want to save in the same file? (1 - yes, 0 - no): ", "") == 0) {
            InputFileName(pts);
        }
        return true;
    }
    else if (pts.empty()) {
        cout << "*System is empty\n";
        if (GetCorrectNumber(cin, 0, 1, "Do you want to save an empty file? (1 - yes, 0 - no): ", "") == 0) {
            return false; 
        }
    }
    InputFileName(pts);
    return true;
}

bool CheckBeforeLoad(PTS& pts) {
    if (!pts.saved()) {
        if (pts.has_saved_file()) {
            cout << "*There are unsaved changes in the system\n";
            if (GetCorrectNumber(cin, 0, 1, "Do you want to save in the same file? (1 - yes, 0 - no): ", "") == 0) {
                InputFileName(pts);
            }
            pts.save_to_file();
        }
        else {
            cout << "*The changes made are new and not saved\n";
            if (GetCorrectNumber(cin, 0, 1, "Do you want to save changes to file? (1 - yes, 0 - no): ", "") == 0) {
                cout << "*Data was lost\n";
            }
            else {
                InputFileName(pts);
                pts.save_to_file();
            }
        }
    }
    InputFileName(pts);
    return true;
}
