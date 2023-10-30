#pragma once
#include <string>


class Pipe
{
public:

	Pipe();

	static void reset_max_id();

	int get_id() const;
	std::string get_name() const;
	bool get_status() const;
	std::string get_status_string() const;

	enum EditStatusType { SET_WORK, SET_IN_REPAIR, SET_OPPOSITE };
	void change_status(const EditStatusType);

	friend std::istream& operator>> (std::istream&, Pipe&);
	friend std::ostream& operator<< (std::ostream&, const Pipe&);

	friend std::ifstream& operator>> (std::ifstream&, Pipe&);
	friend std::ofstream& operator<< (std::ofstream&, const Pipe&);

private:
	static int max_id;
	int id;
	std::string name = "";
	double lenght = 0;
	int diameter = 0;
	bool status = false;
};

