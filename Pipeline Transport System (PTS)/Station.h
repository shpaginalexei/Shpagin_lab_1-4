#pragma once
#include <string>


class Station
{
public:
	
	Station();
	
	static void reset_max_id();
	static int get_max_id();

	int get_id() const;
	std::string get_name() const;
	double get_unused_workshops() const;
	std::string get_ratio_workshops() const;

	enum EditWSType { START_ONE_WS, STOP_ONE_WS };
	void change_num_active_workshops(const EditWSType);

	friend std::istream& operator>> (std::istream&, Station&);
	friend std::ostream& operator<< (std::ostream&, const Station&);

	friend std::ifstream& operator>> (std::ifstream&, Station&);
	friend std::ofstream& operator<< (std::ofstream&, const Station&);

private:
	static int max_id;
	int id;
	std::string name = "";
	int workshops = 0;
	int active_workshops = 0;
	double efficiency = 0.0;
};
