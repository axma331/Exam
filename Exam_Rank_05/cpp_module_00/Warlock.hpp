#pragma once

#include <iostream>

class Warlock {
private:
	std::string _name;
	std::string _title;

public:
	Warlock (std::string name, std::string title) {
		_name = name;
		_title = title;
		std::cout << _name << ": This looks like another boring day.\n";
	}

	~Warlock() {
		std::cout << _name << ": My job here is done!\n";
	}

	std::string getName() const { return _name; }
	std::string getTitle() const { return _title; }

	void setTitle (std::string title) {
		_title = title;
	}

	void introduce() const {
		std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
	}
};

