#ifndef CUSTOMDIFFICULTY_H
#define CUSTOMDIFFICULTY_H
#include <fstream>
#include "screens.hpp"

class CustomDifficulty : public screenSwitch
{
	public:
		CustomDifficulty(void);
		virtual int update(sf::RenderWindow &window);
	protected:
};

#endif
