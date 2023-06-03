#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <fstream>
#include "screens.hpp"

class Leaderboard : public screenSwitch
{
	public:
		Leaderboard();
		virtual int update(sf::RenderWindow &window);
	protected:
};

#endif
