#pragma once
#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include <map>
#include "SpellBook.hpp"

class Warlock {
	std::string	_name;
	std::string	_title;
	SpellBook	book;
public:
	Warlock(const std::string& name, const std::string title) 
		: _name(name), _title(title) {
		std::cout << _name << ": This looks like another boring day.\n";
	}
	~Warlock() {std::cout << _name << ": My job here is done!\n";}
	const std::string&	getName() const {return _name;}
	const std::string&	getTitle() const {return _title;}
	void	setTitle(const std::string&	title) {_title = title;}
	void	introduce() const {
		std::cout << _name << ": I am " << _name << ", "<< _title << "!\n";}
	void	learnSpell(ASpell* spell) {
		book.learnSpell(spell);
	}
	void	forgetSpell(const std::string& name) {
		book.forgetSpell(name);
	}
	void	launchSpell(const std::string& name, ATarget& target) {
		ASpell* spell = book.createSpell(name);
		if (spell)
			spell->launch(target);
	}
};