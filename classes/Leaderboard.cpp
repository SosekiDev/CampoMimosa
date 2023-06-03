#include "Leaderboard.h"
#include <iostream>

Leaderboard::Leaderboard()
{
}

int Leaderboard::update(sf::RenderWindow &window)
{
	int wintime[3][10];
	
	//reads wintime
	std::ifstream lbIn;
	lbIn.open("bin/leaderboard", std::fstream::in | std::fstream::binary);
	if(!lbIn)
	{	//creates default leaderbord
		int defaultLeaderbord = 0;
		std::ofstream lbOut;	
		lbOut.open ("bin/leaderboard", std::fstream::out | std::fstream::trunc | std::fstream::binary);
		for(int i=0; i<30; i++)
			lbOut.write( reinterpret_cast<const char*>(&defaultLeaderbord), sizeof(int) );
		lbOut.close();
		return 4;
	}
	else
	{
		for(int i=0; i<30; i++)
			lbIn.read(reinterpret_cast<char*>(&wintime[i/10][i%10]), sizeof(int));
		lbIn.close();
	}
	
	
	sf::Font lbFont;
	if(!lbFont.loadFromFile("fonts/munro.ttf"))
		std::cout<<"error: missing main menu font";
	
	sf::Text lbText[3][21];
	for(int i=0; i<3; i++)
	{
		lbText[i][0].setFont(lbFont);
		lbText[i][20].setFont(lbFont);
		
		lbText[i][0].setString("1.");
		lbText[i][1].setString("2.");
		lbText[i][2].setString("3.");
		lbText[i][3].setString("4.");
		lbText[i][4].setString("5.");
		lbText[i][5].setString("6.");
		lbText[i][6].setString("7.");
		lbText[i][7].setString("8.");
		lbText[i][8].setString("9.");
		lbText[i][9].setString("10.");
		
		for(int j=10; j<20; j++)
		{
			if( wintime[i][j-10] > 0 )
				lbText[i][j].setString(std::to_string( wintime[i][j-10] / 1000 ));
			else lbText[i][j].setString("---");
		}
	}
	
	lbText[0][20].setString("EASY");
	lbText[1][20].setString("NORMAL");
	lbText[2][20].setString("HARD");

	
	Menu lbMenu[3];
	for(int i=0; i<3; i++)
		lbMenu[i].remakeTxt(&window, lbText[i], true, true, false, 10, 2, sf::FloatRect((4+i*32)/100.0, 5/100.0, 28/100.0, 90/100.0), 0);
		
	Menu back;
	back.remakeBack(&window, 93/100.f, 94.2/100.f, sf::Color(80,255,124), sf::Color(180,255,224), 2, sf::Color(18,89,29));
	
	
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
			      		if(back.getSelected(sf::Mouse::getPosition(window)) == 0)
							return 0;
						break;
					case sf::Keyboard::Escape:
						return 0;
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
						if(back.getSelected(sf::Mouse::getPosition(window)) == 0)
							return 0;
						break;
					default:
						break;
				}
			}
        }
        
        window.clear();

        for(int i=0; i<3; i++)
        	lbMenu[i].draw( sf::Mouse::getPosition(window) );
		back.draw(sf::Mouse::getPosition(window));
		
    	window.display();
	}
    return (-1);
	
}
