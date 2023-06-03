#include "Playing.h"
#include <iostream>

Playing::Playing(void)
{
	state = 0;
	oldState = -1;
	
	if(!lowMenuFont.loadFromFile("fonts/Adventurer.ttf"))
	{
		std::cout<<"Error loading font";
	//	return (-1);
	}
	
	for(int i=0;i<8;i++)
		txtMenuText[i].setFont(lowMenuFont);
	
	for(int i=0;i<5;i++)
		lowMenuText[i].setFont(lowMenuFont);
	
}

int Playing::update(sf::RenderWindow &window)
{
	
	
	
	
	while (window.isOpen())
    {   
    	if(state != oldState)
    	switch(state)
    	{
    		case 0:
				txtMenuText[0].setString("You're just a friendly witch.");
				txtMenuText[1].setString("That's not what the church thinks, thou.");
				txtMenuText[2].setString("The Inquisition is only getting stronger.");
				txtMenuText[3].setString("I advise you to prepare yourself...");
				txtMenuText[4].setString("...unless you want to perish to this putrid line of thought.");
				txtMenuText[5].setString("May Diana and Cernunnos be at your side...");
				txtMenuText[6].setString("...and the wisdom of The Moon be at your mind!");
				txtMenuText[7].setString("");
				
				lowMenuText[0].setString("...");
				lowMenuText[1].setString("...");
				lowMenuText[2].setString("...");
				lowMenuText[3].setString("...");
				lowMenuText[4].setString("");
				
				txtMenu.remakeTxt(window.getSize().x,window.getSize().y,txtMenuText,false);
				lowMenu.remakeLow(window.getSize().x,window.getSize().y,lowMenuText,false);
    			
    			break;
    		case 1:
    			txtMenuText[0].setString("");
				txtMenuText[1].setString("");
				txtMenuText[2].setString("");
				txtMenuText[3].setString("");
				txtMenuText[4].setString("");
				txtMenuText[5].setString("");
				txtMenuText[6].setString("");
				txtMenuText[7].setString("What is your name?");
				
				lowMenuText[0].setString("Isabelle");
				lowMenuText[1].setString("Clarice");
				lowMenuText[2].setString("Joanna");
				lowMenuText[3].setString("Amalia");
				lowMenuText[4].setString("");
				
				txtMenu.remakeTxt(window.getSize().x,window.getSize().y,txtMenuText,true);
				lowMenu.remakeLow(window.getSize().x,window.getSize().y,lowMenuText,false);
    			break;
    		case 2:
    			txtMenuText[0].setString("");
				txtMenuText[1].setString("");
				txtMenuText[2].setString("");
				txtMenuText[3].setString("");
				txtMenuText[4].setString("");
				txtMenuText[5].setString("");
				txtMenuText[6].setString("");
				txtMenuText[7].setString("");
				
				lowMenuText[0].setString("");
				lowMenuText[1].setString("");
				lowMenuText[2].setString("");
				lowMenuText[3].setString("");
				lowMenuText[4].setString("");
    			break;
		}
		
		oldState = state;
		
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
				case sf::Keyboard::Up:
					lowMenu.moveUp();
					break;
				case sf::Keyboard::Down:
					lowMenu.moveDown();
					break;
				case sf::Keyboard::Left:
					lowMenu.moveLeft();
					break;
				case sf::Keyboard::Right:
					lowMenu.moveRight();
					break;
		      	case sf::Keyboard::Return:
		      		switch(state)
		      		{
		      			case 0:
		      				state++;
		      				break;
		      			case 1:
							switch(lowMenu.getSelected() )
							{
							case 0:
								player.name="Isabelle";
								break;
							case 1:
								player.name="Clarice";
								break;
							case 2:
								player.name="Joanna";
								break;
							case 3:
								player.name="Amalia";
								break;
							}
							
							break;
					}
					break;
				default:
						
					break;
		   		}
			}
        }
        window.clear();
        txtMenu.draw(window);
        lowMenu.draw(window);
        window.display();
    }
    return (-1);
	
}
