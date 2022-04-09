#pragma once

#include <iostream>
#include "SpellBook.hpp"
#include "ATarget.hpp"
#include "ASpell.hpp"

class Warlock {
private:
	std::string _name;
	std::string _title;

	SpellBook book;

public:
	Warlock(std::string name, std::string title) {
		this->_name = name;
		this->_title = title;
		std::cout << _name << ": This looks like another boring day.\n";
	}

	~Warlock() {
		std::cout << _name << ": My job here is done!\n";
	}

	std::string getName() { return _name; }
	std::string getTitle() { return _title; }

	void setTitle(std::string title) { _title = title; }

	void introduce() {
		std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
	}

	void learnSpell(ASpell *aspell_ptr) {
		book.learnSpell(aspell_ptr);
	}

	void forgetSpell(std::string name) {
		book.forgetSpell(name);
	}

	void launchSpell(std::string name, ATarget &atarget_ref) {
		ASpell *temp = book.createSpell(name);
		if (temp)
			temp->launch(atarget_ref);
	}
};

