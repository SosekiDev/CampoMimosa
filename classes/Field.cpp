#include "Field.h"
#include <iostream>
#include <fstream>
#include<cmath>

#define size 80/100.0

Field::Field()
{
	
}

Field::Field(sf::RenderWindow *window, /*int width, int height, int Row, int Col, int Bombs,*/ sf::Clock *Time)
{	//set values
//	row=Row;
//	col=Col;
//	bombs=bombsLeft=Bombs;
	windowPtr=window;
	int width=windowPtr->getSize().x, height=windowPtr->getSize().y;
	newField=true;
	time=Time;
	
	std::ifstream fieldInit;
	fieldInit.open("bin/init", std::fstream::in | std::fstream::binary);
	if(fieldInit)
	{
		fieldInit.read(reinterpret_cast<char*>(&row), sizeof(int));
		fieldInit.read(reinterpret_cast<char*>(&col), sizeof(int));
		fieldInit.read(reinterpret_cast<char*>(&bombs), sizeof(int));
		fieldInit.close();
	}
	else
	{
		row=16; col=16; bombs=40;
	}
	
	bombsLeft=bombs;
	
	//the field will be on bottom left and the bigger size (proportionally to the window's size) will ocuppy 80% of window's size		
	rect.left	= width*2/100;
	rect.top	= ( (1.0*width/height > 1.0*col/row) ? height*98/100 - height*size		: height*98/100 - width*size * row/col);
	rect.width	= ( (1.0*width/height > 1.0*col/row) ? height*size * col/row			: width*size );
	rect.height	= ( (1.0*width/height > 1.0*col/row) ? height*size						: width*size * row/col );
	
	//creates matrixes and initialize vith value 0
	trueField = (int **)calloc( row, sizeof(int *) );
	maskField = (int **)calloc( row, sizeof(int *) );
	clickable = (bool **)calloc( row, sizeof(bool *) );
	for (int i=0; i<row; i++)
	{
		trueField[i] = (int *)calloc( col, sizeof(int) );
		maskField[i] = (int *)calloc( col, sizeof(int) );
		clickable[i] = (bool *)calloc( col, sizeof(bool) );
	}
	
	//sets mask because it will appear before field is created
	for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
		{
			maskField[i][j]=9;
			clickable[i][j]=true;
		}
   	
   	//initialize field graphics
	if(!tilemap.loadFromFile("img/campo_mimosa_tilemap.png"))
		std::cout<<"Error loading field\n";
	tilemap.setSmooth(true);
	sprite.setTexture(tilemap);
	sprite.setScale(rect.width/(col*tilemap.getSize().x/4.f)*0.95, rect.height/(row*tilemap.getSize().y/3.f)*0.95);
	
	font.loadFromFile("fonts/munro.ttf");
	
	bombsTxt.setFont(font);
	bombsTxt.setString(std::to_string(bombsLeft));
	bombsTxt.setCharacterSize(72);
	bombsTxt.setPosition( width*5/100, height*2/100 );
	bombsTxt.setFillColor( sf::Color(32,64,128,2) );
	
	timeTxt.setFont(font);
	timeTxt.setCharacterSize(72);
	timeTxt.setFillColor( sf::Color(32,64,128,2) );
	
	//initialize background graphics
	if(!bgTexture.loadFromFile("img/fundomanero.png"))
		std::cout<<"Error loading background\n";
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(1.0*width/bgTexture.getSize().x, 1.0*height/bgTexture.getSize().y);
}

Field::~Field()
{
	time=nullptr;
	windowPtr=nullptr;
	for (int i=0; i<row; i++)
	{
		free(trueField[i]);
		free(maskField[i]);
		free(clickable[i]);
	}
	free(trueField);
	free(maskField);
	free(clickable);
}

void Field::draw(sf::Vector2i mousePos)
{
	windowPtr->draw(bgSprite);
	
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			sprite.setTextureRect(getSpriteRect(maskField[i][j]) );
			sprite.setPosition(	rect.left + j * rect.width / col,  rect.top + i * rect.height / row);
			
			if(clickable[i][j] && sf::IntRect(sprite.getGlobalBounds()).contains(mousePos) )//.contains(float(mousePos.x), float(mousePos.y)) )
			{
				tilemap.loadFromFile("img/campo_mimosa_tilemap_selected.png");
				windowPtr->draw(sprite);
				tilemap.loadFromFile("img/campo_mimosa_tilemap.png");
			}
			else
				windowPtr->draw(sprite);
			
			if(!newField)
			{
				if(victorious || defeated)
					timeTxt.setString( std::to_string( int( endtime ) ) );
				else
					timeTxt.setString( std::to_string( int( getTime() ) ) );
				
				timeTxt.setPosition(rect.left + rect.width/2 - timeTxt.getGlobalBounds().width/4, windowPtr->getSize().y*2/100 );
			}
			windowPtr->draw(timeTxt);
			windowPtr->draw(bombsTxt);
			//std::cout<<j*rect.width/col<<' ';
			//std::cout<<sprite.getPosition().x<<','<<sprite.getPosition().y<<"  ";
		}
		//std::cout<<'\n';
	}
	return;
}

// gets tilemap rects for each sprite
sf::IntRect Field::getSpriteRect(int n) // 0-8: number of bombs		9:mask		10:flag		11:bomb
{
	return( sf::IntRect(	(tilemap.getSize().x/4) * (n%4),	(tilemap.getSize().y/3) * (n/4),
							tilemap.getSize().x/4,				tilemap.getSize().y/3 ) );
}

//creates field when player chooses first square
void Field::createField (int x, int y) 
{
	//preset field and mask
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			trueField[i][j]=0; //calloc sets it to 0 already, but lets make sure
			//maskField[i][j]=9;  //may be useful in case of replay
		}
	}
	
	//distribute bombs making sure starting square will have zero bombs nearby
    for(int i=0; i<bombs; i++)
	{
		int randa=rand()%row, randb=rand()%col;
        if(trueField[randa][randb] != 11 && ( randa<x-1 || randa>x+1 || randb<y-1 || randb>y+1 ) )
			trueField[randa][randb] = 11;
    	else i--;
	}
	
	//fill the numbers
	for(int i=0; i<row; i++)
	{
        for(int j=0; j<col; j++)
		{
            int bombN=0;
           
            if(trueField[i][j]!=11)
			{
                for(int k=( (i>0) ? i-1 : i ); k<=( (i<row-1) ? i+1 : i ); k++)
                    for(int l=( (j>0) ? j-1 : j ); l<=( (j<col-1) ? j+1 : j ); l++)
                        if(trueField[k][l]==11) bombN++;
                            
                trueField[i][j]=bombN;
            }
        }
    }
    time->restart();
    return;
}

sf::Vector2i Field::getSel(sf::Vector2i mousePos)
{
	sf::Vector2i coordinate;
	
	//return field coordinates
	if( 	rect.contains(mousePos) 
		&&	fmod( (mousePos.x - rect.left), (rect.width / float(col)) ) < sf::FloatRect(sprite.getGlobalBounds()).width
		&&	fmod( (mousePos.y - rect.top), (rect.height / float(row)) ) < sf::FloatRect(sprite.getGlobalBounds()).height )
	{
		coordinate.x = (mousePos.y - rect.top) / (rect.height / float(row));
		coordinate.y = (mousePos.x - rect.left) / (rect.width / float(col));
		return(coordinate);
	}
	
	//std::cout<<"error getting selected coordinates\n";
	return(sf::Vector2i (-1,-1));
}

//change mask when player clicks a square (returns: -1 == defeat, 1 == victory
int Field::open(sf::Vector2i mousePos)
{
	int x = getSel(mousePos).x, y = getSel(mousePos).y;
	if(x<0 || x>=row || y<0 || y>=col || !clickable[x][y] || maskField[x][y]>9 || maskField[x][y]==8)
	{
		if(victory()) return 1;
		if(defeat()) return -1;
		return 0;
	}
	
	if(newField)
	{
		createField(x,y);
		newField=false;
	}
	
	//makes it "explode" around safe squares
    if ( (trueField[x][y]==0 && maskField[x][y]==9) || maskField[x][y]!=9 )
	{
		maskField[x][y]=trueField[x][y];
        for(int i=( (x>0) ? x-1 : x ); i<=( (x<row-1) ? x+1 : x ); i++)
            for(int j=( (y>0) ? y-1 : y ); j<=( (y<col-1) ? y+1 : y ); j++)
				open(i,j); 

    }
    else
    	maskField[x][y]=trueField[x][y];
    
    setClickable();
    
    if(defeat()) return -1;
    if(victory()) return 1;
    
    return 0;
}

void Field::open(int x, int y)
{
	if(newField)
	{
		createField(x,y);
		newField=false;
	}
	
	if(!clickable[x][y] || maskField[x][y]==10) return;
	
	//makes it "explode" around safe squares
    if (trueField[x][y]==0 && maskField[x][y]!=0)
	{
		maskField[x][y]=trueField[x][y];
        for(int i=( (x>0) ? x-1 : x ); i<=( (x<row-1) ? x+1 : x ); i++)
            for(int j=( (y>0) ? y-1 : y ); j<=( (y<col-1) ? y+1 : y ); j++)
				open(i,j); 
    }
    else
    	maskField[x][y]=trueField[x][y];
    	
    return;
}

void Field::setClickable()
{
	for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
		{
			if(maskField[i][j] > 0 && maskField[i][j] < 8)
			{
				int flagN = 0;
				bool poppable = false;
				for(int k=( (i>0) ? i-1 : i ); k<=( (i<row-1) ? i+1 : i ); k++)
                    for(int l=( (j>0) ? j-1 : j ); l<=( (j<col-1) ? j+1 : j ); l++)
                    {
                    	if(maskField[k][l]==10) flagN++;
                    	else if(maskField[k][l]==9) poppable=true;
					}
				if(maskField[i][j]==flagN && poppable)
					clickable[i][j]=true;
				else clickable[i][j]=false;
			}
			else if(maskField[i][j] == 9 || maskField[i][j] == 10)
				clickable[i][j] = true;
			else clickable[i][j] = false;
		}
	return;
}

void Field::putFlag(sf::Vector2i mousePos)
{
	int x = getSel(mousePos).x, y = getSel(mousePos).y;
	if(x<0 || x>=row || y<0 || y>=col)
		return;
	
	if(maskField[x][y]==9)
	{
		maskField[x][y]=10;
		bombsLeft--;
	}
	else if(maskField[x][y]==10)
	{
		maskField[x][y]=9;
		bombsLeft++;
	}
		
	setClickable();
		
	bombsTxt.setString(std::to_string(bombsLeft));
		
	return;
}

bool Field::defeat()
{
	if(defeated) return true;
	
	for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
			if(maskField[i][j]==11)
			{
				//reveals all bombs
				for(int k=0; k<row; k++)
					for(int l=0; l<col; l++)
						if(trueField[k][l]==11 && maskField[k][l]!=11)
							maskField[k][l]=trueField[k][l];
				endtime=getTime();
				defeated=true;
				for(int k=0; k<row*col; k++)
					clickable[k/col][k%col]=false;
				return true;
			}
	return false;
}

bool Field::victory()
{
	if(victorious) return true;
	
	int k=0;
	
	for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
		{
			if(maskField[i][j]==9 || maskField[i][j]==10)
				k++;
			if(maskField[i][j]==11)
			{
				endtime=getTime();
				defeated=true;
				for(int k=0; k<row*col; k++)
					clickable[k/col][k%col]=false;
				return false;
			}
		}
	
	if(k==bombs)
	{
		endtime=getTime();
		victorious=true;
		for(int k=0; k<row*col; k++)
			clickable[k/col][k%col]=false;
		return true;
	}
	else return false;
}

int Field::getDifficulty() const
{
	if(row==9 && col==9 && bombs==10)
		return 1;
	if(row==16 && col==16 && bombs==40)
		return 2;
	if( ((row==20 && col==24) || (row==24 && col==20) || (row==16 && col==30) || (row==30 && col==16)) && bombs==99)
		return 3;
	return 0;
}

