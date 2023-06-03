#include "Menu.h"
#include<iostream>

Menu::Menu()
{
	optionsText=nullptr;
}

Menu::~Menu()
{
	if(optionsText!=nullptr)
		delete[] optionsText;
}


void Menu::remake(sf::RenderWindow *window,int Row,int Col,sf::Text text[],float boxL,float boxU,float boxR,float boxD,
					bool Box,bool Title,float txtL,float txtU,float txtR,float txtD, bool Sel)
{
	if(optionsText!=nullptr)
		delete[] optionsText;
	
	box=Box; title=Title; row=Row; col=Col; selectable=Sel; windowPtr=window;
	
	sf::FloatRect rect(	windowPtr->getSize().x*boxL/100, windowPtr->getSize().y*boxU/100,
						windowPtr->getSize().x*(boxR-boxL)/100, windowPtr->getSize().y*(boxD-boxU)/100 );
	sf::FloatRect rectTxt(windowPtr->getSize().x*txtL/100, windowPtr->getSize().y*txtU/100,
						windowPtr->getSize().x*(txtR-txtL)/100, windowPtr->getSize().y*(txtD-txtU)/100 );

	if(box)
	{
		rect_box.setSize(sf::Vector2f(rect.width, rect.height) );
		rect_box.setPosition(rect.left,rect.top);
		rect_box.setOutlineThickness( windowPtr->getSize().y*0.75/100 );
		rect_box.setFillColor( sf::Color(86,149,200) );
		rect_box.setOutlineColor( sf::Color(75,186,135) );
	}
	
	if(title)
	{
		int t=row*col;
		optionsText=new sf::Text[t+1];
		optionsText[t].setFont(* text[t].getFont() );
		optionsText[t].setString(text[t].getString() );
		optionsText[t].setCharacterSize(BIG_SIZE);
		optionsText[t].setOrigin( (optionsText[t].getLocalBounds().width)/2 , (optionsText[t].getLocalBounds().height)/2 );
		optionsText[t].setPosition( rect.left + rect.width/2, rect.top + rect.height/8 );
		optionsText[t].setFillColor( sf::Color(75,186,135) );
	}
	else
		optionsText=new sf::Text[row*col];
	
	int k=0;
	for(int j=0;j<col;j++) 
	{
		for(int i=0;i<row;i++)
		{
			optionsText[k].setFont(* text[0].getFont() );
			optionsText[k].setString(text[k].getString() );
			optionsText[k].setCharacterSize(text[k].getCharacterSize() );
			optionsText[k].setOrigin( (optionsText[k].getLocalBounds().width)/2 , (optionsText[k].getLocalBounds().height)/2 );
			optionsText[k].setPosition( rectTxt.left + rectTxt.width/(col+1) * (j+1), rectTxt.top + rectTxt.height/(row+1) * (i+1) );
			
			k++;
		}
	}
}

void Menu::draw(sf::Vector2i mousePos)
{
	if(box)
		windowPtr->draw(rect_box);
		
	for(int i=0;i<(row*col);i++)
	{
		if(selectable && sf::IntRect(optionsText[i].getGlobalBounds()).contains(mousePos) )//.contains(float(mousePos.x), float(mousePos.y)) )
		{
			optionsText[i].setFillColor (highColor);
			windowPtr->draw(optionsText[i]);
			optionsText[i].setFillColor (fillColor);
		}
		else
			windowPtr->draw(optionsText[i]);
	}
	
	if(title)
		windowPtr->draw(optionsText[row*col]);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//									GENERAL FUNCTIONS												//


void Menu::changeSize(int n, int newSize)
{
	for(int i=0; i<n; i++)
	{
		optionsText[i].setCharacterSize(newSize);
	}
}

void Menu::remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title)
{
	remakeTxt(window, text, Title, true, false, 7, 1);
}
void Menu::remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title, bool Box, bool Sel, int Row, int Col)
{
	remakeTxt(window, text, Title, Box, Sel, Row, Col, sf::FloatRect(3/100.0, 3/100.0, 94/100.0, 69/100.0), 0 );
}
void Menu::remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title, bool Box, bool Sel, int Row, int Col, sf::FloatRect tempRect, int outline)
{
	remakeTxt(window, text, Title, Box, Sel, Row, Col, tempRect, outline, sf::Color(110,230,124), sf::Color(215,255,235), sf::Color(12,87,30) );
}
void Menu::remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title, bool Box, bool Sel, int Row, int Col, sf::FloatRect tempRect, int outline,
		sf::Color boxFill, sf::Color boxOut)
{
	remakeTxt(window,text, Title, Box, Sel, Row, Col, tempRect, outline, sf::Color(110,230,124), sf::Color(215,255,235), sf::Color(12,87,30), boxFill, boxOut );
}
void Menu::remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title, bool Box, bool Sel, int Row, int Col, sf::FloatRect tempRect, int outline,
		sf::Color fill, sf::Color high, sf::Color out)
{
	remakeTxt(window, text, Title, Box, Sel, Row, Col, tempRect, outline, fill, high, out, sf::Color(105,155,230,208), sf::Color(100,243,164,224) );
}
void Menu::remakeTxt(sf::RenderWindow *window, sf::Text text[], bool Title, bool Box, bool Sel, int Row, int Col, sf::FloatRect tempRect, int outline,
		sf::Color fill, sf::Color high, sf::Color out, sf::Color boxFill, sf::Color boxOut)
{
	box=Box; title=Title; row=Row; col=Col; selectable=Sel; windowPtr=window;
	fillColor=fill; highColor=high; outColor=out; boxFillColor=boxFill, boxOutColor=boxOut;
	
	if(optionsText!=nullptr)
		delete[] optionsText;

	sf::FloatRect rect	(windowPtr->getSize().x*tempRect.left, windowPtr->getSize().y*tempRect.top,
						 windowPtr->getSize().x*tempRect.width, windowPtr->getSize().y*tempRect.height );
	sf::FloatRect rectTxt(windowPtr->getSize().x*(tempRect.left+0.02), windowPtr->getSize().y*(tempRect.top+0.02),
						 windowPtr->getSize().x*(tempRect.width-0.04), windowPtr->getSize().y*(tempRect.height-0.04) );
	if(title)
	{
		sf::Text bigText;
		bigText.setFont(* text[row*col].getFont() );
		bigText.setString(text[row*col].getString() );
		bigText.setCharacterSize(BIG_SIZE);
		rectTxt.top		+= windowPtr->getSize().y*1/100.0 + bigText.getLocalBounds().height;
		rectTxt.height	-= windowPtr->getSize().y*1/100.0 + bigText.getLocalBounds().height;
	}
	
	if(box)
	{
		rect_box.setSize(sf::Vector2f(rect.width, rect.height) );
		rect_box.setPosition(rect.left,rect.top);
		rect_box.setOutlineThickness( windowPtr->getSize().y*0.75/100 );
		rect_box.setFillColor( boxFillColor );
		rect_box.setOutlineColor( boxOutColor );
	}
	
	if(title)
	{
		int t=row*col;
		optionsText=new sf::Text[t+1];
		optionsText[t].setFont(* text[t].getFont() );
		optionsText[t].setString(text[t].getString() );
		optionsText[t].setCharacterSize(BIG_SIZE);
		optionsText[t].setOutlineThickness(outline);
		optionsText[t].setOrigin( (optionsText[t].getLocalBounds().width)/2 , (optionsText[t].getLocalBounds().height)/2 );
		optionsText[t].setPosition( rectTxt.left + rectTxt.width/2, rectTxt.top - optionsText[t].getLocalBounds().height/2 - windowPtr->getSize().y/100 );
		optionsText[t].setFillColor( fillColor );
		optionsText[t].setOutlineColor( outColor );
	}
	else
		optionsText=new sf::Text[row*col];
	
	
	int k=0;
	for(int j=0;j<col;j++) 
	{
		for(int i=0;i<row;i++)
		{
			optionsText[k].setFont(* text[0].getFont() );
			optionsText[k].setString(text[k].getString() );
			optionsText[k].setCharacterSize( DEFAULT_SIZE );
			
			int correctSize = DEFAULT_SIZE;
			while(optionsText[k].getLocalBounds().width >= rectTxt.width*0.99) //makes sure text fits screen
			{
				correctSize--;
				optionsText[k].setCharacterSize( correctSize );
			}
			
			optionsText[k].setOutlineThickness(outline);
			optionsText[k].setOrigin( (optionsText[k].getLocalBounds().width)/2 , (optionsText[k].getLocalBounds().height)/2 );
			optionsText[k].setPosition( rectTxt.left + rectTxt.width/(col+1) * (j+1), rectTxt.top + rectTxt.height/(row+1) * (i+1) );//lines qtd will be row-1
			
			optionsText[k].setFillColor( fillColor );
			optionsText[k].setOutlineColor( outColor );
			
			k++;
		}
	}
	
}

void Menu::remakeBack(sf::RenderWindow *window, float width, float height, sf::Color color, sf::Color highlighted)
{
	remakeBack(window, width, height, color, highlighted, 0, sf::Color(0,0,0));
}
void Menu::remakeBack(sf::RenderWindow *window,float width,float height, sf::Color fill, sf::Color high, int outline, sf::Color out)
{
	box=false; title=false; row=1; col=1; selectable=true; windowPtr=window; fillColor=fill; highColor=high; outColor=out;
	
	if(optionsText!=nullptr)
		delete[] optionsText;

	optionsText=new sf::Text[row*col];
	
	font.loadFromFile("fonts/munro.ttf");
	
	optionsText[0].setFont(font);
	optionsText[0].setCharacterSize( DEFAULT_SIZE );	
	optionsText[0].setString("back");
	
	optionsText[0].setFillColor( fillColor );
	optionsText[0].setOutlineThickness( outline );
	optionsText[0].setOutlineColor( outColor );
	
	optionsText[0].setPosition( windowPtr->getSize().x*width, windowPtr->getSize().y*height );
}

void Menu::featureDisabled(sf::Vector2i mousePos)
{
	sf::RectangleShape darkness;
	darkness.setSize(sf::Vector2f(windowPtr->getSize().x,windowPtr->getSize().y) );
	darkness.setFillColor( sf::Color(8,80,26,128) );
	
	sf::Font font;
	font.loadFromFile("fonts/munro.ttf");
	
	sf::Text txt[1];
	txt[0].setFont(font);
	txt[0].setCharacterSize(DEFAULT_SIZE);
	txt[0].setString("Oops, not implemented yet...");
	
	Menu auxmenu;
	auxmenu.remake(windowPtr,1,1,txt,20,40,80,60,true,false,3,35,97,65, true);
	
	windowPtr->draw(darkness);
	auxmenu.draw(mousePos);
    windowPtr->display();
    sf::sleep(sf::milliseconds(1500));
    /*sf::Event event;
    while( event.type!=sf::Event::KeyPressed || event.key.code!=sf::Keyboard::Return )//!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) )
	{
		windowPtr->pollEvent(event);
		if (event.type==sf::Event::Closed)
            windowPtr->close();
	}*/
}

void Menu::setCharacterSize(int n)
{
	DEFAULT_SIZE	= n;
	BIG_SIZE		= DEFAULT_SIZE * 2;
	SMALL_SIZE		= DEFAULT_SIZE * 0.65;
	
	if(optionsText!=nullptr)
	{
		for(int i=0; i<row*col; i++)
			optionsText[i].setCharacterSize(DEFAULT_SIZE);
		if(title)
			optionsText[row*col].setCharacterSize(BIG_SIZE);
	}
}


int Menu::getSelected(sf::Vector2i mousePos) const
{
	for(int i=0; i<row*col; i++)
		if( sf::IntRect(optionsText[i].getGlobalBounds()).contains(mousePos) )
			return (i);
	return -1;
}

