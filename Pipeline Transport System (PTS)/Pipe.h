#pragma once
#include <string>


class Pipe
{
public:

	Pipe();

	static void reset_max_id();
	static int get_max_id();

	int get_id() const;
	std::string get_name() const;
	int get_diameter() const;
	bool get_status() const;
	std::string get_status_string() const;

	enum EditStatusType { SET_WORK, SET_IN_REPAIR, SET_OPPOSITE };
	void change_status(const EditStatusType);

	friend std::istream& operator>> (std::istream&, Pipe&);
	friend std::ostream& operator<< (std::ostream&, const Pipe&);

	friend std::ifstream& operator>> (std::ifstream&, Pipe&);
	friend std::ofstream& operator<< (std::ofstream&, const Pipe&);

	static int get_correct_diameter();
	static std::string get_valid_diameters_string();

private:
	static int max_id;
	int id;
	std::string name = "";
	double lenght = 0;
	int diameter = 0;
	const static int valid_diameters[4];
	bool status = false;
};

