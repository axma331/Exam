#pragma once

#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include <map>

class Warlock
{
private:
	std::string _name;
	std::string _title;

	std::map<std::string, ASpell *> map;

public:
	Warlock(std::string name, std::string title) {
		_name = name;
		_title = title;
		std::cout << _name << ": This looks like another boring day.\n";
	}

	~Warlock() {
		std::cout << _name << ": My job here is done!\n";
	}

	std::string const &getName() { return _name; };
	std::string const &getTitle() { return _title; };

	void setTitle(std::string const &title) {
		_title = title;
	}

	void introduce() {
		std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
	}

	void learnSpell(ASpell *aspell_ptr) {
		map[aspell_ptr->getName()] = aspell_ptr;
	}

	void forgetSpell(std::string name) {
		map.erase(name);
	}

	void launchSpell(std::string name, ATarget &atarget_ref) {
		if (map[name] != 0)
			map[name]->launch(atarget_ref);
	}
};
