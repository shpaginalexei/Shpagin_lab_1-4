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


void ViewText(const string menu[], const int size) {
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
    ViewText(view_menu, view_menu_size);
    int view = GetCorrectNumber(cin, 0, 4, ">> ", "**The number must be in the range 0..3, please repeat\n");
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

unordered_set<int> SelectSpecificIDs(const unordered_set<int>& IDs) {
    int select = GetCorrectNumber(cin, 0, 2, "Select (0 - all, 1 - some): ",
        "**The number must be 0 or 1, please repeat\n");
    switch (select) {
    case 1:
    {
        unordered_set<int> spec_IDs;

        // GetCorrectKeys

        int id;
        cout << "Select some IDs: ";
        string s;
        getline(cin, s);
        istringstream is(s);
        while (!is.eof()) {
            if (is >> id && IDs.contains(id)) { spec_IDs.insert(id); }
            else { is.clear(); is.ignore(1, ' '); }
        }

        return spec_IDs;
    }
    case 0: 
    default: { return IDs; }
    }
}

unordered_set<int> SearchByName(PTS& pts, const PTS::ObjectType obj) {
    cout << "name: ";
    string name;
    cin >> ws;
    getline(cin, name);
    switch (obj) {
    case PTS::PIPE:    { return pts.search(check_pipe_by_name,    name); }
    case PTS::STATION: { return pts.search(check_station_by_name, name); }
    default:           { return unordered_set<int>{}; }
    }
}

unordered_set<int> SearchPipes(PTS& pts) {
    unordered_set<int> IDs;
    int search = GetCorrectNumber(cin, 0, 3, "Select option (0 - name, 1 - status, 2 - all(no filter)): ",
        "**The number must be in range 0..2, please repeat\n");
    switch (search) {
    case 0: 
    {
        IDs = SearchByName(pts, PTS::PIPE);
        break;
    }
    case 1: 
    {
        bool status = GetCorrectNumber(cin, 0, 2, "status(1 - work, 0 - in repair): ", "**The number must be 0 or 1, please repeat\n");
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
    int search = GetCorrectNumber(cin, 0, 3, "Select option (0 - name, 1 - % unactive workshops, 2 - all(no filter)): ",
        "**The number must be in range 0..2, please repeat\n");
    switch (search) {
    case 0:
    {
        IDs = SearchByName(pts, PTS::STATION);
        break;
    }
    case 1:
    {
        double perc = GetCorrectNumber(cin, 0.0, 100.0, "% unactive workshops: ", "**The number must be in range 0..100, please repeat\n");
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
    case PTS::PIPE:    { return SearchPipes(pts);     }
    case PTS::STATION: { return SearchStations(pts);  }
    default:           { return unordered_set<int>{}; }
    }
}

void Edit(PTS& pts, const PTS::ObjectType obj, const unordered_set<int>& IDs) {
    switch (obj) {
    case PTS::PIPE:
    {
        int edit = GetCorrectNumber(cin, 0, 3, "Select option (1 - work, 0 - in repair, 2 - opposite): ",
            "**The number must be in range 0..2, please repeat\n");

        switch (edit) {
        case 0: { pts.edit(IDs, Pipe::SET_IN_REPAIR); break; }
        case 1: { pts.edit(IDs, Pipe::SET_WORK);      break; }
        case 2: { pts.edit(IDs, Pipe::SET_OPPOSITE);  break; }
        }
        return;
    }
    case PTS::STATION:
    {
        int edit = GetCorrectNumber(cin, 0, 2, "Select option (1 - start workshop, 0 - stop workshop): ",
            "**The number must be in range 0 or 1, please repeat\n");

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
    auto all_IDs = SearchObjects(pts, obj);
    pts.short_view(obj, all_IDs);

    all_IDs = SelectSpecificIDs(all_IDs);
    pts.short_view(obj, all_IDs);

    if (!all_IDs.empty()) {
        Edit(pts, obj, all_IDs);
        pts.short_view(obj, all_IDs);
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
    ViewText(edit_menu, edit_menu_size);
    int view = GetCorrectNumber(cin, 0, 4, ">> ", "**The number must be in the range 0..3, please repeat\n");
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

void InputFileName(PTS& pts) {
    cout << "Entry name of the file: ";
    cin >> ws;
    getline(cin, pts.file_name);
}

bool CheckBeforeSave(PTS& pts) {
    if (!pts.changed) {
        if (pts.saved()) { 
            cout << "*There are no unsaved changes in the system\n"; 
            return false; 
        }
        else if (pts.empty()) {
            cout << "*System is empty\n";
            if (GetCorrectNumber(cin, 0, 2, "Do you want to save an empty file? (1 - yes, 0 - no): ", 
                "**The enter must be 0 or 1, please repeat\n") == 0) { 
                return false; 
            }
            else {
                InputFileName(pts);
                return true;
            }
        }
        else { cout << "\n?\n"; return false; }
    }
    else if (pts.saved()) {
        if (GetCorrectNumber(cin, 0, 2, "Do you want to save in the same file? (1 - yes, 0 - no): ",
            "**The enter must be 0 or 1, please repeat\n") == 0) { 
            InputFileName(pts);
        }
        return true;
    }
    else if (pts.empty()) {
        cout << "*System is empty\n";
        if (GetCorrectNumber(cin, 0, 2, "Do you want to save an empty file? (1 - yes, 0 - no): ",
            "**The enter must be 0 or 1, please repeat\n") == 0) { 
            return false; 
        }
        else { 
            InputFileName(pts);
            return true;
        }
    }
    else { 
        InputFileName(pts);
        return true;
    }
}

bool CheckBeforeLoad(PTS& pts) {
    if (pts.changed) {
        if (pts.saved()) {
            cout << "*There are unsaved changes in the system\n";
            if (GetCorrectNumber(cin, 0, 2, "Do you want to save in the same file? (1 - yes, 0 - no): ",
                "**The enter must be 0 or 1, please repeat\n") == 0) {
                InputFileName(pts);
            }
            pts.save_to_file();
        }
        else {
            cout << "*The changes made are new and not saved\n";
            if (GetCorrectNumber(cin, 0, 2, "Do you want to save changes to file? (1 - yes, 0 - no): ",
                "**The enter must be 0 or 1, please repeat\n") == 0) {
                return true;
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

void MainMenu(PTS& pts) {
    const int main_menu_size = 9;
    const std::string main_menu[main_menu_size] = {
    "1. Add Pipe",
    "2. Add Station",
    "3. View Objects",
    "4. Edit Pipes",
    "5. Edit Stations",
    "6. Save",
    "7. Load",
    "0. Exit"
    };
    while (true) {
        ViewText(main_menu, main_menu_size);
        int menu = GetCorrectNumber(cin, 0, 8, ">> ", "**The number must be in the range 0..8, please repeat\n");
        system("cls");
        switch (menu) {
        case 1:
        {
            cout << "-> Add Pipe" << endl;
            pts.add(PTS::PIPE);
            BackToMenu();
            break;
        }
        case 2:
        {
            cout << "-> Add Station" << endl;
            pts.add(PTS::STATION);
            BackToMenu();
            break;
        }
        case 3:
        {
            ViewMenu(pts);
            break;
        }
        case 4:
        {
            EditMenu(pts, PTS::PIPE);
            break;
        }
        case 5:
        {
            EditMenu(pts, PTS::STATION);
            break;
        }
        case 6:
        {
            cout << "-> Save" << endl;

            if (CheckBeforeSave(pts)) { 
                pts.save_to_file(); 
            }
            BackToMenu();
            break;
        }
        case 7:
        {
            cout << "-> Load" << endl;

            if (CheckBeforeLoad(pts)) { 
                pts.load_from_file();
            }
            BackToMenu();
            break;
        }
        case 0:
        default: 
        { 
            system("cls"); 
            return; 
        }
        }
    }
}
