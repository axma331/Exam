#pragma once
#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include <map>

class Warlock {
	std::string	_name;
	std::string	_title;
	std::map<std::string, ASpell*>	map;

public:
	Warlock(std::string name, std::string title) : _name(name), _title(title) {
		std::cout << _name << ": This looks like another boring day.\n";
	}
	~Warlock() {std::cout << _name << ": My job here is done!\n";}

	const std::string&	getName() {return _name;};
	const std::string&	getTitle() {return _title;};

	void setTitle(const std::string& title) {
		_title = title;
	}

	void introduce() {
		std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
	}

	void learnSpell(ASpell *spell) {
		map[spell->getName()] = spell;
	}
	void forgetSpell(std::string name) {
		map.erase(name);
	}
	void launchSpell(std::string name, ATarget &target) {
		if (map[name] != 0)
			map[name]->launch(target);
	}
};
