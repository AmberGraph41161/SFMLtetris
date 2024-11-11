#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <array>
#include <cmath>
#include <cstdlib>

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "gamefunctions.hpp"

/*

	"standard tetris board is 10 wide and 20 high"
	"the client code may create a taller board such as 10x24,
	to allow extra space at the top for the pieces to fall into play"

	xxxx    //i-block_light-blue

	x	//j-block_dark-blue
	xxx

	  x	//l-block_orange
	xxx

	xx	//o-block_yellow
	xx

	 xx	//s-block_light-green
	xx

	 x	//t-block_purple
	xxx

	xx	//z-block_red
	 xx
*/

int RANDOM(int minimum, int maximum)
{
	return (rand() % (maximum - minimum + 1)) + minimum;
}

int main()
{
	srand(time(0));

	bool debug = true;

	enum blockType { iBlock, jBlock, lBlock, oBlock, sBlock, tBlock, zBlock };

	//as of Monday, November 11, 2024, 00:19:43, Block is vector for now. Might change to static array later. Dynamic cuz I might play around with it in future
	Block iBlockCoords({ {0, 0}, {1, 0}, {2, 0}, {3, 0} });
	Block jBlockCoords({ {0, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block lBlockCoords({ {2, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block oBlockCoords({ {0, 0}, {1, 0}, {0, 1}, {1, 1} });
	Block sBlockCoords({ {1, 0}, {2, 0}, {0, 1}, {1, 1} });
	Block tBlockCoords({ {1, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block zBlockCoords({ {0, 0}, {1, 0}, {1, 1}, {2, 1} });
	std::array<Block, 7> groupedBlockCollection;

	std::queue<Block> blockQueue;
	for(int x = 0; x <= 5; x++)
	{
		blockQueue.push(groupedBlockCollection[RANDOM(0, groupedBlockCollection.size() - 1)]);
	}

	const char blankChar = 'b';
	const char activeChar = 'a';
	const char inactiveChar = 'i';
	int boardWidth = 10;
	int boardHeight = 30;
	std::vector<std::vector<char>> board; //as of Wednesday, November 06, 2024, 10:25:44, I am reconsidering my choices as to have board[y][x]... maybe I will regret this later
	for(int y = 0; y < boardHeight; y++)
	{
		std::vector<char> pushBackRowVector(boardWidth);
		for(int x = 0; x < boardWidth; x++)
		{
			pushBackRowVector[x] = blankChar;
		}
		board.push_back(pushBackRowVector);
	}
	//board structure:
	/*
	(0, 0) top left of the board
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000	right side of the board
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
			0000000000
						(10, 30) bottom right of the board
	
		when moving active pieces, start from bottom of the board to the top of the board when shimming pieces down.
	*/

	sf::Sprite theBlock;
	sf::Texture diamondBlockTexture;
	if(!diamondBlockTexture.loadFromFile("textures/blocks/diamond_block.png"))
	{
		std::cerr << "failed to load \"textures/blocks/diamond_block.png\"" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Texture diamondOreTexture;
	if(!diamondOreTexture.loadFromFile("textures/blocks/diamond_ore.png"))
	{
		std::cerr << "failed to load \"textures/blocks/diamond_ore.png\"" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Texture wool_colored_pinkTexture;
	if(!wool_colored_pinkTexture.loadFromFile("textures/blocks/wool_colored_pink.png"))
	{
		std::cerr << "failed to load \"textures/blocks/wool_colored_pink.png\"" << std::endl;
		exit(EXIT_FAILURE);
	}
	theBlock.setTexture(diamondOreTexture);
	theBlock.setScale(sf::Vector2f(2, 2));

	int theBlockStartX = (1920.f / 2) - (theBlock.getGlobalBounds().width / 2); //temp. will make prettier later
	int theBlockStartY = 0;//(1080.f / 2) - (theBlock.getGlobalBounds().height / 2); //temp. will make prettier later

	std::chrono::time_point<std::chrono::system_clock> lastlastframe = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::system_clock> lastframe = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> deltaTime = lastframe - lastlastframe;
	std::chrono::duration<double> tickDelta = deltaTime;
	double tickDeltaThreshold = 0.4;

	int screenWidth = 1920;
	int screenHeight = 1080;
	sf::View view(sf::FloatRect(0, 0, screenWidth, screenHeight));
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "title goes here lol", sf::Style::Default);
	window.setFramerateLimit(60);
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			if(event.type == sf::Event::Resized)
			{
				//copied and pasted from SFMLflappybird for resizing logic. as of Tuesday, November 05, 2024, 11:40:24
				if((((float)window.getSize().x / 16) * 9) > window.getSize().y)
				{
					view.setViewport(sf::FloatRect(0.5 - (((((float)window.getSize().y / 9) * 16) / (float)window.getSize().x) / 2), 0, (((float)window.getSize().y / 9) * 16) / (float)window.getSize().x, 1));
				} else
				{
					view.setViewport(sf::FloatRect(0, 0.5 - (((((float)window.getSize().x / 16) * 9) / (float)window.getSize().y) / 2), 1, (((float)window.getSize().x / 16) * 9) / (float)window.getSize().y));
				}
				window.setView(view);
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			window.close();
		}
		/*
		if(debug && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){for(int x = 0; x < iBlockCoords.size(); x++){board[iBlockCoords[x].y][iBlockCoords[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){for(int x = 0; x < jBlockCoords.size(); x++){board[jBlockCoords[x].y][jBlockCoords[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){for(int x = 0; x < lBlockCoords.size(); x++){board[lBlockCoords[x].y][lBlockCoords[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){for(int x = 0; x < oBlockCoords.size(); x++){board[oBlockCoords[x].y][oBlockCoords[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){for(int x = 0; x < sBlockCoords.size(); x++){board[sBlockCoords[x].y][sBlockCoords[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){for(int x = 0; x < tBlockCoords.size(); x++){board[tBlockCoords[x].y][tBlockCoords[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){for(int x = 0; x < zBlockCoords.size(); x++){board[zBlockCoords[x].y][zBlockCoords[x].x] = activeChar;}}
			
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				for(int y = 0; y < board.size(); y++)
				{
					for(int x = 0; x < board[y].size(); x++)
					{
						if(board[y][x] == activeChar)
						{
							board[y][x] = inactiveChar;
						}
					}
				}
			}
		}
		*/

		//bool tick = false;
		if(tickDelta.count() >= tickDeltaThreshold)
		{
			tickDelta = std::chrono::seconds::zero();
			//tick = true;
			updateBoard(board, blankChar, activeChar, inactiveChar);
			updateFullRows(board, blankChar, activeChar, inactiveChar);

			/*
			if(debug)
			{
				std::cout << std::string(boardWidth, '-') << std::endl;
				printBoard(board);
			}
			*/
		}
		tickDelta += deltaTime;

		if(!activePiecesExistOnBoard(board, blankChar, activeChar, inactiveChar))
		{
			placeBlockAsActivePieces(board, iBlockCoords, blankChar, activeChar, inactiveChar);
			blockQueue.pop();
			blockQueue.push(groupedBlockCollection[RANDOM(0, groupedBlockCollection.size() - 1)]);
		}

		//controls
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if(activePiecesExistOnBoard(board, blankChar, activeChar, inactiveChar))
			{
				moveActivePiecesInDirection(board, directionUp, blankChar, activeChar, inactiveChar);
			}
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if(activePiecesExistOnBoard(board, blankChar, activeChar, inactiveChar))
			{
				moveActivePiecesInDirection(board, directionLeft, blankChar, activeChar, inactiveChar);
			}
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if(activePiecesExistOnBoard(board, blankChar, activeChar, inactiveChar))
			{
				moveActivePiecesInDirection(board, directionDown, blankChar, activeChar, inactiveChar);
			}
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if(activePiecesExistOnBoard(board, blankChar, activeChar, inactiveChar))
			{
				moveActivePiecesInDirection(board, directionRight, blankChar, activeChar, inactiveChar);
			}
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if(activePiecesExistOnBoard(board, blankChar, activeChar, inactiveChar))
			{
				slamActivePiecesInDirection(board, directionDown, blankChar, activeChar, inactiveChar);
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			while(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{

			}
			if(activePiecesExistOnBoard(board, blankChar, activeChar, inactiveChar))
			{
				rotateActivePieces(board, blankChar, activeChar, inactiveChar, true);
			}
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			while(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{

			}
			if(activePiecesExistOnBoard(board, blankChar, activeChar, inactiveChar))
			{
				rotateActivePieces(board, blankChar, activeChar, inactiveChar, false);
			}
		}

		//draw stuff
		lastlastframe = std::chrono::high_resolution_clock::now();
		window.clear(sf::Color::Black);

		for(int y = 0; y < board.size(); y++)
		{
			for(int x = 0; x < board[y].size(); x++)
			{
				if(board[y][x] == activeChar)
				{
					theBlock.setTexture(diamondOreTexture);
					theBlock.setPosition(x * theBlock.getGlobalBounds().width, y * theBlock.getGlobalBounds().height);
					theBlock.move(theBlockStartX, theBlockStartY);
					window.draw(theBlock);
				} else if(board[y][x] == inactiveChar)
				{
					theBlock.setTexture(diamondBlockTexture);
					theBlock.setPosition(x * theBlock.getGlobalBounds().width, y * theBlock.getGlobalBounds().height);
					theBlock.move(theBlockStartX, theBlockStartY);
					window.draw(theBlock);
				} else if(board[y][x] == blankChar)
				{
					theBlock.setTexture(wool_colored_pinkTexture);
					theBlock.setPosition(x * theBlock.getGlobalBounds().width, y * theBlock.getGlobalBounds().height);
					theBlock.move(theBlockStartX, theBlockStartY);
					window.draw(theBlock);
				}
			}
		}

		window.display();
		lastframe = std::chrono::high_resolution_clock::now();
		deltaTime = lastframe - lastlastframe;
	}

	std::cout << "done!" << std::endl;
	return 0;
}
