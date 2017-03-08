#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include <Windows.h>
#include <vector>
#include <string>
//#include "Character.h"

struct Data;
class PhPhysicalCharacteristics;
class Player;

bool right_enable;
bool left_enable;
bool down_enable;
bool up_enable;

struct Dimension
{	
	float x, y;
};

struct Data 
{
	float jumpF = 190;
	float gravityAcceleration = 9.8;

};

class PhysicalCharacteristics_new
{
protected:
	
public:
	float mass;

	float speedValue = 0;
	float speedAngle = 0;
	
	float accelerationValue = 0;
	float accelerationAngle = 0;

};

class Player : public PhysicalCharacteristics_new
{
public:
	sf::Sprite playerSprite;
	
	sf::Sprite topSprite;
	sf::Sprite leftSprite;
	sf::Sprite rightSprite;
	sf::Sprite bottomSprite;

	struct massCenter
	{
		float x;
		float y;
	};

	Player()
	{
	}

	massCenter GetMassCenter()
	{
		massCenter mc;

		mc.x = playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width / 2);
		mc.y = playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height / 2);

		return mc;
	}

};

int main()
{
	std::ifstream openfile("Map1.txt");
	
	Dimension screenDimension;
	
	screenDimension.x = 1180;
	screenDimension.y = 690;

	sf::RenderWindow window(sf::VideoMode(screenDimension.x, screenDimension.y, 64), "BionicMachine v2.0");

	Player pack;
	Player enemy[20];

	Data dat;

	sf::Clock delta;
	sf::Clock clock;

	sf::Vector2f position(0, 0);
	
	sf::Texture backgroundTex;
	sf::Texture tileTexture;
	sf::Texture playerTex;
	sf::Texture EnemyTex;
	sf::Texture groundTex;
	sf::Texture CoinTex;
	sf::Texture textureBox;
	sf::Texture supportTexture;
	sf::Texture texDoor;

	sf::Sprite door;
	sf::Sprite backgroundSprite;
	sf::Sprite tiles;
	sf::Sprite  ground;
	sf::Sprite coin[20];
	sf::Sprite box[300];
	
	sf::Text text1;
	sf::Text text;
	sf::Font font;
	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<std::vector<int>> Colmap;

	std::vector<sf::Vector2i> tempMap;
	std::vector<int> tempMapCol;
	
	sf::View view;	
	sf::SoundBuffer a;
	sf::Sound mu;

	float deltaTime;
	bool whileJump = false;
	float move_speed = 10;
	bool game_over = false;
	right_enable = true;
	left_enable  = true;
	down_enable = true;
	up_enable = true;
	int potential = 609;
	int score = 0;
	pack.mass = 40;
	bool CoinToucing = false;
	view.reset(sf::FloatRect(0, 0, screenDimension.x, screenDimension.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	
	text.setColor(sf::Color::Green);
	

	if (!supportTexture.loadFromFile("playerSupport.png"))
	{
		std::cout << "Player support could not be loaded !!! " << std::endl;
	}
	if (!a.loadFromFile("EvilSong.wav"))
	{
		std::cout << "Eorro2ro " << std::endl;
	}
	if (!CoinTex.loadFromFile("coin.png"))
	{
		std::cout << "Error!!! not loaded coin !!!! .... \n";
	}
	if (!groundTex.loadFromFile("ground1.png")) {
		std::cout << "Error !!! ground Texture could not be loaded !!! \n";
	}
	if (!backgroundTex.loadFromFile("seamless_background.jpg"))
	{
		std::cout << "Error !!! backgroundTex could not be loaded !!! \n";
	}
	if (!playerTex.loadFromFile("player1.png"))
	{
		std::cout << "Player Texture could not be loaded !!!  \n";
	}
	if (!EnemyTex.loadFromFile("enemy.png"))
	{
		std::cout << "Enemy Png could not be loaded !!!\n";
	}
	if (!textureBox.loadFromFile("box1.png"))
	{
		std::cout << "Box can be loaded !!! \n";
	}
	if (!texDoor.loadFromFile("door.png"))
	{
		std::cout << "There is a mistake with door !!!" << std::endl;
	}
	pack.playerSprite.setTexture(playerTex);
	pack.playerSprite.setPosition(sf::Vector2f(0, 609));
	
	pack.topSprite.setTexture(supportTexture);
	pack.leftSprite.setTexture(supportTexture);
	pack.rightSprite.setTexture(supportTexture);
	pack.bottomSprite.setTexture(supportTexture);

	door.setTexture(texDoor);

	mu.setBuffer(a);

	ground.setTexture(groundTex);
	ground.setScale(sf::Vector2f(0.1, 0.12));
	ground.setColor(sf::Color(100 , 100, 220, 240));

	backgroundSprite.setTexture(backgroundTex);
	backgroundSprite.setScale(sf::Vector2f(0.62, 0.64));
	backgroundSprite.setTextureRect( sf::IntRect(0,0, 1920, 1080));

	for (int i = 0; i < 20; i++)
	{
		enemy[i].playerSprite.setTexture(EnemyTex);
		enemy[i].playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}

	for (int i = 0; i < 20; i++)
	{
		coin[i].setTexture(CoinTex);
		coin[i].setTextureRect(sf::IntRect(0, 0, 64, 64));
	}
	for (int i = 0; i < 300 ; i++)
	{
		box[i].setTexture(textureBox);
		box[i].setTextureRect(sf::IntRect(0, 0, 64, 64));
		box[i].setScale(sf::Vector2f(1.0f , 1.0f));
	}
	if (openfile.is_open())
	{
		std::string tileLocation;
		openfile >> tileLocation;
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture);
		while (!openfile.eof())
		{
			std::string str;
			openfile >> str;
			char x = str[0], y = str[2];  
			if (!isdigit(x) || !isdigit(y))
				tempMap.push_back(sf::Vector2i(-1, -1));
			else
				tempMap.push_back(sf::Vector2i(x - '0', y - '0'));
			
			if (openfile.peek() == '\n')
			{
				map.push_back(tempMap);
				tempMap.clear();
			}
			
		}
		map.push_back(tempMap);
	}
	
	int count_intersect = 0;
	int amount = 0;
	bool collision = false;
	bool Touch = false;
	//int collisionEnabled = 1;
	mu.play();


	while (window.isOpen())  // Burda main loop acilir
	{
		pack.topSprite.setPosition(pack.playerSprite.getPosition().x + 8, pack.playerSprite.getPosition().y - 5);
		pack.bottomSprite.setPosition(pack.playerSprite.getPosition().x + 8, pack.playerSprite.getPosition().y + 21);
		pack.leftSprite.setPosition(pack.playerSprite.getPosition().x - 5, pack.playerSprite.getPosition().y + 8);
		pack.rightSprite.setPosition(pack.playerSprite.getPosition().x + 21, pack.playerSprite.getPosition().y + 8);


		sf::Event Event;
		int count_enemy = 19;
		int count_coin = 19;
		int count_box = 300;
		deltaTime = delta.restart().asSeconds();

		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Space && whileJump == false)
			{
				pack.speedValue = dat.jumpF / pack.mass;
				whileJump = true;
				left_enable = true;
				right_enable = true;
			}
		}
		if (whileJump)
		{
			////////// Burda Jump var
			Data date;

			pack.speedValue -= date.gravityAcceleration*0.008;
			pack.playerSprite.move(0, -pack.speedValue);
		//	std::cout << "Bura : " << pack.speedValue << std::endl;

			if (pack.playerSprite.getPosition().y > 609)
			{
				pack.playerSprite.setPosition(pack.playerSprite.getPosition().x, 609);
				whileJump = false;
				//collisionEnabled = 1;
				pack.accelerationValue = 0;
			}
		}
		
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && 1)
			{
				
				pack.playerSprite.move(-400 * deltaTime, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && 1)
			{
				
				pack.playerSprite.move(400 * deltaTime, 0);
			}
		
	
		window.clear();
		
		position.x = pack.playerSprite.getPosition().x + 10 - (screenDimension.x / 2);
		position.y = pack.playerSprite.getPosition().y + 10 - (screenDimension.y / 2); 

		if (position.x < 0)
			position.x = 0;
		if (position.y < 0)
			position.y = 0;

		text.setPosition(sf::Vector2f(position.x+5, 0 ));
		view.reset(sf::FloatRect(position.x, 0, screenDimension.x, screenDimension.y));
		
		window.setView(view);

		Touch = false;

		//CoinToucing = false;
		for (int i = 0; i < map.size(); i++) 
		{
			for (int j = 0; j < map[i].size(); j++)
			{
	
				 if (map[i][j].x == 8 && map[i][j].y == 8 )
				{
					box[--count_box].setPosition(j * 64, i*64);
					window.draw(box[count_box]);

					if (pack.playerSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds()))
					{
						while (	
							pack.playerSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds()) && 
							pack.bottomSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds())
							)
						{
							pack.playerSprite.move(0, -1);
							whileJump = false;
						}
						
						while (
							pack.playerSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds()) &&
							pack.topSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds())
							)
						{
							pack.playerSprite.move(0, 1);	
							pack.speedValue = -2.0;
						}
						
						while (
							pack.playerSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds()) &&
							pack.rightSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds())
							)
						{
							
							pack.playerSprite.move(-2, 0);
						}

						while (
							pack.playerSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds()) &&
							pack.leftSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds())
							)
						{
							pack.playerSprite.move(2, 0);
						}
						
						
					}

					 if (pack.bottomSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds()) && !whileJump && !Touch )
						 Touch = true;
					 
					
				}
				else if (map[i][j].x == 2 && map[i][j].y == 2)
				{
					backgroundSprite.setPosition(j * 1190, 0);
					window.draw(backgroundSprite);
				}
				else if (map[i][j].x == 9 && map[i][j].y == 9)
				{
					enemy[count_enemy].playerSprite.setPosition(sf::Vector2f(j*64 , i*64));
					window.draw(enemy[count_enemy].playerSprite);
					if (pack.playerSprite.getGlobalBounds().intersects(enemy[count_enemy].playerSprite.getGlobalBounds()))
					{
						
						text1.setFont(font);
						text1.setCharacterSize(144);
						text1.setColor(sf::Color::Red);
						//text1.setScale(sf::Vector2f(3.0f , 3.0f));
						text1.setPosition(sf::Vector2f(position.x + 200, 250));
						text1.setString("You Died !!!");
						game_over = true;
					}
					count_enemy--;
				}
				else if (map[i][j].x == 7 && map[i][j].y == 7)
				{
					door.setPosition(j * 64, i * 30);
					
					if (pack.playerSprite.getGlobalBounds().intersects(door.getGlobalBounds()))
					{
						text1.setFont(font);
						text1.setCharacterSize(144);
						text1.setColor(sf::Color::Green);
						//text1.setScale(sf::Vector2f(3.0f , 3.0f));
						text1.setPosition(sf::Vector2f(position.x + 200, 250));
						text1.setString("You Win !!!");
						mu.stop();
						game_over = true;
					}

					window.draw(door);
					

				}
				else if (map[i][j].x == 4 && map[i][j].y == 4)
				{
					coin[count_coin].setPosition(j * 64, i * 64);
					CoinToucing = false;
					if (pack.playerSprite.getGlobalBounds().intersects(coin[count_coin].getGlobalBounds()))
					{
						// Music should be written
						map[i][j].x = -1;
						map[i][j].y = -1;
						score++;
						//std::cout << score << std::endl;
					}
					
					window.draw(coin[count_coin]); 
					count_coin--;

				}
				else if (map[i][j].x != -1 && map[i][j].y != -1)
				{
					tiles.setPosition(j * 64 , i * 64);
					tiles.setTextureRect(sf::IntRect(0, 0, 64, 64));
					window.draw(tiles);

					if (pack.playerSprite.getGlobalBounds().intersects(box[count_box].getGlobalBounds()))
					{
						count_intersect++;
					}
				}				
			}
		}
		
		if (!Touch && !whileJump && pack.playerSprite.getPosition().y != 609)
		{
			whileJump = true;
			pack.speedValue = -1.0f;
			//std::cout << "Hoppa !!!" << std::endl;
		}
		/*if (CoinToucing)
		{
			CoinToucing = false;
		}
		*/
		std::stringstream ss;
		ss << score;
		std::string str = ss.str();
		text.setString("   Score : " + str);
		if (game_over)
		{
			window.draw(text1);
			window.display();
			Sleep(2000);
			return 0;
		}
		
		window.draw(pack.playerSprite);
		window.draw(text);
		window.display();
	}

	return 0;
}