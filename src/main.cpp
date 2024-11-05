#include <iostream>
#include <vector>
#include <chrono>

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

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

			if(board[y][x] == activeChar && board[y + 1][x] == inactiveChar)
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

int main()
{
	Block iBlock({ {0, 0}, {1, 0}, {2, 0}, {3, 0} });
	Block jBlock({ {0, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block lBlock({ {2, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block oBlock({ {0, 0}, {1, 0}, {0, 1}, {1, 1} });
	Block sBlock({ {1, 0}, {2, 0}, {0, 1}, {1, 1} });
	Block tBlock({ {1, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block zBlock({ {0, 0}, {1, 0}, {1, 1}, {2, 1} });

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

	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			std::cout << board[y][x];
		}
		std::cout << std::endl;
	}

	std::chrono::time_point<std::chrono::system_clock> lastlastframe = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::system_clock> lastframe = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> deltaTime = lastframe - lastlastframe;
	std::chrono::duration<double> tickDelta = deltaTime;
	double tickDeltaThreshold = 0.4;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "title goes here lol", sf::Style::Default);
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
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			window.close();
		}

		//controls
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			int x, y;
			std::cin >> x;
			std::cin >> y;
			board[y][x] = activeChar;
		}

		//bool tick = false;
		if(tickDelta.count() >= tickDeltaThreshold)
		{
			tickDelta = std::chrono::seconds::zero();
			//tick = true;
			updateBoard(board, blankChar, activeChar, inactiveChar);
			std::cout << "UPDATE" << std::endl;
			std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
			for(int y = 0; y < board.size(); y++)
			{
				for(int x = 0; x < board[y].size(); x++)
				{
					std::cout << board[y][x];
				}
				std::cout << std::endl;
			}
		}
		tickDelta += deltaTime;

		lastlastframe = std::chrono::high_resolution_clock::now();
		window.clear(sf::Color::Black);
		//window.draw();
		window.display();
		lastframe = std::chrono::high_resolution_clock::now();
		deltaTime = lastframe - lastlastframe;

	}

	std::cout << "done!" << std::endl;
	return 0;
}
