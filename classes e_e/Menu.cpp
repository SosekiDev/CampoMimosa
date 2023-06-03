#include "Menu.h"

Menu::Menu(float width,float height,int Row,int Col,sf::Text text[],float boxL,float boxU,float boxR,float boxD,
			bool Box,bool Title,bool VLoop, bool HLoop,float txtL,float txtU,float txtR,float txtD, bool select)
{
	box=Box; title=Title; row=Row; col=Col; vLoop=VLoop; hLoop=HLoop; optionSelected=select-1;
	
	sf::FloatRect rect(width*boxL/100, height*boxU/100, width*(boxR-boxL)/100, height*(boxD-boxU)/100 );
	sf::FloatRect rectTxt(width*txtL/100, height*txtU/100, width*(txtR-txtL)/100, height*(txtD-txtU)/100 );

	if(box)
	{
		rect_box.setSize(sf::Vector2f(rect.width, rect.height) );
		rect_box.setPosition(rect.left,rect.top);
		rect_box.setOutlineThickness( height*0.75/100 );
		rect_box.setFillColor( sf::Color(8,0,10) );
		rect_box.setOutlineColor( sf::Color(224,224,224) );
	}
	
	if(title)
	{
		int t=row*col;
		optionsText=new sf::Text[t+1];
		optionsText[t].setFont(* text[t].getFont() );
		optionsText[t].setString(text[t].getString() );
		optionsText[t].setCharacterSize(text[t].getCharacterSize() );
		optionsText[t].setOrigin( (optionsText[t].getLocalBounds().width)/2 , (optionsText[t].getLocalBounds().height)/2 );
		optionsText[t].setPosition( rect.left + rect.width/2, rect.top + rect.height/8 );
		optionsText[t].setFillColor( sf::Color(224,224,224) );
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
			
			if(k==optionSelected)
				optionsText[k].setFillColor( sf::Color(255,255,255) );
			else
				optionsText[k].setFillColor( sf::Color(112,112,112) );
			k++;
		}
	}
}

Menu::~Menu()
{
	delete[] optionsText;
}

void Menu::draw(sf::RenderWindow &window)
{
	if(box)
		window.draw(rect_box);
		
	for(int i=0;i<(row*col);i++)
	{
		window.draw(optionsText[i]);
	}
	
	if(title)
		window.draw(optionsText[row*col]);
}

bool Menu::remake(float width,float height,int Row,int Col,sf::Text text[],float boxL,float boxU,float boxR,float boxD,
					bool Box,bool Title,bool VLoop, bool HLoop,float txtL,float txtU,float txtR,float txtD, bool select)
{
	box=Box; title=Title; row=Row; col=Col; vLoop=VLoop; hLoop=HLoop; optionSelected=select-1;
	
	sf::FloatRect rect(width*boxL/100, height*boxU/100, width*(boxR-boxL)/100, height*(boxD-boxU)/100 );
	sf::FloatRect rectTxt(width*txtL/100, height*txtU/100, width*(txtR-txtL)/100, height*(txtD-txtU)/100 );

	if(box)
	{
		rect_box.setSize(sf::Vector2f(rect.width, rect.height) );
		rect_box.setPosition(rect.left,rect.top);
		rect_box.setOutlineThickness( height*0.75/100 );
		rect_box.setFillColor( sf::Color(8,0,10) );
		rect_box.setOutlineColor( sf::Color(224,224,224) );
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
		optionsText[t].setFillColor( sf::Color(224,224,224) );
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
				
			if(k==optionSelected)
				optionsText[k].setFillColor( sf::Color(255,255,255) );
			else
				optionsText[k].setFillColor( sf::Color(112,112,112) );
			k++;
		}
	}
	return true;
}

void Menu::moveUp()
{
	if(optionSelected%row && optionSelected!=-1)
	{
		optionsText[optionSelected].setFillColor( sf::Color(112,112,112) );
		optionSelected-=1;
		correctError();
		optionsText[optionSelected].setFillColor( sf::Color(255,255,255) );
	}
	else if(vLoop && optionSelected!=-1)
	{
		optionsText[optionSelected].setFillColor( sf::Color(112,112,112) );
		optionSelected+=row-1;
		correctError();
		optionsText[optionSelected].setFillColor( sf::Color(255,255,255) );
	}
}

void Menu::moveDown()
{
	if((optionSelected+1)%row && optionSelected!=-1)
	{
		optionsText[optionSelected].setFillColor( sf::Color(112,112,112) );
		optionSelected+=1;
		correctError();
		optionsText[optionSelected].setFillColor( sf::Color(255,255,255) );
	}
	else if(vLoop && optionSelected!=-1)
	{
		optionsText[optionSelected].setFillColor( sf::Color(112,112,112) );
		optionSelected-=row-1;
		correctError();
		optionsText[optionSelected].setFillColor( sf::Color(255,255,255) );
	}
}

void Menu::moveLeft()
{
	if(optionSelected >= row && optionSelected!=-1)
	{
		optionsText[optionSelected].setFillColor( sf::Color(112,112,112) );
		optionSelected-=row;
		correctError();
		optionsText[optionSelected].setFillColor( sf::Color(255,255,255) );
	}
	else if(hLoop && optionSelected!=-1)
	{
		optionsText[optionSelected].setFillColor( sf::Color(112,112,112) );
		optionSelected+=row*(col-1);
		correctError();
		optionsText[optionSelected].setFillColor( sf::Color(255,255,255) );
	}
}

void Menu::moveRight()
{
	if( optionSelected < ( (col-1) * row)  && optionSelected!=-1)
	{
		optionsText[optionSelected].setFillColor( sf::Color(112,112,112) );
		optionSelected+=row;
		correctError();
		optionsText[optionSelected].setFillColor( sf::Color(255,255,255) );
	}
	else if(hLoop && optionSelected!=-1)
	{
		optionsText[optionSelected].setFillColor( sf::Color(112,112,112) );
		optionSelected%=row;
		correctError();
		optionsText[optionSelected].setFillColor( sf::Color(255,255,255) );
	}
}

bool Menu::correctError()
{
	while(optionSelected>=row*col)
		optionSelected-=row;
	while(optionSelected<0)
		optionSelected+=row;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//									GENERAL FUNCTIONS												//


void Menu::changeSize(sf::Text (&TEXT)[TXT_N], int newSize)
{
	for(int i=0;i<TXT_N;i++)
		TEXT[i].setCharacterSize(newSize);
}


bool Menu::remakeLow(int width, int height, sf::Text text[], bool Title)
{
	box=true; title=Title; vLoop=false; hLoop=false; optionSelected=0;
	row=2; col=2;
	
	sf::FloatRect rect(width*3/100, height*75/100, width*(94)/100, height*(22)/100 );
	sf::FloatRect rectTxt(0,0,0,0);
	if(!title)
	{
		rectTxt.left	= width*3/100;
		rectTxt.top		= height*75/100;
		rectTxt.width	= width*94/100;
		rectTxt.height	= height*22/100;
	}
	else
	{
		rectTxt.left	= width*42/100;
		rectTxt.top		= height*75/100;
		rectTxt.width	= width*55/100;
		rectTxt.height	= height*22/100;
	}
		
	
		
	rect_box.setSize(sf::Vector2f(rect.width, rect.height) );
	rect_box.setPosition(rect.left,rect.top);
	rect_box.setOutlineThickness( height*0.75/100 );
	rect_box.setFillColor( sf::Color(12,0,18) );
	rect_box.setOutlineColor( sf::Color(224,224,224) );
	
	if(title)
	{
		int t=row*col;
		optionsText=new sf::Text[t+1];
		optionsText[t].setFont(* text[t].getFont() );
		optionsText[t].setString(text[t].getString() );
		optionsText[t].setCharacterSize(DEFAULT_SIZE*1.2);
		optionsText[t].setOrigin( 0 , (optionsText[t].getLocalBounds().height)/2 );
		optionsText[t].setPosition( rect.left + rect.width * 4/100, rect.top + rect.height/2 );
		optionsText[t].setFillColor( sf::Color(224,224,224) );
	}
	else
		optionsText=new sf::Text[row*col];
	
	
	for(int j=0;j<col;j++) 
	{
		for(int i=0;i<row;i++)
		{
			int k = j*row + i;
			optionsText[k].setFont(* text[0].getFont() );
			optionsText[k].setString(text[k].getString() );
			optionsText[k].setCharacterSize(DEFAULT_SIZE*0.8);
			optionsText[k].setOrigin( 0 , (optionsText[k].getLocalBounds().height)/2 );
			optionsText[k].setPosition( rectTxt.left + 10 + rectTxt.width / (col) * (j) ,
										rectTxt.top + rectTxt.height / (row+1) * (i+1) );
				
			if(k==optionSelected)
				optionsText[k].setFillColor( sf::Color(255,255,255) );
			else
				optionsText[k].setFillColor( sf::Color(112,112,112) );
			k++;
		}
	}
	return true;
}

bool Menu::remakeTxt(int width, int height, sf::Text text[], bool Title)
{
	box=true; title=Title; vLoop=false; hLoop=false; optionSelected=-1;
	row=7; col=1;


	sf::FloatRect rect(width*3/100, height*3/100, width*94/100, height*69/100 );
	sf::FloatRect rectTxt (0,0,0,0);
	if(!title)
	{
		rectTxt.left	= width*5/100;
		rectTxt.top		= height*5/100;
		rectTxt.width	= width*90/100;
		rectTxt.height	= height*65/100;
	}
	else
	{
		sf::Text bigText;
		bigText.setFont(* text[row].getFont() );
		bigText.setString(text[row].getString() );
		bigText.setCharacterSize(BIG_SIZE);
		rectTxt.left	= width*5/100;
		rectTxt.top		= height*6/100 + bigText.getLocalBounds().height;
		rectTxt.width	= width*90/100;
		rectTxt.height	= height*65/100 - bigText.getLocalBounds().height;
	}
		
	rect_box.setSize(sf::Vector2f(rect.width, rect.height) );
	rect_box.setPosition(rect.left,rect.top);
	rect_box.setOutlineThickness( height*0.75/100 );
	rect_box.setFillColor( sf::Color(12,0,18) );
	rect_box.setOutlineColor( sf::Color(224,224,224) );
	
	if(title)
	{
		int t=row;
		optionsText=new sf::Text[t+1];
		optionsText[t].setFont(* text[t].getFont() );
		optionsText[t].setString(text[t].getString() );
		optionsText[t].setCharacterSize(BIG_SIZE);
		optionsText[t].setOrigin( (optionsText[t].getLocalBounds().width)/2 , (optionsText[t].getLocalBounds().height)/2 );
		optionsText[t].setPosition( rectTxt.left + rectTxt.width / 2, rectTxt.top - optionsText[t].getLocalBounds().height / 2 - height / 100 );
		optionsText[t].setFillColor( sf::Color(224,224,224) );
	}
	else
		optionsText=new sf::Text[row];
	

	for(int i=0;i<row;i++)
	{
		optionsText[i].setFont(* text[0].getFont() );
		optionsText[i].setString(text[i].getString() );
		optionsText[i].setCharacterSize( DEFAULT_SIZE );
		
		int correctSize = DEFAULT_SIZE;
		while(optionsText[i].getLocalBounds().width >= rectTxt.width*0.98) //makes sure text fits screen
		{
			correctSize--;
			optionsText[i].setCharacterSize( correctSize );
		}
		
		optionsText[i].setOrigin( /* ( optionsText[i].getLocalBounds().width)/2 */ 0 , (optionsText[i].getLocalBounds().height)/2 );
		optionsText[i].setPosition( rectTxt.left + rectTxt.width/100 ,
									rectTxt.top + height/100 + rectTxt.height / 8 * (i+1) ); //lines qtd will be 8-1=7
				
		optionsText[i].setFillColor( sf::Color(223,191,223) );

	}

	return true;
}


void Menu::featureDisabled(sf::RenderWindow &window)
{
	sf::RectangleShape darkness;
	darkness.setSize(sf::Vector2f(window.getSize().x,window.getSize().y) );
	darkness.setPosition(0,0);
	darkness.setFillColor( sf::Color(8,0,10,128) );
	
	sf::Font font;
	font.loadFromFile("fonts/Adventurer.ttf");
	
	sf::Text txt[1];
	txt[0].setFont(font);
	txt[0].setCharacterSize(DEFAULT_SIZE);
	txt[0].setString("Oops, that's embarrassing...");
	
	Menu auxmenu;
	auxmenu.remake(window.getSize().x,window.getSize().y,1,1,txt,20,40,80,60,true,false,false,false,3,35,97,65,true);
	
	window.draw(darkness);
	auxmenu.draw(window);
    window.display();
    sf::Event event;
    //sf::sleep(sf::milliseconds(1000));
    while( event.type!=sf::Event::KeyPressed || event.key.code!=sf::Keyboard::Return )//!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) )
	{
		window.pollEvent(event);
		if (event.type==sf::Event::Closed)
            window.close();
	}
}

