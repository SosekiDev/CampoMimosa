#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>


#define TXT_N 10
static int DEFAULT_SIZE = 30;
static int BIG_SIZE     = DEFAULT_SIZE * 2;
static int SMALL_SIZE   = DEFAULT_SIZE * 0.65;


class Menu
{
	public:
		Menu(float width,float height,int Row,int Col,sf::Text text[],float boxL,float boxU,float boxR,float boxD,
					bool Box,bool Title,bool VLoop, bool HLoop,float txtL,float txtU,float txtR,float txtD, bool select);
		Menu(){	}
		~Menu();
		
		void draw(sf::RenderWindow &window);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		int getSelected(){return optionSelected; }
		bool remake(float width,float height,int Row,int Col,sf::Text text[],float boxL,float boxU,float boxR,float boxD,
					bool Box,bool Title,bool VLoop, bool HLoop,float txtL,float txtU,float txtR,float txtD, bool select);
		bool remakeLow(int width, int height, sf::Text text[], bool Title);
		bool remakeTxt(int width, int height, sf::Text text[], bool Title);
					
		//bool setText(std::string txt, int n) {optionsText[n].setString(txt);	}
		//std::string getText(int n) {return ( optionsText[n].getString() );	}
		//int getTextSize(){return (textSize);	}
		
	private:
		bool correctError(); //if chosen option is outside of the matrix, move it back
		
		sf::Text *optionsText;
		sf::RectangleShape rect_box;
		sf::FloatRect rect;
		sf::FloatRect rectTxt;
		bool box, vLoop, hLoop, title;
		int optionSelected,row,col;
		
	public:				
						
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		void changeSize(sf::Text (&TEXT)[TXT_N], int newSize);
		void featureDisabled(sf::RenderWindow &window);
};

#endif
