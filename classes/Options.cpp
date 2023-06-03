#include "Options.h"
#include<iostream>

Options::Options()
{
}

int Options::update(sf::RenderWindow &window)
{	
	sf::Font menuFont;
	sf::Text menuText[5], volumeTxt, sel;
	int n; //row, col, bombs
	
		
	{	
		std::ifstream getVol;
		getVol.open("bin/volume", std::fstream::in | std::fstream::binary);
		if(getVol)
		{
			getVol.read(reinterpret_cast<char*>(&n), sizeof(int));
			getVol.close();
		}
		else
		{
			n=50;			
		}
	}
	
	
	if(!menuFont.loadFromFile("fonts/munro.ttf"))
		std::cout<<"error: missing main menu font";

	volumeTxt.setFont			( menuFont );
	volumeTxt.setCharacterSize	( 45 );
	volumeTxt.setString			( std::to_string( n ) );
	volumeTxt.setPosition		( window.getSize().x/2, window.getSize().y * ( 45/100.0 + (1*61/400.0) ) );
	volumeTxt.setFillColor		( sf::Color(80,255,124) );
	volumeTxt.setOutlineThickness( 2 );
	volumeTxt.setOrigin			( volumeTxt.getGlobalBounds().width / 2, 0 );

	sel.setString( "BACK" );
	sel.setFont				( menuFont );
	sel.setCharacterSize		( 60 );
	sel.setPosition			( window.getSize().x * (40/100.0 + 0.5 *20/100.0), window.getSize().y * 85/100.0 );
	sel.setFillColor			( sf::Color(80,255,124) );
	sel.setOutlineThickness	( 3 );
	sel.setOrigin			( sel.getGlobalBounds().width / 2, 0 );

	
	//menu initialization
	
	for(int i=0;i<5;i++)
		menuText[i].setFont(menuFont);
	
	
	menuText[0].setString("(--)");
	menuText[1].setString("(-)");
	menuText[2].setString("VOLUME");
	menuText[3].setString("(+)");
	menuText[4].setString("(++)");

	
	Menu menu;
	menu.remakeTxt(&window, menuText, false, false, true, 1, 5, sf::FloatRect(0/100.0, 25/100.0, 100/100.0, 65/100.0), 2);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////// MAIN LOOP ////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	while (window.isOpen())
    {   
		//highlights PLAY and BACK
		for(int i=0; i<2; i++)
		{
			if( sf::IntRect(sel.getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
			{
				if( sel.getFillColor() != sf::Color(175,255,220) )
					sel.setFillColor(sf::Color(175,255,220));	
			}
			else if( sel.getFillColor() != sf::Color(80,255,124) )
				sel.setFillColor(sf::Color(80,255,124));
		}

			
		
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
			      		//BACK
						if( sf::IntRect(sel.getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
						{
							std::ofstream ofile;
							
							ofile.open ("bin/volume", std::fstream::out | std::fstream::trunc | std::fstream::binary);
							ofile.write( reinterpret_cast<const char*>(&n), sizeof(int) );
							ofile.close();
							
							return 0; //menu
						}

						switch ( menu.getSelected(sf::Mouse::getPosition(window)) )
						{	//always respect n[0]*n[1] >= n[2]+10
							case 0: // --vol
								n = ((n>10) ? n-10 : 0);
								break;
							case 1: // -vol
								n = ((n>1) ? n-1 : 0);
								break;
							case 2: // set vol
								n = 50;
								break;
							case 3: // + vol
								n = ((n<99) ? n+1 : 100);
								break;
							case 4: // ++vol
								n = ((n<90) ? n+10 : 100);
								break;
							default:
								break;
						}
						if( menu.getSelected(sf::Mouse::getPosition(window)) != -1 )
						{
							sf::Listener::setGlobalVolume(n);
							volumeTxt.setString( std::to_string( n ) );
							volumeTxt.setOrigin(volumeTxt.getGlobalBounds().width / 2, 0 );
						}
						break;
					case sf::Keyboard::Escape:
						{
							std::ofstream ofile;
							ofile.open ("bin/volume", std::fstream::out | std::fstream::trunc | std::fstream::binary);
							ofile.write( reinterpret_cast<const char*>(&n), sizeof(int) );
							ofile.close();
						}
						return 0; //menu
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
						//Back
						if( sf::IntRect(sel.getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
						{
							std::ofstream ofile;
							
							ofile.open ("bin/volume", std::fstream::out | std::fstream::trunc | std::fstream::binary);
							ofile.write( reinterpret_cast<const char*>(&n), sizeof(int) );
							ofile.close();
							
							return 0; //menu
						}
						
						switch ( menu.getSelected(sf::Mouse::getPosition(window)) )
						{	//always respect n[0]*n[1] >= n[2]+10
							
							case 0: // --vol
								n = ((n>10) ? n-10 : 0);
								break;
							case 1: // -vol
								n = ((n>1) ? n-1 : 0);
								break;
							case 2: // set vol
								n = 50;
								break;
							case 3: // + vol
								n = ((n<99) ? n+1 : 100);
								break;
							case 4: // ++vol
								n = ((n<90) ? n+10 : 100);
								break;
							default:
								break;
						}
						if( menu.getSelected(sf::Mouse::getPosition(window)) != -1 )
						{
							sf::Listener::setGlobalVolume(n);
							volumeTxt.setString( std::to_string( n ) );
							volumeTxt.setOrigin(volumeTxt.getGlobalBounds().width / 2, 0 );
						}
						break;
					default:
						break;
				}
			}
        }
        
        window.clear();
        
        menu.draw(sf::Mouse::getPosition(window));
        
        window.draw(volumeTxt);
        
        for(int i=0; i<2; i++)
        	window.draw(sel);
		
        window.display();
    }
    return (-1);
	
}
