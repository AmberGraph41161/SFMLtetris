#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

/*

	"standard Tetris board is 10 wide and 20 high"
	"The client code may create a taller board such as 10x24,
	to allow extra space at the top for the pieces to fall into play"

	XXXX    //I-block_LIGHT-BLUE

	X	//J-block_DARK-BLUE
	XXX

	  X	//L-block_ORANGE
	XXX

	XX	//O-block_YELLOW
	XX

	 XX	//S-block_LIGHT-GREEN
	XX

	 X	//T-block_PURPLE
	XXX

	XX	//Z-block_RED
	 XX
*/

int main()
{
	sf::RenderWindow window(sf::VideoMode(300, 500), "SFML Tetris Clone");

	while(window.isOpen())
	{
		//Event handling
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}


		//CLEAR and DISPLAY objects
		window.clear(sf::Color::Black);
		
		window.display();
	}
}
