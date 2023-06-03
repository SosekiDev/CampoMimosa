#ifndef FIELD_H
#define FIELD_H
#include <SFML/Graphics.hpp>
#include "Menu.h"
//#include <vector>

//typedef std::vector<std::vector<int> >  intMatrix;
//typedef std::vector<std::vector<sf::Sprite> >  spriteMatrix;

class Field
{
	public:
		Field();
		Field(sf::RenderWindow *window, /*int width, int height, int Row, int Col, int Bombs,*/ sf::Clock *Time);
		~Field();

	//	void create_field (intMatrix &newField);
		void setWindow(sf::RenderWindow *window) {windowPtr=window; };
		void draw(sf::Vector2i mousePos);
		void matchSprite(int n);
		sf::IntRect getSpriteRect(int n);
		void createField(int x, int y);
		sf::Vector2i getSel(sf::Vector2i mousePos);
		int open(sf::Vector2i mousePos);
		void open(int x, int y);
		void setClickable();
		void putFlag(sf::Vector2i mousePos);
		bool defeat();
		bool victory();
		float getTime() const {return(time->getElapsedTime().asSeconds() );	};
		float getEndtime() const {return endtime;	}
		float getBombRatio() const {return ( bombs / double(row*col) );	};
		int getDifficulty() const; //1=easy; 2=normal; 3=hard
		
	private:
		int row, col, bombs, bombsLeft;
		float endtime;
		int **trueField, **maskField;
		bool **clickable, newField, defeated=false, victorious=false;
		sf::Sprite sprite, bgSprite;
		sf::Texture tilemap, bgTexture;
		sf::IntRect rect;
		sf::Font font;
		sf::Text bombsTxt, timeTxt;
		sf::Clock *time;
		sf::RenderWindow *windowPtr;
};

#endif
