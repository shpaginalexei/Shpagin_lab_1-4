#pragma once
#include "Pipe.h"
#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <unordered_set>

class App
{
public:

	//void add_pipe();
	//void add_station();
	template <typename T> void add_to(std::unordered_map<int, T>& group);
	
	//void edit_pipes();
	//void edit_stations();
    template <typename T> void edit(std::unordered_map<int, T>& group);

	//void view_pipes() const;
	//void view_stations() const;
    template <typename T> void view(std::unordered_map<int, T>& group) const;

	//void search_pipes();
	//void search_stations();
    template <typename T> void search(std::unordered_map<int, T>& group);

	void input_file_name();
	void save_to_file();
	void load_from_file();

    std::unordered_map<int, Pipe> pipes{};
    std::unordered_map<int, Station> stations{};

private:

	bool empty = true;
	bool changed = false;
	bool saved = false;
	std::string file_name = "";
	const std::string path = ".saves\\";

	//bool pipes_is_empty() const;
	//bool stations_is_empty() const;
	//template <typename T> bool is_empty(std::unordered_map<int, T>& group) const;

	//std::unordered_set<int> get_pipes_by_filter();
	//std::unordered_set<int> get_stations_by_filter();
    template <typename T> std::unordered_set<int> get_objs_by_filter(std::unordered_map<int, T>& group);

	//void short_view_pipes() const;
	//void short_view_pipes(const std::unordered_set<int>&) const;
	//void short_view_stations() const;
	//void short_view_stations(const std::unordered_set<int>&) const;
    template <typename T> void short_view(std::unordered_map<int, T>& group) const;
    template <typename T> void short_view(std::unordered_map<int, T>& group, const std::unordered_set<int>& IDs) const;

	//void edit_one_pipe();
	//void edit_one_station();
    template <typename T> void edit_one_from(std::unordered_map<int, T>& group);
	//void edit_mult_pipes();
	//void edit_mult_stations();
    template <typename T> void edit_mult_from(std::unordered_map<int, T>& group);
	//void remove_pipe();
	//void remove_station();
    template <typename T> void remove_from(std::unordered_map<int, T>& group);

};

bool check_by_name(Pipe&, std::string);
bool check_by_name(Station&, std::string);
bool check_by_status(Pipe&, bool);
bool check_by_unworking_workshops(Station&, double);


template<typename T>
bool is_empty(std::unordered_map<int, T>& group) {
    if (group.empty()) {
        std::cout << "\n*The group hasn't objects\n";
        return true;
    }
    return false;
}

template <typename T>
inline std::string value_type(std::unordered_map<int, T>& group) {
    return typeid(T).name();
}

template<typename T>
std::unordered_set<int> App::get_objs_by_filter(std::unordered_map<int, T>& group) {
    if (!is_empty(group)) {
        int search_choice = 0;
        std::unordered_set<int> IDs;
        if (typeid(Pipe).name() == value_type(group)) {
            search_choice = GetCorrectNumValue("Parameter (1 - by name, 2 - by status, 3 - all): ", 0, 3,
                "**The number must be in the range 0..2, please repeat\n");
        }
        else if (typeid(Station).name() == value_type(group)) {
            search_choice = GetCorrectNumValue("Parameter (1 - by name, 2 - by percentage of unworking workshops, 3 - all): ", 0, 3,
                "**The number must be in the range 0..2, please repeat\n");
        }
        switch (search_choice) {
        case 1: {
            std::cout << "Name: ";
            std::string str;
            std::getline(std::cin, str);
            std::unordered_set<int> unordered_IDs = SearchByFilter(group, check_by_name, str);
            std::set<std::pair<std::string, int>> name_id_set;
            for (auto& id : unordered_IDs) {
                name_id_set.insert({ group.at(id).get_name(), id });
            }
            for (auto& [name, id] : name_id_set) {
                IDs.insert(id);
            }
            break;
        }
        case 2: {
            if (typeid(Pipe).name() == value_type(group)) {
                bool status = GetCorrectNumValue("Status (1 - work, 0 - in repair): ", -1, 1,
                    "**The number must be 0 or 1, please repeat\n");
                std::unordered_set<int> unordered_IDs = SearchByFilter(pipes, check_by_status, status);
                std::set<std::pair<bool, int>> status_id_set;
                for (auto& id : unordered_IDs) {
                    status_id_set.insert({ pipes.at(id).status, id });
                }
                for (auto& [status, id] : status_id_set) {
                    IDs.insert(id);
                }
            }
            else if (typeid(Station).name() == value_type(group)) {
                double perc = GetCorrectNumValue("Enter percentage of unworking workshops: ", 0, 100,
                    "**The number must be in range 0..100, please repeat\n");
                std::unordered_set<int> unordered_IDs = SearchByFilter(stations, check_by_unworking_workshops, perc);
                std::set<std::pair<double, int>, std::greater<std::pair<double, int>>> perc_id_set;
                for (auto& id : unordered_IDs) {
                    perc_id_set.insert({ stations.at(id).get_unused(), id });
                }
                for (auto& [perc, id] : perc_id_set) {
                    IDs.insert(id);
                }
            }
            break;
        }
        case 3: {
            for (auto& [id, obj] : group) {
                IDs.insert(id);
            }
            break;
        }
        }
        return IDs;
    }
    else {
        return std::unordered_set<int>{};
    }
}

template<typename T>
void App::short_view(std::unordered_map<int, T>& group) const {
    if (!is_empty(group)) {
        if (typeid(Pipe).name() == value_type(group)) {
            std::set<std::pair<bool, int>> status_id_set;
            for (auto& [id, p] : pipes) {
                status_id_set.insert({ p.status, id });
            }
            for (auto& [status, id] : status_id_set) {
                std::cout << "id::" << id
                    << " | name - " << pipes.at(id).get_name()
                    << " | status - " << pipes.at(id).get_status() << std::endl;
            }
        }
        else if (typeid(Station).name() == value_type(group)) {
            std::set<std::pair<double, int>, std::greater<std::pair<double, int>>> perc_id_set;
            for (auto& [id, s] : stations) {
                perc_id_set.insert({ s.get_unused(), id });
            }
            for (auto& [perc, id] : perc_id_set) {
                std::cout << "id::" << id
                    << " | name - " << stations.at(id).get_name()
                    << " | " << stations.at(id).get_ratio_workshops_in_work()
                    << " (" << perc << "% unused)" << std::endl;
            }
        }
        std::cout << "\n";
    }
}

template<typename T>
void App::short_view(std::unordered_map<int, T>& group, const std::unordered_set<int>& IDs) const {
    if (!is_empty(group)) {
        if (typeid(Pipe).name() == value_type(group)) {
            for (auto& id : IDs) {
                std::cout << "id::" << id
                    << " | name - " << pipes.at(id).get_name()
                    << " | status - " << pipes.at(id).get_status() << std::endl;
            }
        }
        else if (typeid(Station).name() == value_type(group)) {
            for (auto& id : IDs) {
                std::cout << "id::" << id
                    << " | name - " << stations.at(id).get_name()
                    << " | " << stations.at(id).get_ratio_workshops_in_work()
                    << " (" << stations.at(id).get_unused() << "% unused)" << std::endl;
            }
        }        
        std::cout << "\n";
    }
}

template<typename T>
void App::edit_one_from(std::unordered_map<int, T>& group) {
    if (!is_empty(group)) {
        std::cout << "\nExisting Objects:\n\n";
        short_view(group);
        int ID = GetCorrectID(pipes);
        
        if (typeid(Pipe).name() == value_type(group)) {
            auto& p = pipes.at(ID);
            std::cout << p;
            bool agree = GetCorrectYesNoValue<bool>("Want to change the status of this pipe? (Y/n): ");
            if (agree) {
                p.change_status();
                std::cout << p;
            }
        }
        else if (typeid(Station).name() == value_type(group)) {
            auto& s = stations.at(ID);
            std::cout << s;
            int choice = GetCorrectNumValue("Want to start(1) or stop(0) the workshop?: ", -1, 1,
                "**The number must be 0 or 1, please repeat\n");
            switch (choice) {
            case 0: {
                s.stop_workshop();
                break;
            }
            case 1: {
                s.start_workshop();
                break;
            }
            }
            std::cout << s;
        }
        changed = true;
    }
}

template<typename T>
void App::edit_mult_from(std::unordered_map<int, T>& group) {
    if (!is_empty(group)) {
        auto IDs = get_objs_by_filter(group);
        if (IDs.empty()) {
            std::cout << "\n*There are no such objects\n";
            return;
        }
        std::cout << "\nSelected Objects:\n\n";
        short_view(group, IDs);

        int choice1 = GetCorrectNumValue("Do you want to edit all(1) or just some(0)?: ", -1, 1,
            "**The number must be 0 or 1, please repeat\n");
        std::unordered_set<int> selected_IDs;
        if (choice1 == 1) selected_IDs = IDs;
        else {
            std::cout << "Select some IDs: ";
            int id = -1;
            while (std::cin.peek() != '\n') {
                std::cin >> id;
                if (group.contains(id)) {
                    selected_IDs.insert(id);
                }
                else {
                    std::cout << "id::" << id << " *No such id exists\n";
                }
            }
            std::cout << "\n";
            short_view(group, selected_IDs);
        }

        if (selected_IDs.empty()) return;

        if (typeid(Pipe).name() == value_type(group)) {
            int choice2 = GetCorrectNumValue("Want to change all statuses to \"in work\"(1), to \"in repair\"(-1) or to reverse(0)?: ", -2, 1,
                "**The number must be -1, 0 or 1, please repeat\n");
            switch (choice2) {
            case -1: {
                for (auto& id : selected_IDs) {
                    pipes.at(id).status = false;
                }
                break;
            }
            case 0: {
                for (auto& id : selected_IDs) {
                    pipes.at(id).change_status();
                }
                break;
            }
            case 1: {
                for (auto& id : selected_IDs) {
                    pipes.at(id).status = true;
                }
                break;
            }
            }
        }
        else if (typeid(Station).name() == value_type(group)) {
            int choice2 = GetCorrectNumValue("Want to start(1) or stop(0) the workshop?: ", -1, 1,
                "**The number must be -1, 0 or 1, please repeat\n");
            switch (choice2) {
            case 0: {
                for (auto& id : IDs) {
                    stations.at(id).stop_workshop();
                }
                break;
            }
            case 1: {
                for (auto& id : IDs) {
                    stations.at(id).start_workshop();
                }
                break;
            }
            }
        }
        std::cout << "\n";
        short_view(group, IDs);
        changed = true;
    }
}

template<typename T>
void App::remove_from(std::unordered_map<int, T>& group) {
    if (!is_empty(group)) {
        std::cout << "\nExisting Pipes:\n\n";
        short_view(group);
        int ID = GetCorrectID(group);
        std::cout << group.at(ID);
        bool agree = GetCorrectYesNoValue<bool>("Want to remove this object? (Y/n): ");
        if (agree) {
            group.erase(ID);
            std::cout << "\n*Object was deleted\n";
        }
        changed = true;
    }
}

template<typename T>
void App::add_to(std::unordered_map<int, T>& group) {
    T obj;
    std::cin >> obj;
    group.insert({ obj.get_id(), obj });
    empty = false;
    changed = true;
}

template<typename T>
void App::edit(std::unordered_map<int, T>& group) {
    if (!is_empty(group)) {
        std::cout << "\n";
        int choice = GetCorrectNumValue("Parameter (1 - edit one object, 2 - batch editing, 0 - remove): ", -1, 2,
            "**The number must be 0, 1 or 2, please repeat\n");
        switch (choice) {
        case 0: {
            remove_from(group);
            break;
        }
        case 1: {
            edit_one_from(group);
            break;
        }
        case 2: {
            edit_mult_from(group);
            break;
        }
        }
        changed = true;
    }
}

template<typename T>
void App::view(std::unordered_map<int, T>& group) const {
    if (!is_empty(group)) {
        for (auto& [id, obj] : group) {
            std::cout << obj;
        }
    }
}

template<typename T>
void App::search(std::unordered_map<int, T>& group) {
    if (!is_empty(group)) {
        std::cout << "\n";
        std::unordered_set<int> IDs = get_objs_by_filter(group);
        if (!IDs.empty()) {
            for (auto& id : IDs) {
                std::cout << group.at(id);
            }
        }
        else {
            std::cout << "\n*There are no such objects\n";
        }
    }
}
