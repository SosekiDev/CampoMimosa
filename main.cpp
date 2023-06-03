#include <SFML/Audio.hpp>
#include <iostream>
#include "classes/screens.hpp"

int main()
{	 
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	
	float gameWidth=900;
	float gameHeight=600;
	
	sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight,32), "Campo Mimosa", sf::Style::Close);
	window.setFramerateLimit(30);
	window.setKeyRepeatEnabled(false);
	
	std::vector<screenSwitch*> Screens;
	int screen=0;
	
	//MainMenu s0;
	//Screens.push_back(&s0);
	MainMenu s0;
	Screens.push_back(&s0);
	Difficulty s1;
	Screens.push_back(&s1);
	Playing s2;
	Screens.push_back(&s2);
	CustomDifficulty s3;
	Screens.push_back(&s3);
	Leaderboard s4;
	Screens.push_back(&s4);
	Options s5;
	Screens.push_back(&s5);
	int vol = 50;
	{
		std::ifstream iVolume;
		iVolume.open("bin/volume", std::fstream::in | std::fstream::binary);
		if(iVolume)
		{
			iVolume.read(reinterpret_cast<char*>(&vol), sizeof(int));
			iVolume.close();
		}
		else
		{
			std::ofstream oVolume;				
			oVolume.open ("bin/volume", std::fstream::out | std::fstream::trunc | std::fstream::binary);
			oVolume.write( reinterpret_cast<const char*>(&vol), sizeof(int) );
			oVolume.close();
		}
		sf::Listener::setGlobalVolume(vol);
	}
	
	sf::Music moo;
	moo.openFromFile("sound/moo_intensifies.ogg");
	moo.setVolume(vol*10/100.f);
	moo.play();
	moo.setLoop(true);
	
	while (screen >= 0)
	{
		screen=Screens[screen]->update(window);
		
		if( screen!=1 && screen!=2 && screen!=3 )
		{
			if(moo.getStatus() == sf::SoundSource::Status::Paused)
				moo.play();
		//	if(moo.getVolume() < vol)
		//		moo.setVolume( moo.getVolume() + 1*vol/1000.f );
			
		}
		else 
		{
		//	if(moo.getVolume() > 0)
		//		moo.setVolume( moo.getVolume() - 1*vol/1000.f );
		//	if(moo.getVolume() <= 0.1 &&
			if(moo.getStatus() == sf::SoundSource::Status::Playing)
				moo.pause();
		}
	}
    window.close();
    std::cout<<"Game closed";
    return EXIT_SUCCESS;
}

