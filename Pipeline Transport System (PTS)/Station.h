#pragma once
#include <string>


class Station
{
public:
	static int max_id;
	
	Station();

	int get_id() const;
	int get_workshop() const;
	int get_workshop_in_work() const;

	void start_workshop();
	void stop_workshop();

	friend std::istream& operator>> (std::istream&, Station&);
	friend std::ostream& operator<< (std::ostream&, const Station&);

	friend std::ifstream& operator>> (std::ifstream&, Station&);
	friend std::ofstream& operator<< (std::ofstream&, const Station&);

private:
	int id;
	std::string name = "";
	int workshops = 0;
	int workshops_in_work = 0;
	double efficiency = 0.0;
};
