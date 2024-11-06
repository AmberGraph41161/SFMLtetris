#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

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

struct Point
{
	Point(int x, int y) : x(x), y(y)
	{
	}

	int x = 0;
	int y = 0;
};

struct Block
{
//as of Tuesday, November 05, 2024, 09:44:34
	//thought that it might be nice to have a dynamic and not static n-points so that I can do some "cool custom stuff later"
	Block(std::vector<Point> points)
	{
		this->points.reserve(4);
		this->points = points;
	}

	std::vector<Point> points;
};

enum direction { directionUp, directionDown, directionLeft, directionRight };
void moveActivePiecesInDirection(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &blankChar, const char &activeChar, const char &inactiveChar)
{
	bool canMoveActivePieces = true;
	switch(upDownLeftRight)
	{
		case directionUp:
		{
			for(int x = 0; x < board[0].size(); x++)
			{
				if(board[0][x] == activeChar)
				{
					canMoveActivePieces = false;
					break;
				}
			}
			for(int y = 1; y < board.size(); y++)
			{
				if(!canMoveActivePieces)
				{
					break;
				}

				for(int x = 0; x < board[y].size(); x++)
				{
					if(!canMoveActivePieces)
					{
						break;
					}

					if(board[y][x] == activeChar && (board[y - 1][x] != blankChar && board[y - 1][x] != activeChar))
					{
						canMoveActivePieces = false;
					}
				}
			}

			break;
		}

		case directionDown:
		{
			for(int x = 0; x < board[board.size() - 1].size(); x++)
			{
				if(board[board.size() - 1][x] == activeChar)
				{
					canMoveActivePieces = false;
					break;
				}
			}

			for(int y = board.size() - 2; y >= 0; y--)
			{
				if(!canMoveActivePieces)
				{
					break;
				}

				for(int x = 0; x < board[y].size(); x++)
				{
					if(!canMoveActivePieces)
					{
						break;
					}

					if(board[y][x] == activeChar && (board[y + 1][x] != blankChar && board[y + 1][x] != activeChar))
					{
						canMoveActivePieces = false;
					}
				}
			}

			break;
		}

		case directionLeft:
		{
			for(int y = 0; y < board.size(); y++)
			{
				if(board[y][0] == activeChar)
				{
					canMoveActivePieces = false;
					break;
				}
			}

			for(int y = 0; y < board.size(); y++)
			{
				if(!canMoveActivePieces)
				{
					break;
				}

				for(int x = 1; x < board[y].size(); x++)
				{
					if(!canMoveActivePieces)
					{
						break;
					}

					if(board[y][x] == activeChar && (board[y][x - 1] != blankChar && board[y][x - 1] != activeChar))
					{
						canMoveActivePieces = false;
					}
				}
			}

			break;
		}

		case directionRight:
		{
			for(int y = 0; y < board.size(); y++)
			{
				if(board[y][board[y].size() - 1] == activeChar)
				{
					canMoveActivePieces = false;
					break;
				}
			}

			for(int y = 0; y < board.size(); y++)
			{
				if(!canMoveActivePieces)
				{
					break;
				}

				for(int x = board[y].size() - 2; x >= 0; x--)
				{
					if(!canMoveActivePieces)
					{
						break;
					}

					if(board[y][x] == activeChar && (board[y][x + 1] != blankChar && board[y][x + 1] != activeChar))
					{
						canMoveActivePieces = false;
					}
				}
			}

			break;
		}

		default:
		{
			canMoveActivePieces = false;
			std::cout << "invalid direction to move???" << std::endl;
			std::cout << "you've reached unreachable code" << std::endl;
			break;
		}
	}

	//move or don't move pieces after checking yo
	if(canMoveActivePieces)
	{
		std::cout << "can move in direction ";
		switch(upDownLeftRight)
		{
			case directionUp:
				std::cout << "up" << std::endl;
				break;
			case directionDown:
				std::cout << "down" << std::endl;
				break;
			case directionLeft:
				std::cout << "left" << std::endl;
				break;
			case directionRight:
				std::cout << "right" << std::endl;
				break;
			default:
				std::cout << "default" << std::endl;
				break;
		}
	}
}

void updateBoard(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar, const char &inactiveChar)
{
	bool canMoveActivePieces = true;

	for(int x = 0; x < board[board.size() - 1].size(); x++)
	{
		if(board[board.size() - 1][x] == activeChar)
		{
			canMoveActivePieces = false;
			break;
		}
	}
	for(int y = board.size() - 2; y >= 0; y--)
	{
		if(!canMoveActivePieces)
		{
			break;
		}

		for(int x = 0; x < board[y].size(); x++)
		{
			if(!canMoveActivePieces)
			{
				break;
			}

			if(board[y][x] == activeChar && (board[y + 1][x] != blankChar && board[y + 1][x] != activeChar))
			{
				canMoveActivePieces = false;
			}
		}
	}

	if(canMoveActivePieces)
	{
		for(int y = board.size() - 2; y >= 0; y--)
		{
			for(int x = 0; x < board[y].size(); x++)
			{
				if(board[y][x] == activeChar)
				{
					board[y + 1][x] = activeChar;
					board[y][x] = blankChar;
				}
			}
		}
	} else
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

void printBoard(std::vector<std::vector<char>> &board)
{
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			std::cout << board[y][x];
		}
		std::cout << std::endl;
	}
}

int main()
{
	bool debug = true;

	enum blockType { iBlock, jBlock, lBlock, oBlock, sBlock, tBlock, zBlock };

	Block iBlockCoords({ {0, 0}, {1, 0}, {2, 0}, {3, 0} });
	Block jBlockCoords({ {0, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block lBlockCoords({ {2, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block oBlockCoords({ {0, 0}, {1, 0}, {0, 1}, {1, 1} });
	Block sBlockCoords({ {1, 0}, {2, 0}, {0, 1}, {1, 1} });
	Block tBlockCoords({ {1, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block zBlockCoords({ {0, 0}, {1, 0}, {1, 1}, {2, 1} });

	const char blankChar = 'b';
	const char activeChar = 'a';
	const char inactiveChar = 'i';
	int boardWidth = 10;
	int boardHeight = 30;
	std::vector<std::vector<char>> board;
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
	theBlock.setTexture(diamondOreTexture);
	theBlock.setScale(sf::Vector2f(2, 2));

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

		//controls
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			board[0][0] = activeChar;
			board[1][0] = activeChar;
			board[1][1] = activeChar;
			board[1][2] = activeChar;
			board[1][3] = activeChar;

			/*
			int x, y;
			std::cin >> x;
			std::cin >> y;
			board[y][x] = activeChar;
			*/
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			moveActivePiecesInDirection(board, directionUp, blankChar, activeChar, inactiveChar);
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			moveActivePiecesInDirection(board, directionLeft, blankChar, activeChar, inactiveChar);
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			moveActivePiecesInDirection(board, directionDown, blankChar, activeChar, inactiveChar);
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			moveActivePiecesInDirection(board, directionRight, blankChar, activeChar, inactiveChar);
		}

		//bool tick = false;
		if(tickDelta.count() >= tickDeltaThreshold)
		{
			tickDelta = std::chrono::seconds::zero();
			//tick = true;
			updateBoard(board, blankChar, activeChar, inactiveChar);

			if(debug)
			{
				std::cout << std::string(boardWidth, '-') << std::endl;
				printBoard(board);
			}
		}
		tickDelta += deltaTime;

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
					window.draw(theBlock);
				} else if(board[y][x] == inactiveChar)
				{
					theBlock.setTexture(diamondBlockTexture);
					theBlock.setPosition(x * theBlock.getGlobalBounds().width, y * theBlock.getGlobalBounds().height);
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
