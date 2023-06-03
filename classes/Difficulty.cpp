#include "Difficulty.h"
#include<iostream>

#define screenScale 90/100.0
#define spacing 15

Difficulty::Difficulty(void)
{

}

int Difficulty::update(sf::RenderWindow &window)
{
	std::ofstream ofile;
	
	bool highlighted[4]={0, 0, 0, 0};
	
	sf::Texture texture[8];
	sf::Sprite sprite[4];
	
	texture[0].loadFromFile("img/easy.png");
	texture[1].loadFromFile("img/normal.png");
	texture[2].loadFromFile("img/hard.png");
	texture[3].loadFromFile("img/custom.png");
	texture[4].loadFromFile("img/easy_sel.png");
	texture[5].loadFromFile("img/normal_sel.png");
	texture[6].loadFromFile("img/hard_sel.png");
	texture[7].loadFromFile("img/custom_sel.png");
	
	sf::Font font;
	if(!font.loadFromFile("fonts/munro.ttf"))
		std::cout<<"Error loading font\n";
	
	Menu back;
	back.remakeBack(&window, 92/100.f, 93.5/100, sf::Color(96,96,96), sf::Color(192,192,192) );
	
	
	for(int i=0; i<4; i++)
	{
		sprite[i].setTexture(texture[i]);
		texture[i].setSmooth(true);
		texture[i+4].setSmooth(true);
		
		float fitScr=((1.0*window.getSize().x / window.getSize().y > 1.0*texture[3].getSize().x / (texture[1].getSize().y + 25 + texture[3].getSize().y) )?
						1.0*window.getSize().y / (texture[1].getSize().y + 25 + texture[3].getSize().y) : 1.0*window.getSize().x / texture[3].getSize().x );
		sprite[i].setScale( fitScr * screenScale, fitScr * screenScale );
	}
	
	sprite[1].setPosition(window.getSize().x/2 - sprite[1].getGlobalBounds().width/2,
					(window.getSize().y - sprite[1].getGlobalBounds().height - spacing*sprite[1].getScale().x -  sprite[3].getGlobalBounds().height) /2 );
	sprite[0].setPosition(sprite[1].getPosition().x - spacing*sprite[1].getScale().x - sprite[1].getGlobalBounds().width, sprite[1].getPosition().y );
	sprite[2].setPosition(sprite[1].getPosition().x + spacing*sprite[1].getScale().x + sprite[1].getGlobalBounds().width, sprite[1].getPosition().y );
	sprite[3].setPosition(window.getSize().x/2 - sprite[3].getGlobalBounds().width/2,
					sprite[1].getPosition().y + spacing*sprite[1].getScale().y + sprite[1].getGlobalBounds().height);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////// MAIN LOOP ////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	while (window.isOpen())
    {   
		//highlights options if hovered by mouse
		for(int i=0; i<4; i++)
		{
			if( sf::IntRect( sprite[i].getGlobalBounds()).contains(sf::Mouse::getPosition(window)) )
			{
				if(!highlighted[i])
				{
					sprite[i].setTexture(texture[i+4]);
					highlighted[i] = true;
				}
			}
			else if( highlighted[i] )
			{
				sprite[i].setTexture(texture[i]);
				highlighted[i] = false;
			}
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
			      		if(back.getSelected(sf::Mouse::getPosition(window)) == 0 )
							return 0;
							
						bool click[4];
						for(int i=0; i<4; i++)
							click[i]=sf::IntRect(sprite[i].getGlobalBounds()).contains(sf::Mouse::getPosition(window));
						
						if( click[0] || click[1] || click[2] )
						{
							int n[3]; // row, col, bombs
							if(click[0])		{n[0]=9;	n[1]=9;		n[2]=10;	}
							else if(click[1]) 	{n[0]=16;	n[1]=16;	n[2]=40;	}
							else 			 	{n[0]=20;	n[1]=24;	n[2]=99;	}
							
							ofile.open ("bin/init", std::fstream::out | std::fstream::trunc | std::fstream::binary);
							ofile.write( reinterpret_cast<const char*>(&n[0]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[1]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[2]), sizeof(int) );
							ofile.close();
							
							return 2; //playing
						}
						if(click[3])	
							return 3; //custom difficulty screen
						break;
						
						break;
					case sf::Keyboard::Escape:
						//back to menu
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
						if(back.getSelected(sf::Mouse::getPosition(window)) == 0 )
							return 0;
							
						bool click[4];
						for(int i=0; i<4; i++)
							click[i]=sf::IntRect(sprite[i].getGlobalBounds()).contains(sf::Mouse::getPosition(window));
						
						if( click[0] || click[1] || click[2] )
						{
							int n[3]; // row, col, bombs
							if(click[0])		{n[0]=9;	n[1]=9;		n[2]=10;	}
							else if(click[1]) 	{n[0]=16;	n[1]=16;	n[2]=40;	}
							else 			 	{n[0]=20;	n[1]=24;	n[2]=99;	}
							
							ofile.open ("bin/init", std::fstream::out | std::fstream::trunc | std::fstream::binary);
							ofile.write( reinterpret_cast<const char*>(&n[0]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[1]), sizeof(int) );
							ofile.write( reinterpret_cast<const char*>(&n[2]), sizeof(int) );
							ofile.close();
							
							return 2; //playing
						}
						if(click[3])	
							return 3; //custom difficulty screen
						break;
					default:
						break;
				}
			}
        }
        
        window.clear();
        
        for(int i=0; i<4; i++)
        	window.draw(sprite[i]);
        back.draw(sf::Mouse::getPosition(window));
        window.display();
    }
    return (-1);
	
}
