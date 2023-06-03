#ifndef MAINMENU_H
#define MAINMENU_H
#include "screens.hpp"
#include "Field.h"

class MainMenu : public screenSwitch
{
	public:
		MainMenu();
		virtual int update(sf::RenderWindow &window);
	private:
};

#endif
