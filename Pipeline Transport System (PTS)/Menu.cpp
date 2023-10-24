#include "Menu.h"
//#include "PTS.h"
#include "Pipe.h"
#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

PTS pts;

const int main_menu_size = 9;
const std::string main_menu[main_menu_size] = {
"1. Add Pipe",
"2. Add Station",
"3. View Objects",
"4. Edit Pipes",
"5. Edit Stations",
"6. Search",
"7. Save",
"8. Load",
"0. Exit"
};

const int view_menu_size = 5;
const std::string view_menu[view_menu_size] = {
"-> View Objects",
"     1. View Pipes",
"     2. View Stations",
"     3. View All",
"     0. Return"
};

const int edit_pipe_menu_size = 5;
const std::string edit_pipe_menu[edit_pipe_menu_size] = {
"-> Edit Pipes",
"     1. Edit Pipe",
"     2. Banch editing Pipes",
"     3. Remove Pipe",
"     0. Return"
};

const int edit_station_menu_size = 5;
const std::string edit_station_menu[edit_station_menu_size] = {
"-> Edit Stations",
"     1. Edit Station",
"     2. Banch editing Stations",
"     3. Remove Station",
"     0. Return"
};

const int search_menu_size = 4;
const std::string search_menu[search_menu_size] = {
"-> Search",
"     1. Search Pipes",
"     2. Search Stations",
"     0. Return"
};

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

void ViewGroup(PTS::GroupType group) {
    cout << "-> View Objects" << endl
        << "     -> " << to_string(group) << "s" << endl;
    auto IDs = pts.get_group_ids(group);
    if (!IDs.empty()) { pts.view(group, IDs); }
    else { cout << "\n*System hasn't " << to_string(group) << "s" << "\n\n"; }
}

void ViewMenu() {
    ViewText(view_menu, view_menu_size);
    int view = GetCorrectNumber(cin, 0, 4, ">> ", "**The number must be in the range 0..3, please repeat\n");
    system("cls");
    switch (view) {
    case 1:
    {
        ViewGroup(PTS::PIPES);
        BackToMenu();
        break;
    }
    case 2:
    {
        ViewGroup(PTS::STATIONS);
        BackToMenu();
        break;
    }
    case 3:
    {
        ViewGroup(PTS::PIPES);
        ViewGroup(PTS::STATIONS);
        BackToMenu();
        break;
    }
    case 0:
    default: { system("cls"); break; }
    }
}

void EditObjects(PTS::GroupType group, const unordered_set<int>& IDs) {
    switch (group) {
    case PTS::PIPES: {
        int edit = GetCorrectNumber(cin, 0, 3, "Select option (1 - work, 0 - in repair, 2 - opposite): ",
            "**The number must be in range 0..2, please repeat\n");
        Pipe::StatusType editType = Pipe::StatusType::UNKNOWN;
        switch (edit) {
        case 0: { editType = Pipe::StatusType::IN_REPAIR; break; }
        case 1: { editType = Pipe::StatusType::WORK;      break; }
        case 2: { editType = Pipe::StatusType::OPPOSITE;  break; }
        }
        pts.edit<PTS::PIPES>(IDs, editType);
        return;
    }
    case PTS::STATIONS: {
        int edit = GetCorrectNumber(cin, 0, 2, "Select option (1 - start workshop, 0 - stop workshop): ",
            "**The number must be in range 0 or 1, please repeat\n");
        Station::WhatDo editType = Station::WhatDo::UNKNOWN;
        switch (edit) {
        case 0: { editType = Station::WhatDo::STOP;  break; }
        case 1: { editType = Station::WhatDo::START; break; }
        }
        pts.edit<PTS::STATIONS>(IDs, editType);
        return;
    }
    }
}

unordered_set<int> SelectSpecificKeys(PTS::GroupType group, const unordered_set<int>& IDs) {
    int select = GetCorrectNumber(cin, 0, 2, "Select (0 - all, 1 - some): ",
        "**The number must be 0 or 1, please repeat\n");
    if (select == 0) { pts.short_view(group, IDs); return IDs; }
    else {
        unordered_set<int> spec_IDs;
        int id;
        cout << "Select some IDs: ";
        while (cin.peek() != '\n') {
            cin >> id;
            if (cin.fail()) { cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), ' '); }
            else if (IDs.contains(id)) { spec_IDs.insert(id); }
        }
        return spec_IDs;
    }
}

unordered_set<int> SearchObjects(PTS::GroupType group) {
    unordered_set<int> IDs;
    int search = GetCorrectNumber(cin, 0, 3, "Select option (0 - name, 1 - status/% unactive workshops, 2 - all): ",
        "**The number must be in range 0..2, please repeat\n");
    switch (search) {
    case 0: { 
        cout << "name: ";
        string name;
        cin >> ws;
        getline(cin, name);
        switch (group) {
        case PTS::PIPES:    { IDs = pts.search<PTS::PIPES>(name, check_pipe_by_name);       break; }
        case PTS::STATIONS: { IDs = pts.search<PTS::STATIONS>(name, check_station_by_name); break; }
        }
        pts.short_view(group, IDs);
        IDs = SelectSpecificKeys(group, IDs);
        break;
    }
    case 1: {
        switch (group) {
        case PTS::PIPES: {
            bool status = GetCorrectNumber(cin, 0, 2, "status(1 - work, 0 - in repair): ", "**The number must be 0 or 1, please repeat\n");
            IDs = pts.search<PTS::PIPES>(status, check_pipe_by_status);       
            break; 
        }
        case PTS::STATIONS: {
            double perc = GetCorrectNumber(cin, 0.0, 100.0, "% unactive workshops: ", "**The number must be in range 0..100, please repeat\n");
            IDs = pts.search<PTS::STATIONS>(perc, check_station_by_unactive_workshops); 
            break; 
        }
        }
        pts.short_view(group, IDs);
        IDs = SelectSpecificKeys(group, IDs);
        break;
    }
    case 2: { IDs = pts.get_group_ids(group);  break; }
    }
    pts.short_view(group, IDs);
    return IDs;
}

void EditOneObject(PTS::GroupType group, bool remove) {
    auto IDs = pts.get_group_ids(group);
    pts.short_view(group, IDs);
    int selected_ID = GetCorrectNumber(cin, 1, INT_MAX, "Select ID: ",
        "**The number must be more 1, please repeat\n");
    if (!IDs.contains(selected_ID)) {
        cout << "id::" << selected_ID << " *No such id exists\n";
        return;
    }
    if (!remove) { EditObjects(group, { selected_ID }); pts.short_view(group, IDs); }
    else { pts.remove_from(group, selected_ID); /*cout about remove*/ }
}

void BatchEditing(PTS::GroupType group) {
    unordered_set<int> IDs = SearchObjects(group);
    EditObjects(group, IDs);
    pts.short_view(group, IDs);
}

void EditMenu(PTS::GroupType group) {
    auto IDs = pts.get_group_ids(group);
    if (IDs.empty()) {
        cout << "\n*System hasn't " << to_string(group) << "s" << "\n"; BackToMenu(); return;
    }
    switch (group) {
    case PTS::PIPES: { ViewText(edit_pipe_menu, edit_pipe_menu_size); break; }
    case PTS::STATIONS: { ViewText(edit_station_menu, edit_station_menu_size); break; }
    }
    int view = GetCorrectNumber(cin, 0, 4, ">> ", "**The number must be in the range 0..3, please repeat\n");
    system("cls");
    switch (view) {
    case 1:
    {
        cout << "-> Edit " << to_string(group) << endl;
        EditOneObject(group, false);
        BackToMenu();
        break;
    }
    case 2:
    {
        cout << "-> Banch editing " << to_string(group) << "s" << endl;
        BatchEditing(group);
        BackToMenu();
        break;
    }
    case 3:
    {
        cout << "-> Remove " << to_string(group) << endl;
        EditOneObject(group, true);
        BackToMenu();
        break;
    }
    case 0:
    default: { system("cls"); break; }
    }
}

void InputFileName() {
    cout << "Entry name of the file: ";
    cin >> ws;
    getline(cin, pts.file_name);
}

bool CheckBeforeSave() {
    if (!pts.changed) {
        if (pts.saved) { cout << "\n*There are no unsaved changes in the system\n"; return false; }
        else if (pts.empty) {
            cout << "\n*System is empty\n";
            if (GetCorrectNumber(cin, 0, 2, "Do you want to save an empty file? (1 - yes, 0 - no): ", 
                "**The enter must be 0 or 1, please repeat\n") == 0) { return false; }
            else { cout << "\n"; InputFileName(); }
        }
        else { cout << "?"; return false; }
    }
    else if (pts.saved) {
        cout << "\n";
        if (GetCorrectNumber(cin, 0, 2, "Do you want to save in the same file? (1 - yes, 0 - no): ",
            "**The enter must be 0 or 1, please repeat\n") == 0) { InputFileName(); }
    }
    else if (pts.empty) {
        cout << "\n*System is empty\n";
        if (GetCorrectNumber(cin, 0, 2, "Do you want to save an empty file? (1 - yes, 0 - no): ",
            "**The enter must be 0 or 1, please repeat\n") == 0) { return false; }
        else { cout << "\n"; InputFileName(); }
    }
    else { cout << "\n"; InputFileName(); }
    return true;
}

bool CheckBeforeLoad() {
    if (pts.changed) {
        if (pts.saved) { cout << "\n*There are unsaved changes in the system\n"; }
        else { cout << "\n*The changes made are new and not saved\n"; }
        if (CheckBeforeSave()) { pts.save_to_file(); InputFileName(); }
        else { return false; }
    }
    else { InputFileName(); }
    return true;
}

void SearchMenu() {
    ViewText(search_menu, search_menu_size);
    int search = GetCorrectNumber(cin, 0, 3, ">> ", "**The number must be in the range 0..2, please repeat\n");
    system("cls");
    switch (search) {
    case 1:
    {
        cout << "-> Search" << endl
            << "     -> Pipes" << endl;
        //
        break;
    }
    case 2:
    {
        cout << "-> Search" << endl
            << "     -> Stations" << endl;
        //
        break;
    }
    case 0:
    default: { system("cls"); break; }
    }
}

void MainMenu() {
    while (true) {
        ViewText(main_menu, main_menu_size);
        int menu = GetCorrectNumber(cin, 0, 9, ">> ", "**The number must be in the range 0..8, please repeat\n");
        system("cls");
        switch (menu) {
        case 1:
        {
            cout << "-> Add Pipe" << endl;
            pts.add_to(PTS::PIPES);
            BackToMenu();
            break;
        }
        case 2:
        {
            cout << "-> Add Station" << endl;
            pts.add_to(PTS::STATIONS);
            BackToMenu();
            break;
        }
        case 3:
        {
            ViewMenu();
            break;
        }
        case 4:
        {
            EditMenu(PTS::PIPES);
            break;
        }
        case 5:
        {
            EditMenu(PTS::STATIONS);
            break;
        }
        case 6:
        {
            SearchMenu();
            break;
        }
        case 7:
        {
            cout << "-> Save" << endl;
            if (CheckBeforeSave()) { pts.save_to_file(); }
            BackToMenu();
            break;
        }
        case 8:
        {
            cout << "-> Load" << endl;
            if (CheckBeforeLoad()) { pts.load_from_file(); }
            BackToMenu();
            break;
        }
        case 0:
        default: { system("cls"); return; }
        }
    }
}
