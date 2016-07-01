#include "SFML\Graphics.hpp"
#include <iostream>


int Second_main() 
{
	sf::RenderWindow window(sf::VideoMode(600 , 600 ) , "SFML WORKS");

	while (window.isOpen()) 
	{

		sf::Event event;

		while (window.pollEvent(event)) 
		{
			switch (event.type)
			{
				case sf::Event::Closed :
					window.close(); // function that closes the window
					break;

				case sf::Event::KeyPressed :
					std::cout << "the Key is Pressed !" << "  " << event.key.code << std::endl;

					switch (event.key.code)
					{
					case sf::Keyboard::A:
						std::cout << "A Key is Pressed !" << std::endl;
						break;
					default:
						break;
					}

					break;

				case sf::Event::KeyReleased:
					std::cout << "The Key you pressed is released by others !!!" << std::endl;
					switch (event.key.code)
					{
					case sf::Keyboard::B:
						std::cout << "B Key is Released !" << std::endl;
						break;
					default:
						break;
					}
					break;

				case sf::Event::MouseButtonPressed:
					std::cout << "Mouse button is Pressed !" << std::endl;
					switch (event.key.code)
					{
					case sf::Mouse::Left:
						std::cout << "Left Button is Pressed!" << std::endl;
						break;
					default:
						break;
					}
					break;

				case sf::Event::MouseWheelMoved:
					std::cout << "Mouse Wheel Moved !" << std::endl;
					std::cout << event.mouseWheel.delta << std::endl;
					break;
				case sf::Event::MouseMoved:
					//std::cout << "Mouse Moved !" << std::endl;
					
					break;
				case sf::Event::MouseEntered:
					std::cout << "Mouse Entered Window !" << std::endl;

					break;
				case sf::Event::MouseLeft:
					std::cout << "Mouse Left Window !" << std::endl;

					break;
				case sf::Event::Resized:
					std::cout << event.size.width <<" : "<< event.size.height << std::endl;

					break;
				case sf::Event::GainedFocus:
					std::cout <<"Focused !" << std::endl;

					break;
				case sf::Event::LostFocus:
					std::cout << "Lost Focus !" << std::endl;

					break;

			}
		}
		window.clear();
		window.display();
	}
	return 0;
}