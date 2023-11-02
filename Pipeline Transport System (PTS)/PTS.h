#pragma once
#include "Pipe.h"
#include "Station.h"
#include "Utilities.h"
#include <string>
#include <unordered_map>


class PTS
{
public:

	enum ObjectType { PIPE, STATION };
	std::string to_string(const ObjectType) const;
	void add(const ObjectType);
	void remove(const ObjectType, const int);
	void view(const ObjectType, const std::unordered_set<int>&) const;
	void short_view(const ObjectType, const std::unordered_set<int>&) const;

	void edit(const std::unordered_set<int>&, const Pipe::EditStatusType);
	void edit(const std::unordered_set<int>&, const Station::EditWSType);

	template <typename T>
	std::unordered_set<int> search(filter<Pipe, T>, const T) const;
	template <typename T>
	std::unordered_set<int> search(filter<Station, T>, const T) const;

	std::unordered_set<int> get_ids_objects(const ObjectType) const;

	bool empty() const;
	bool has_saved_file() const;
	bool saved() const;
	void set_save_directory(const std::string);
	void set_filename(const std::string);

	void save_to_file();
	void load_from_file();

private:

	std::unordered_map<int, Pipe> pipes{};
	std::unordered_map<int, Station> stations{};

	void clear_system();
	bool changed = false;
	std::string file_name = "";
	std::string directory = "";
	
};

bool check_pipe_by_name(const Pipe&, const std::string);
bool check_pipe_by_status(const Pipe&, const bool);
bool check_station_by_name(const Station&, const std::string);
bool check_station_by_unactive_workshops(const Station&, const double);

template <typename T>
std::unordered_set<int> PTS::search(filter<Pipe, T> f, const T par) const {
	return search_by_filter(pipes, f, par);
}

template <typename T>
std::unordered_set<int> PTS::search(filter<Station, T> f, const T par) const {
	return search_by_filter(stations, f, par);
}
