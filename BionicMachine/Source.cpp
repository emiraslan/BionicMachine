#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>       // std::string
#include <sstream>
#include "string.h"
#include <cstring>
#include <ctime>
#include <sstream>
#include <cctype>
#include <fstream>
#include <algorithm>
using namespace std;

int main_134()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1000, 600), "BionicMachine by Harmonica v1.0");

	sf::Font font;

	sf::Sound sound1;
	sf::Sound main;

	sf::Texture texture;
	sf::Texture redTexture; 
	sf::Texture Monster;
	sf::Texture Background;

	sf::SoundBuffer buffer;
	sf::SoundBuffer back;

	sf::Text text;

	sf::Sprite sprite;
	sf::Sprite sprite2;
	sf::Sprite monster;
	sf::Sprite background;

	sf::Time delayTime = sf::milliseconds(10);

	int score = 0;
	int Height = 0;
	int Width = 0;
	int increase = 1;
	
	bool collide = false;

	if (!buffer.loadFromFile("Shoot.wav"))
	{
		cout << "Eorroro " << endl;
	}
	if (!back.loadFromFile("EvilSong.wav"))
	{
		cout << "Eorro2ro " << endl;
	}

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Erorroororo " << std::endl;
	}
	if (!texture.loadFromFile("BlackCross.png"))
	{
		std::cout << "Cannot load the image from the file !!!\n";
	}
	if (!redTexture.loadFromFile("RedCross.png"))
	{
		std::cout << "Cannot load the image from the file !!!\n";
	}
	if (!Monster.loadFromFile("Monster.png"))
	{
		std::cout << "Cannot load the image from the file !!!\n";
	}
	if (!Background.loadFromFile("Background.png"))
	{
		std::cout << "Cannot load the image from the file !!!\n";
	}
	

	main.setBuffer(back);
	sound1.setBuffer(buffer);

	main.play();

	window.setMouseCursorVisible(false);
	sf::Vector2i loc = sf::Vector2i(100, 40);
	window.setPosition(loc);
		
	text.setFont(font);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);

	sprite.setTexture(texture);
	monster.setTexture(Monster);
	background.setTexture(Background);

	sprite.setTextureRect(sf::IntRect(0  ,  0 , 600 , 600));
	sprite.setScale(sf::Vector2f(0.2, 0.2));
	
	monster.setTextureRect(sf::IntRect(150, 0, 470, 700));
	monster.setScale(sf::Vector2f(0.3, 0.3));
	
	background.setTextureRect(sf::IntRect(0, 0, 1000, 600));
	background.setScale(sf::Vector2f(1, 1));

	monster.setPosition(sf::Vector2f(rand()%900, rand()%500 ));

	{
		stringstream ss;
		ss << score;
		string str1 = ss.str();
		text.setString("Score : " + str1);
	}

	while (window.isOpen())
	{
		sf::Event event;
		sprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x-80 , sf::Mouse::getPosition(window).y - 80));

		if (sprite.getGlobalBounds().intersects(monster.getGlobalBounds()) && collide == false)
		{
			std::cout << "there is a collision" <<std::endl;
			sprite.setTexture(redTexture);
			collide = true;
		}
		else if(!sprite.getGlobalBounds().intersects(monster.getGlobalBounds()) && collide == true)
		{
			std::cout << "No collision !" << std::endl;
			sprite.setTexture(texture);
			collide = false;
		}

		while (window.pollEvent(event))
		{
			
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close(); // function that closes the window
				break;
			case sf::Event::MouseButtonPressed:
				if (sprite.getGlobalBounds().intersects(monster.getGlobalBounds()) )
				{
					stringstream ss;
					string str;

					score++;
					ss << score;
				    str = ss.str();
					text.setString("Score : " + str);

					monster.setPosition(sf::Vector2f(rand() % 900, rand() % 500));

					sound1.play();
				}
				break;
			}
		}
		
		sf::sleep(delayTime);

		window.draw(background);
		window.draw(monster);
		window.draw(sprite);
		window.draw(text);
		
		window.display();
	}

	return 0;
}