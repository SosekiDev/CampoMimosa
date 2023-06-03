#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>


#define TXT_N 10


class Menu
{
	public:

		Menu();
		~Menu();
		void remake(sf::RenderWindow *window,int Row,int Col,sf::Text text[],float boxL,float boxU,float boxR,float boxD,
					bool Box,bool Title,float txtL,float txtU,float txtR,float txtD, bool Sel);
		void draw(sf::Vector2i mousePos);
		void remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title);
		void remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title, bool Box, bool Sel, int Row, int Col);
		void remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title, bool Box, bool Sel, int Row, int Col, sf::FloatRect tempRect, int outline);
		void remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title, bool Box, bool Sel, int Row, int Col, sf::FloatRect tempRect, int outline,
			sf::Color boxFill, sf::Color boxOut);
		void remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title, bool Box, bool Sel, int Row, int Col, sf::FloatRect tempRect, int outline,
			sf::Color fill, sf::Color high, sf::Color out);
		void remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title, bool Box, bool Sel, int Row, int Col, sf::FloatRect tempRect, int outline,
			sf::Color fill, sf::Color high, sf::Color out, sf::Color boxFill, sf::Color boxOut);
		void remakeBack(sf::RenderWindow *window, float width, float height, sf::Color color, sf::Color highlighted);
		void remakeBack(sf::RenderWindow *window,float width,float height,sf::Color color,sf::Color highlighted,int outline, sf::Color outColor);
		
		//void setWindow(sf::RenderWindow *window) {windowPtr=window; };
		void setCharacterSize(int n);
		int getCharacterSize() const {if(optionsText!=nullptr) return (optionsText[0].getCharacterSize()); else return 0;	}
		
		int getSelected(sf::Vector2i mousePos) const;
		
	private:
		void correctError(); //if chosen option is outside of the matrix, move it back
		
		sf::Text *optionsText;
		sf::RectangleShape rect_box;
		sf::FloatRect rect;
		sf::FloatRect rectTxt;
		bool box, title, selectable=false;
		int row, col, DEFAULT_SIZE=30, BIG_SIZE=DEFAULT_SIZE*2, SMALL_SIZE=DEFAULT_SIZE*0.65;
		sf::RenderWindow *windowPtr;
		sf::Color fillColor, highColor, outColor, boxFillColor, boxOutColor;
		sf::Font font;
		
	public:				
						
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		void changeSize(int n, int newSize);
		void featureDisabled(sf::Vector2i mousePos);
};

#endif
