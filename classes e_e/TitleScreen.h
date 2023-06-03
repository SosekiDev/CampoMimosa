#ifndef TITLESCREEN_H
#define TITLESCREEN_H
#include "screens.hpp"
#include "Menu.h"
#include <SFML/Graphics.hpp>

class TitleScreen:public screenSwitch
{
	public:
		TitleScreen(void);
		virtual int update(sf::RenderWindow &window);
	private:
		Menu menu;
};

#endif
