#pragma once
#include <iostream>
#include "SpellBook.hpp"
#include "ATarget.hpp"
#include "ASpell.hpp"

class Warlock {
	std::string _name;
	std::string _title;
	SpellBook book;
public:
	Warlock(std::string name, std::string title) : _name(name), _title(title) {
		std::cout << _name << ": This looks like another boring day.\n";
	}
	~Warlock() {std::cout << _name << ": My job here is done!\n";}

	std::string getName() {return _name;}
	std::string getTitle() {return _title;}

	void setTitle(std::string title) {_title = title;}
	void introduce() {
		std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
	}
	void learnSpell(ASpell *spell) {
		book.learnSpell(spell);
	}
	void forgetSpell(std::string name) {
		book.forgetSpell(name);
	}
	void launchSpell(std::string name, ATarget &target) {
		ASpell *temp = book.createSpell(name);
		if (temp)
			temp->launch(target);
	}
};

