#include "TitleScreen.h"
#include<iostream>

TitleScreen::TitleScreen(void)
{
	
}

int TitleScreen::update(sf::RenderWindow &window)
{
	
	sf::Font mainMenuFont;
	if(!mainMenuFont.loadFromFile("fonts/Adventurer.ttf"))
		return (-1);
	
	sf::Text mainMenuText[4];
	for(int i=0;i<4;i++)
	{
		mainMenuText[i].setFont(mainMenuFont);
		mainMenuText[i].setCharacterSize(DEFAULT_SIZE);
	}
	mainMenuText[0].setString("Play");
	mainMenuText[1].setString("Options");
	mainMenuText[2].setString("Exit");
	//title
	mainMenuText[3].setString("Elemental Witches");

	
	menu.remake(window.getSize().x,window.getSize().y,3,1,mainMenuText,3,3,97,97,true,true,true,false,3,27,97,97,true);
	
	
	while (window.isOpen())
    {      
        sf::Event event;
        while (window.pollEvent(event))
        {
        	if (event.type==sf::Event::Closed)
                return(-1);
            if (event.type==sf::Event::KeyPressed)
		    {
				switch(event.key.code)
				{
				case sf::Keyboard::Up:
					menu.moveUp();
					break;
				case sf::Keyboard::Down:
					menu.moveDown();
					break;
				case sf::Keyboard::Left:
					menu.moveLeft();
					break;
				case sf::Keyboard::Right:
					menu.moveRight();
					break;
		      	case sf::Keyboard::Return:
					switch(menu.getSelected() )
					{
					case 0:
						return (1);
						break;
					case 1:
						menu.featureDisabled(window);
						break;
					case 2:
						return (-1);
						break;
					}
					break;
				default:
					
					break;
		   		}
			}
        }
        window.clear();
        menu.draw(window);
        window.display();
    }
    return (-1);
	
}
