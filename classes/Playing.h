#ifndef PLAYING_H
#define PLAYING_H
#include "screens.hpp"
#include "Field.h"


class Playing:public screenSwitch
{
	public:
		Playing(void);
		virtual int update(sf::RenderWindow &window);
		
	private:
		sf::Music bgMusic;
		
};

#endif
