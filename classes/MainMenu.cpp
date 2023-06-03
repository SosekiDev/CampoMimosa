#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
}

int MainMenu::update(sf::RenderWindow &window)
{
	sf::Texture bgTex, extraTex;
	if(!bgTex.loadFromFile("img/fundomanero.png"))
		std::cout<<"Error loading background\n";
	
	sf::Sprite bgSprite, extraSprite;
	bgSprite.setTexture(bgTex);
	bgSprite.setScale(1.0*window.getSize().x / bgTex.getSize().x, 1.0*window.getSize().y / bgTex.getSize().y);
	
	int state=0; //0=menu, 1=tutorial, 2=credits
	
	sf::Font menuFont;
	if(!menuFont.loadFromFile("fonts/munro.ttf"))
		std::cout<<"error: missing main menu font";
	
	sf::Text menuText[8];
	for(int i=0;i<8;i++)
		menuText[i].setFont(menuFont);

	menuText[0].setString("Play");
	menuText[1].setString("How to play + Commands");
	menuText[2].setString("Leaderboard");
	menuText[3].setString("Options");
	menuText[4].setString("Credits");
	menuText[5].setString("Exit");
	
	menuText[6].setString("Campo Mimosa");
	menuText[7].setString("Mimosa Field");
	menuText[6].setCharacterSize(100);
	menuText[7].setCharacterSize(25);
	menuText[6].setFillColor( sf::Color(124,255,80) );
	menuText[7].setFillColor( sf::Color(124,255,80) );
	menuText[6].setOutlineThickness(5);
	menuText[7].setOutlineThickness(3);
	menuText[6].setOutlineColor( sf::Color(31,87,8) );
	menuText[7].setOutlineColor( sf::Color(31,87,8) );
	menuText[6].setOrigin( menuText[6].getGlobalBounds().width/2, 0 );
	menuText[7].setOrigin( menuText[7].getGlobalBounds().width/2, 0 );
	menuText[6].setPosition( window.getSize().x/2, 20 );
	menuText[7].setPosition( window.getSize().x/2, menuText[6].getGlobalBounds().height + 30 );
	
	Menu menu;
	menu.remakeTxt(&window, menuText, false, false, true, 6, 1, sf::FloatRect(5/100.0, 30/100.0, 90/100.0, 73/100.0), 2);
	
	Menu back;	
	
	while (window.isOpen())
    {
    	
		///////////////////////////////////// EVENT LOOP /////////////////////////////////////////////
        sf::Event event;
        while (window.pollEvent(event))
        {
        	if (event.type==sf::Event::Closed)
                return(-1);
            if (event.type==sf::Event::KeyPressed)
		    {
				switch(event.key.code)
				{
			    	case sf::Keyboard::Return:
			      		if(!state)
						switch ( menu.getSelected(sf::Mouse::getPosition(window)) )
						{
							case 0: //play
								return 1;
								break;
							case 1: //how to play + commands
							{
								if(!extraTex.loadFromFile("img/tutorial.png"))
									std::cout<<"Error loading tutorial\n";
								extraSprite.setTexture( extraTex );
								extraSprite.setScale(1.0*window.getSize().x / extraTex.getSize().x, 1.0*window.getSize().y / extraTex.getSize().y);
								
								back.remakeBack(&window, 68/100.f, 93/100.f, sf::Color(130,184,243), sf::Color(160,224,255), 2, sf::Color(12,30,87) );
								
								state = 1;
								break;
							}
							case 2: //leaderboards
								return 4;
								break;
							case 3: //options
								return 5;
								break;
							case 4: //credits
								back.remakeBack(&window, 70/100.f, 92/100.f, sf::Color(100,243,164), sf::Color(130,255,194), 2, sf::Color(12,87,30) );
								menu.featureDisabled(sf::Mouse::getPosition(window));
								break;
							case 5: //exit
								return -1;
								break;
							default:
								break;
						}
						else if(state && back.getSelected(sf::Mouse::getPosition(window)) == 0 )//tutorial
							return 0;
						break;
					case sf::Keyboard::Escape:
						if(!state)
							return -1;
						else return 0;
						break;
					default:
						break;
		   		}
			}
			if (event.type==sf::Event::MouseButtonPressed)
			{
				switch(event.mouseButton.button)
				{	
					case sf::Mouse::Left:
						if(!state)
						switch ( menu.getSelected(sf::Mouse::getPosition(window)) )
						{
							case 0: //play
								return 1;
								break;
							case 1: //how to play + commands
							{
								if(!extraTex.loadFromFile("img/tutorial.png"))
									std::cout<<"Error loading tutorial\n";
								extraSprite.setTexture( extraTex );
								extraSprite.setScale(1.0*window.getSize().x / extraTex.getSize().x, 1.0*window.getSize().y / extraTex.getSize().y);
								
								back.remakeBack(&window, 68/100.f, 93/100.f, sf::Color(130,184,243), sf::Color(160,224,255), 2, sf::Color(12,30,87) );
								
								state = 1;
								break;
							}
							case 2: //leaderboards
								return 4;
								break;
							case 3: //options
								return 5;
								break;
							case 4: //credits
								back.remakeBack(&window, 70/100.f, 92/100.f, sf::Color(100,243,164), sf::Color(130,255,194), 2, sf::Color(12,87,30) );
								menu.featureDisabled(sf::Mouse::getPosition(window));
								break;
							case 5: //exit
								return -1;
								break;
							default:
								break;
						}
						else if(state && back.getSelected(sf::Mouse::getPosition(window)) == 0 )//tutorial
							return 0;
						break;
					default:
						break;
				}
			}
        }
        
        window.clear();
    	
    	if(state)
    	{
    		window.draw(extraSprite);
    		back.draw(sf::Mouse::getPosition(window));
		}
		else
		{
		   	window.draw(bgSprite);
			menu.draw( sf::Mouse::getPosition(window) );
			window.draw(menuText[6]);
			window.draw(menuText[7]);
		}
		
    	window.display();
	}
    return -1;
	
}
