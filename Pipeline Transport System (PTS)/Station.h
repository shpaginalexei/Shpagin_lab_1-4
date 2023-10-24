#pragma once
#include <string>


class Station
{
public:
	static int max_id;
	
	Station();

	int get_id() const;
	std::string get_name() const;
	double get_unused_workshops() const;
	std::string get_ratio_workshops() const;

	enum class WhatDo { START, STOP, UNKNOWN };
	void change_num_active_workshops(WhatDo);

	friend std::istream& operator>> (std::istream&, Station&);
	friend std::ostream& operator<< (std::ostream&, const Station&);

	friend std::ifstream& operator>> (std::ifstream&, Station&);
	friend std::ofstream& operator<< (std::ofstream&, const Station&);

private:
	int id;
	std::string name = "";
	int workshops = 0;
	int active_workshops = 0;
	double efficiency = 0.0;
};
