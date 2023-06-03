#include "Playing.h"
#include <iostream>
#include <fstream>

Playing::Playing(void)
{	
	// get game volume, or sets to the standard 50
	bgMusic.openFromFile("sound/cow_lofi.ogg");
}

int Playing::update(sf::RenderWindow &window)
{
	bgMusic.setVolume(0.2);
	bgMusic.play();
	////////////////////////////////// VARIABLE DECLARATION /////////////////////////////////////////
	sf::Font font, timeFont;
	Field *field;
	sf::Texture gameoverTexture;
	sf::Sprite gameoverSprite;
	sf::Clock time;
	bool gameover=false, screenshot=false, viewField=false;
	sf::Text gameoverText[11], timeTxt, timeNbr;
	Menu gameoverMenu;
	sf::RectangleShape darkness;
	
	/////////////////////////////////// VARIABLE INITIALIZATION //////////////////////////////////////////////
	field = new Field(&window, &time);
	
	if(!font.loadFromFile("fonts/munro.ttf"))
		std::cout<<"Error loading font\n";
		
	if(!timeFont.loadFromFile("fonts/munro.ttf"))
		std::cout<<"Error loading time font\n";
	
	//sets fonts
	for(int i=0; i<11; i++)
		gameoverText[i].setFont(font);
	
	//initializes restart/quit options
	for(int i=8; i<11; i++)
	{
		gameoverText[i].setCharacterSize(50);
		gameoverText[i].setFillColor( sf::Color(80,255,124) );
		gameoverText[i].setOutlineThickness(2);
	}
	gameoverText[10].setCharacterSize(30);
	
	
	//initializes time (only printed after gameover)
	timeTxt.setCharacterSize(35);
	timeNbr.setCharacterSize(35);
	timeTxt.setFillColor( sf::Color(100,243,164) );
	timeNbr.setFillColor( sf::Color(100,243,164) );
	timeTxt.setFont(font);
	timeNbr.setFont(timeFont);
	timeTxt.setString("Time:");
	timeTxt.setPosition( window.getSize().x*88/100 - timeTxt.getGlobalBounds().width, window.getSize().y*5/100 );
	
	//darkens the screenshot after gameover
	darkness.setSize(sf::Vector2f(window.getSize().x, window.getSize().y) );
	darkness.setFillColor( sf::Color(8,80,26,128) );
	
	sf::Music endgameMusic;
	endgameMusic.setVolume(50);
	
	///////////////////////////////////////////// MAIN LOOP ////////////////////////////////////////////////////
	while (window.isOpen())
    {   
    	if(screenshot && bgMusic.getVolume() > 0) //volume will reduce in 5% of gameVolume per loop
    		bgMusic.setVolume( bgMusic.getVolume() - 5/10.f );
    	else if(!screenshot && bgMusic.getVolume() < 100)
    		bgMusic.setVolume( bgMusic.getVolume() + 1/250.f );
    		
    	if(screenshot && bgMusic.getVolume() <= 0.5)
    		bgMusic.pause();
    
    	//sets everything needed when player achieves gameover
		if( (field->defeat() || field->victory()) && !gameover )
		{
			bgMusic.pause();
			
			if(field->defeat())
			{
				if(!endgameMusic.openFromFile("sound/cow_anthem.ogg"))
					std::cout<<"Error loading sound\n";
				endgameMusic.play();
			}
			else
			{
				if(!endgameMusic.openFromFile("sound/cow_fanfare.ogg"))
					std::cout<<"Error loading sound\n";
				endgameMusic.play();
			}
				
			sf::sleep(sf::seconds(1));
			gameover=true;
		}
		else if(gameover && !screenshot)
		{
			screenshot=true;
			
			gameoverTexture.create(window.getSize().x, window.getSize().y);
			gameoverTexture.update(window);
			gameoverSprite.setTexture(gameoverTexture);
			
			timeNbr.setString( std::to_string( int( field->getEndtime()) ) );
			timeNbr.setPosition( timeTxt.getPosition().x + timeTxt.getGlobalBounds().width + window.getSize().x*1/100, timeTxt.getPosition().y );
			
			if(field->defeat())
			{
				gameoverText[0].setString("You didn't step on the poop...");
				gameoverText[1].setString("...you were swallowed by it.");
				gameoverText[2].setString("In the end, it revealed to be an alternate dimension.");
				gameoverText[3].setString("Our dimension was conquered by the cow empire.");
				gameoverText[4].setString("They are taking much more care of the planet than us...");
				gameoverText[5].setString("...so you did Earth-chan a favor, I guess?");
				gameoverText[6].setString("Anyway, nice try. You were vere brave, soldier.");
				gameoverText[7].setString("DEFEAT!");
				
				gameoverText[8].setString("Die to the cow again");
				gameoverText[9].setString("Give up, like all the others");
				gameoverText[10].setString("view field");
			}
			else
			{
				float r = field->getBombRatio();
				if(r<0.0823)		gameoverText[0].setString("Your journey was babyplay, but I'll give you some credit.");
				else if(r<0.1230)	gameoverText[0].setString("Your journey was very easy, but I'll give you some credit.");
				else if(r<0.1398)	gameoverText[0].setString("Your journey was kinda easy, but you've still helped.");
				else if(r<0.1812)	gameoverText[0].setString("Your journey was pretty standard, and here you stand.");
				else if(r<0.2065)	gameoverText[0].setString("Your journey was quite hard, but here you stand.");
				else if(r<0.3100)	gameoverText[0].setString("Your journey was very hard, but here you stand.");
				else				gameoverText[0].setString("Your journey was almost suicide... how did you make it?");
				gameoverText[1].setString("Alive. In one piece!");
				gameoverText[2].setString("No one thought you'd make it...");
				gameoverText[3].setString("...but don't blame them. Your chances were almost zero.");
				gameoverText[4].setString("You filled us with hope, kid.");
				gameoverText[5].setString("We can keep slavering those damn cows. All thanks to you.");
				gameoverText[6].setString("Now get back to work. Rent won't pay itself.");
				gameoverText[7].setString("VICTORY!");
				
				gameoverText[8].setString("Try your luck again");
				gameoverText[9].setString("Accept yout fate");
				gameoverText[10].setString("view field");
				
				if(field->getDifficulty())
				{
					std::ifstream lbIn;
					int wintime[3][10], dif=field->getDifficulty()-1, lbPos, curWintime=1000*field->getEndtime();
					lbIn.open("bin/leaderboard", std::fstream::in | std::fstream::binary);
					if(!lbIn)
					{	//creates default leaderbord
						int defaultLeaderbord = 0;
						std::ofstream lbOut;	
						lbOut.open ("bin/leaderboard", std::fstream::out | std::fstream::trunc | std::fstream::binary);
						for(int i=0; i<30; i++)
							lbOut.write( reinterpret_cast<const char*>(&defaultLeaderbord), sizeof(int) );
						lbOut.close();
						for(int i=0; i<30; i++)
							wintime[i/10][i%10]=0;
					}
					else
					{
						for(int i=0; i<30; i++)
							lbIn.read(reinterpret_cast<char*>(&wintime[i/10][i%10]), sizeof(int));
					}
					lbIn.close();
					
					lbPos = 10;
					// sees where player fits on the leaderboad
					for(int i=9; i>=0; i--)
						if(curWintime < wintime[dif][i] || wintime[dif][i] <= 0)
							lbPos = i;
					// if they are going to the leaderboard
					if( lbPos < 10 )
					{	//set position and pushes everyone behind
						for(int i=lbPos; i<10; i++)
						{
							int aux = wintime[dif][i];
							wintime[dif][i] = curWintime;
							curWintime = aux; //curWintime will be out of the leaderboard
						}
						//savs leaderboard
						std::ofstream lbOut;	
						lbOut.open ("bin/leaderboard", std::fstream::out | std::fstream::trunc | std::fstream::binary);
						for(int i=0; i<30; i++)
							lbOut.write( reinterpret_cast<const char*>(&wintime[i/10][i%10]), sizeof(int) );
						lbOut.close();
					}
				}
				
			}
			gameoverMenu.remakeTxt(&window, gameoverText, true);
			
			gameoverText[8].setOrigin(gameoverText[8].getGlobalBounds().width/2, 0);
			gameoverText[8].setPosition(window.getSize().x/2, window.getSize().y*74/100);
			
			gameoverText[9].setOrigin(gameoverText[9].getGlobalBounds().width/2, 0);
			gameoverText[9].setPosition(window.getSize().x/2,
										gameoverText[8].getGlobalBounds().top + gameoverText[8].getGlobalBounds().height + window.getSize().y*2/100);
		
			gameoverText[10].setPosition(window.getSize().x*98/100 - gameoverText[10].getGlobalBounds().width,
										window.getSize().y*97/100 - gameoverText[10].getGlobalBounds().height);
		}
		
		if(gameover)
		{
			//highlights restart option if hovered by mouse
			for(int i=8; i<11; i++)
			{
				if( sf::IntRect(gameoverText[i].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
				{
					if( gameoverText[i].getFillColor() != sf::Color(155,255,210) )
						gameoverText[i].setFillColor(sf::Color(155,255,210));	
				}
				else if( gameoverText[i].getFillColor() != sf::Color(80,255,124) )
					gameoverText[i].setFillColor(sf::Color(80,255,124));
			}
			
				
		}
		
		///////////////////////////////////// EVENT LOOP /////////////////////////////////////////////
        sf::Event event;
        while (window.pollEvent(event))
        {
        	if (event.type==sf::Event::Closed)
        	{
        		bgMusic.stop();
                return -1;
			}
            if (event.type==sf::Event::KeyPressed)
		    {
				switch(event.key.code)
				{
					case sf::Keyboard::Return:
			      		//same as left mouse click
						if(!gameover) //opens field
							field->open(sf::Mouse::getPosition(window));
						else
						{
							//restart
							if( sf::IntRect(gameoverText[8].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
							{
								bgMusic.pause();
								return 2;
							}
							//quit to menu
							if( sf::IntRect(gameoverText[9].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
							{
								bgMusic.pause();
								return 0;
							}
							//view field
							if( sf::IntRect(gameoverText[10].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
							{
								viewField=!viewField;
								if(viewField)
								{
									gameoverText[10].setString("back");
									gameoverText[10].setPosition(window.getSize().x*98/100 - gameoverText[10].getGlobalBounds().width,
										window.getSize().y*97/100 - gameoverText[10].getGlobalBounds().height);
								}
								else
								{
									gameoverText[10].setString("view field");
									gameoverText[10].setPosition(window.getSize().x*98/100 - gameoverText[10].getGlobalBounds().width,
										window.getSize().y*97/100 - gameoverText[10].getGlobalBounds().height);
								}
							}
						}
						break;
			    	case sf::Keyboard::Space:
			      		//restart field
			      		bgMusic.pause();
						return 2;
						break;
					case sf::Keyboard::Escape:
						//quit 
						bgMusic.pause();
						return 1;
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
						if(!gameover) //opens field
							field->open(sf::Mouse::getPosition(window));
						else
						{
							//restart
							if( sf::IntRect(gameoverText[8].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
							{
								bgMusic.pause();
								return 2;
							}
							//quit to menu
							if( sf::IntRect(gameoverText[9].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
							{
								bgMusic.pause();
								return 0;
							}
							//view field
							if( sf::IntRect(gameoverText[10].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
							{
								viewField=!viewField;
								if(viewField)
								{
									gameoverText[10].setString("back");
									gameoverText[10].setPosition(window.getSize().x*98/100 - gameoverText[10].getGlobalBounds().width,
										window.getSize().y*97/100 - gameoverText[10].getGlobalBounds().height);
								}
								else
								{
									gameoverText[10].setString("view field");
									gameoverText[10].setPosition(window.getSize().x*98/100 - gameoverText[10].getGlobalBounds().width,
										window.getSize().y*97/100 - gameoverText[10].getGlobalBounds().height);
								}
							}
						}
						break;
					case sf::Mouse::Right:
						if(!gameover)
							field->putFlag(sf::Mouse::getPosition(window));
						break;
					default:
						break;
				}
			}
        }
        
        window.clear();
        
        if(!screenshot)
        {
			field->draw(sf::Mouse::getPosition(window));
		}
		else if(viewField)
		{
			window.draw(gameoverSprite);
			window.draw(gameoverText[10]);
		}
        else
        {
        	window.draw(gameoverSprite);

        	window.draw(darkness);
        	gameoverMenu.draw(sf::Mouse::getPosition(window));
        	
        	window.draw(timeTxt);
        	window.draw(timeNbr);
        	
        	window.draw(gameoverText[8]);
        	window.draw(gameoverText[9]);
        	window.draw(gameoverText[10]);
		}
		
        window.display();
    }
    bgMusic.stop();
    return (-1);
	
}
