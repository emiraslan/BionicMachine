#include "SFML\Graphics.hpp"
#include <iostream>


int main3()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML WORKS");

	while (window.isOpen())
	{

		sf::Event event;

		while (window.pollEvent(event))
		{
			//system("pause");
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close(); // function that closes the window
				break;

			
			case sf::Event::TextEntered:
				std::cout << "Text was Entered !" << std::endl;
				if (event.text.unicode == 65) 
				{
					std::cout << "Something happened" << std::endl;
				}
				break;


			}
		}
		
		/*
		if (sf::Keyboard::isKeyPressed) 
		{
			std::cout << "Jumping right now !" << std::endl;
		}
		*/

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		{
			std::cout << "Fire !!" << std::endl;
		}

		//std::cout << sf::Mouse::getPosition().y << std::endl;
		std::cout << sf::Mouse::getPosition(window).y << std::endl;

		sf::Mouse::setPosition(sf::Vector2i(40, 60) , window);

		window.clear();
		window.display();
	}
	return 0;
}