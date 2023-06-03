#include "CustomDifficulty.h"
#include<iostream>

CustomDifficulty::CustomDifficulty(void)
{
}

int CustomDifficulty::update(sf::RenderWindow &window)
{	
	sf::Font menuFont;
	sf::Text menuText[21], nText[3], sel[2];
	int n[3]; //row, col, bombs
	
		
	{	std::ifstream fieldInit;
		fieldInit.open("bin/init", std::fstream::in | std::fstream::binary);
		if(fieldInit)
		{
			fieldInit.read(reinterpret_cast<char*>(&n[0]), sizeof(int));
			fieldInit.read(reinterpret_cast<char*>(&n[1]), sizeof(int));
			fieldInit.read(reinterpret_cast<char*>(&n[2]), sizeof(int));
			fieldInit.close();
		}
		else
		{
			n[0]=16; n[1]=16; n[2]=40;			
		}
	}
	
	
	if(!menuFont.loadFromFile("fonts/munro.ttf"))
		std::cout<<"error: missing main menu font";

	for(int i=0;i<3;i++)
	{
		nText[i].setFont			( menuFont );
		nText[i].setCharacterSize	( 45 );
		nText[i].setString			( std::to_string( n[i] ) );
		nText[i].setPosition		( window.getSize().x/2, window.getSize().y * ( 45/100.0 + (i*61/400.0) ) );
		nText[i].setFillColor		( sf::Color(80,255,124) );
		nText[i].setOutlineThickness( 2 );
		nText[i].setOrigin			( nText[i].getGlobalBounds().width / 2, 0 );
	}
	
	sel[0].setString( "PLAY" );
	sel[1].setString( "BACK" );
	for(int i=0;i<2;i++)
	{
		sel[i].setFont				( menuFont );
		sel[i].setCharacterSize		( 60 );
		sel[i].setPosition			( window.getSize().x * (40/100.0 + i*20/100.0), window.getSize().y * 85/100.0 );
		sel[i].setFillColor			( sf::Color(80,255,124) );
		sel[i].setOutlineThickness	( 3 );
		sel[i].setOrigin				( sel[i].getGlobalBounds().width / 2, 0 );
	}

	
	//menu initialization
	
	for(int i=0;i<21;i++)
		menuText[i].setFont(menuFont);
	
	for(int i=0;i<3;i++)
	{
		menuText[i].setString("Min");
		menuText[i+3].setString("(--)");
		menuText[i+6].setString("(-)");
	}
	
	menuText[9].setString("Rows");
	menuText[10].setString("Columns");
	menuText[11].setString("Bombs");
	
	for(int i=12;i<15;i++)
	{
		menuText[i].setString("(+)");
		menuText[i+3].setString("(++)");
		menuText[i+6].setString("Max");
	}
	
	Menu menu;
	menu.remakeTxt(&window, menuText, false, false, true, 3, 7, sf::FloatRect(0/100.0, 25/100.0, 100/100.0, 65/100.0), 2);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////// MAIN LOOP ////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	while (window.isOpen())
    {   
		//highlights PLAY and BACK
		for(int i=0; i<2; i++)
		{
			if( sf::IntRect(sel[i].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
			{
				if( sel[i].getFillColor() != sf::Color(175,255,220) )
					sel[i].setFillColor(sf::Color(175,255,220));	
			}
			else if( sel[i].getFillColor() != sf::Color(80,255,124) )
				sel[i].setFillColor(sf::Color(80,255,124));
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
			      		//PLAY
						if( sf::IntRect(sel[0].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
						{
							std::ofstream ofile;
							
							ofile.open ("bin/init", std::fstream::out | std::fstream::trunc | std::fstream::binary);
							ofile.write( reinterpret_cast<const char*>(&n[0]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[1]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[2]), sizeof(int) );
							ofile.close();
							
							return 2; //playing
						}
						//BACK
						if( sf::IntRect(sel[1].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
						{
							std::ofstream ofile;
							
							ofile.open ("bin/init", std::fstream::out | std::fstream::trunc | std::fstream::binary);
							ofile.write( reinterpret_cast<const char*>(&n[0]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[1]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[2]), sizeof(int) );
							ofile.close();
							
							return 1; //choose dificulty
						}
						
						switch ( menu.getSelected(sf::Mouse::getPosition(window)) )
						{	//always respect n[0]*n[1] >= n[2]+10
							
							case 0: // min row
								while( (n[0]-1)*n[1] >= n[2]+10  &&  n[0]-1>=5)
									n[0]--;
								break;
							case 1: // min col
								while( n[0]*(n[1]-1) >= n[2]+10  &&  n[1]-1>=5)
									n[1]--;
								break;
							case 2: // min bombs
								while( n[2]-1 >= 1 )
										n[2]--;
								break;
							case 3: // -- row
								for(int i=0; i<10; i++)
									if( (n[0]-1)*n[1] >= n[2]+10  &&  n[0]-1>=5)
										n[0]--;
								break;
							case 4: // -- col
								for(int i=0; i<10; i++)
									if( n[0]*(n[1]-1) >= n[2]+10  &&  n[1]-1>=5)
										n[1]--;
								break;
							case 5: // -- bombs
								for(int i=0; i<10; i++)
									if( n[2]-1 >= 1 )
										n[2]--;
								break;
							case 6: // - row
								if( (n[0]-1)*n[1] >= n[2]+10  &&  n[0]-1>=5)
									n[0]--;
								break;
							case 7: // - col
								if( n[0]*(n[1]-1) >= n[2]+10  &&  n[1]-1>=5)
									n[1]--;
								break;
							case 8: // - bombs
								if( n[2]-1 >= 1 )
									n[2]--;
								break;
							case 9: // set row
								n[0]=16;
								while( n[0]*n[1] < n[2]+10 )
									n[2]--;
								break;
							case 10: // set col
								n[1]=16;
								while( n[0]*n[1] < n[2]+10 )
									n[2]--;
								break;
							case 11: // set bombs
								n[2]=40;
								while( n[0]*n[1] < n[2]+10 )
									n[2]--;
								break;
							case 12: // + row
								if( n[0]+1 <= 40 )
									n[0]++;
								break;
							case 13: // + col
								if( n[1]+1 <= 40 )
									n[1]++;
								break;
							case 14: // + bombs
								if( n[0]*n[1] >= n[2]+1+10 )
									n[2]++;
								break;
							case 15: // ++ row
								for(int i=0; i<10; i++)
									if( n[0]+1 <= 40 )
										n[0]++;
								break;
							case 16: // ++ col
								for(int i=0; i<10; i++)
									if( n[1]+1 <= 40 )
										n[1]++;
								break;
							case 17: // ++ bombs
								for(int i=0; i<10; i++)
									if( n[0]*n[1] >= n[2]+1+10 )
										n[2]++;
								break;
							case 18: // max row
								while( n[0]+1 <= 40 )
									n[0]++;
								break;
							case 19: // max col
								while( n[1]+1 <= 40 )
									n[1]++;
								break;
							case 20: // max bombs
								while( n[0]*n[1] >= n[2]+1+10 )
									n[2]++;
								break;
							default:
								break;
						}
						if( menu.getSelected(sf::Mouse::getPosition(window)) != -1 )
						{
							for(int i=0; i<3; i++)
							{
								nText[i].setString( std::to_string( n[i] ) );
								nText[i].setOrigin( nText[i].getGlobalBounds().width / 2, 0 );
							}
						}
						
						break;
					case sf::Keyboard::Escape:
						//back to difficulty
						{
							std::ofstream ofile;
								
							ofile.open ("bin/init", std::fstream::out | std::fstream::trunc | std::fstream::binary);
							ofile.write( reinterpret_cast<const char*>(&n[0]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[1]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[2]), sizeof(int) );
							ofile.close();
						}
						return 1; //difficulty
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
						//PLAY
						if( sf::IntRect(sel[0].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
						{
							std::ofstream ofile;
							
							ofile.open ("bin/init", std::fstream::out | std::fstream::trunc | std::fstream::binary);
							ofile.write( reinterpret_cast<const char*>(&n[0]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[1]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[2]), sizeof(int) );
							ofile.close();
							
							return 2; //playing
						}
						//BACK
						if( sf::IntRect(sel[1].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
							return 1; //choose dificulty
						
						switch ( menu.getSelected(sf::Mouse::getPosition(window)) )
						{	//always respect n[0]*n[1] >= n[2]+10
							
							case 0: // min row
								while( (n[0]-1)*n[1] >= n[2]+10  &&  n[0]-1>=5)
									n[0]--;
								break;
							case 1: // min col
								while( n[0]*(n[1]-1) >= n[2]+10  &&  n[1]-1>=5)
									n[1]--;
								break;
							case 2: // min bombs
								while( n[2] > 1 )
										n[2]--;
								break;
							case 3: // -- row
								for(int i=0; i<10; i++)
									if(n[0]-1>=5)
									{
										n[0]--;
										if( n[0]*n[1] < n[2]+10 )
											n[2]=n[0]*n[1]-10;
									}
								break;
							case 4: // -- col
								for(int i=0; i<10; i++)
									if(n[1]-1>=5)
									{
										n[1]--;
										if( n[0]*n[1] < n[2]+10 )
											n[2]=n[0]*n[1]-10;
									}
								break;
							case 5: // -- bombs
								for(int i=0; i<10; i++)
									if( n[2]-1 >= 1 )
										n[2]--;
								break;
							case 6: // - row
								if(n[0]-1>=5)
								{
									n[0]--;
									if( n[0]*n[1] < n[2]+10 )
										n[2]=n[0]*n[1]-10;
								}
								break;
							case 7: // - col
								if(n[1]-1>=5)
								{
									n[1]--;
									if( n[0]*n[1] < n[2]+10 )
										n[2]=n[0]*n[1]-10;
								}
								break;
							case 8: // - bombs
								if( n[2] > 1 )
									n[2]--;
								break;
							case 9: // set row
								n[0]=16;
								while( n[0]*n[1] < n[2]+10 )
									n[2]--;
								break;
							case 10: // set col
								n[1]=16;
								while( n[0]*n[1] < n[2]+10 )
									n[2]--;
								break;
							case 11: // set bombs
								n[2]=40;
								while( n[0]*n[1] < n[2]+10 )
									n[2]--;
								break;
							case 12: // + row
								if( n[0]+1 <= 40 )
									n[0]++;
								break;
							case 13: // + col
								if( n[1]+1 <= 40 )
									n[1]++;
								break;
							case 14: // + bombs
								if( n[0]*n[1] >= n[2]+1+10 )
									n[2]++;
								break;
							case 15: // ++ row
								for(int i=0; i<10; i++)
									if( n[0]+1 <= 40 )
										n[0]++;
								break;
							case 16: // ++ col
								for(int i=0; i<10; i++)
									if( n[1]+1 <= 40 )
										n[1]++;
								break;
							case 17: // ++ bombs
								for(int i=0; i<10; i++)
									if( n[0]*n[1] >= n[2]+1+10 )
										n[2]++;
								break;
							case 18: // max row
								while( n[0]+1 <= 40 )
									n[0]++;
								break;
							case 19: // max col
								while( n[1]+1 <= 40 )
									n[1]++;
								break;
							case 20: // max bombs
								while( n[0]*n[1] >= n[2]+1+10 )
									n[2]++;
								break;
							default:
								break;
						}
						if( menu.getSelected(sf::Mouse::getPosition(window)) != -1 )
						{
							for(int i=0; i<3; i++)
							{
								nText[i].setString( std::to_string( n[i] ) );
								nText[i].setOrigin( nText[i].getGlobalBounds().width / 2, 0 );
							}
						}
						
						break;
					default:
						break;
				}
			}
        }
        
        window.clear();
        
        menu.draw(sf::Mouse::getPosition(window));
        
        for(int i=0; i<3; i++)
        	window.draw(nText[i]);
        for(int i=0; i<2; i++)
        	window.draw(sel[i]);
		
        window.display();
    }
    return (-1);
	
}
