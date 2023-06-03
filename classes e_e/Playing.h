#ifndef PLAYING_H
#define PLAYING_H
#include "screens.hpp"
#include "Menu.h"
#include <SFML/Graphics.hpp>

class Playing:public screenSwitch
{
	public:
		Playing(void);
		virtual int update(sf::RenderWindow &window);
	private:
		Menu lowMenu, txtMenu;
		int state, oldState;
		sf::Text txtMenuText[8];
		sf::Text lowMenuText[5];
		sf::Font lowMenuFont;
		Character player;
};

#endif
