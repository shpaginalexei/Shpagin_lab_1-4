#pragma once
#include "Pipe.h"
#include "Station.h"
#include "Utilities.h"
#include <string>
#include <unordered_map>
#include <type_traits>


class PTS
{
public:

	enum GroupType { PIPES, STATIONS, UNKNOWN };
	void add_to(const GroupType);
	void remove_from(const GroupType, const int);
	void view(const GroupType, const std::unordered_set<int>&) const;
	void short_view(const GroupType, const std::unordered_set<int>&) const;

	template <PTS::GroupType type, typename T>
	void edit(const std::unordered_set<int>&, const T, std::enable_if_t<type == PIPES>* = nullptr);
	template <PTS::GroupType type, typename T>
	void edit(const std::unordered_set<int>&, const T, std::enable_if_t<type == STATIONS>* = nullptr);

	template <PTS::GroupType type, typename T2>
	std::unordered_set<int> search(const T2, filter<Pipe, T2>, std::enable_if_t<type == PIPES>* = nullptr);
	template <PTS::GroupType type, typename T2>
	std::unordered_set<int> search(const T2, filter<Station, T2>, std::enable_if_t<type == STATIONS>* = nullptr);

	std::unordered_set<int> get_group_ids(GroupType) const;

	bool empty = true;
	bool changed = false;
	bool saved = false;
	std::string file_name = "";

	void save_to_file();
	void load_from_file();

private:
	std::unordered_map<int, Pipe> pipes{};
	std::unordered_map<int, Station> stations{};
	const std::string path = ".saves\\";
};

std::string to_string(PTS::GroupType);

bool check_pipe_by_name(Pipe&, std::string);
bool check_pipe_by_status(Pipe&, bool);
bool check_station_by_name(Station&, std::string);
bool check_station_by_unactive_workshops(Station&, double);

template<PTS::GroupType type, typename T>
void PTS::edit(const std::unordered_set<int>& IDs, const T editType, std::enable_if_t<type == PIPES>*) {
	for (auto& id : IDs) { pipes.at(id).change_status(editType); }
	changed = true;
}

template<PTS::GroupType type, typename T>
void PTS::edit(const std::unordered_set<int>& IDs, const T editType, std::enable_if_t<type == STATIONS>*) {
	for (auto& id : IDs) { stations.at(id).change_num_active_workshops(editType); }
	changed = true;
}

template <PTS::GroupType type, typename T2>
std::unordered_set<int> PTS::search(const T2 par, filter<Pipe, T2> f,
	std::enable_if_t<type == PIPES>*) {
	return search_by_filter(pipes, f, par);
}

template <PTS::GroupType type, typename T2>
std::unordered_set<int> PTS::search(const T2 par, filter<Station, T2> f,
	std::enable_if_t<type == STATIONS>*) {
	return search_by_filter(stations, f, par);
}
