#ifndef OPTIONS_H
#define OPTIONS_H
#include <fstream>
#include "screens.hpp"

class Options : public screenSwitch
{
	public:
		Options();
		virtual int update(sf::RenderWindow &window);
	protected:
};

#endif
