#ifndef DIFFICULTY_H
#define DIFFICULTY_H
#include <fstream>
#include "screens.hpp"

class Difficulty : public screenSwitch
{
	public:
		Difficulty(void);
		virtual int update(sf::RenderWindow &window);
	protected:
};

#endif
