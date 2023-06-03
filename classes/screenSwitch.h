#ifndef SCREENSWITCH_H
#define SCREENSWITCH_H
#include <SFML/Graphics.hpp>
#include "Field.h"

class screenSwitch
{
	public:
		virtual int update(sf::RenderWindow &window)=0;
	protected:
};

#endif
