#pragma once
#include <string>


class Pipe
{
public:
	static int max_id;
	bool status = false;

	Pipe();

	int get_id() const;
	std::string get_name() const;
	std::string get_status() const;

	enum class StatusType { WORK, IN_REPAIR, OPPOSITE, UNKNOWN };
	void change_status(StatusType);

	friend std::istream& operator>> (std::istream&, Pipe&);
	friend std::ostream& operator<< (std::ostream&, const Pipe&);

	friend std::ifstream& operator>> (std::ifstream&, Pipe&);
	friend std::ofstream& operator<< (std::ofstream&, const Pipe&);
	
private:
	int id;
	std::string name = "";
	double lenght = 0;
	int diameter = 0;	
};

