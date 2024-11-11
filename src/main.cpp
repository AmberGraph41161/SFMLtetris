#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <cstdlib>

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

struct FloatingPoint
{
	FloatingPoint(float x, float y) : x(x), y(y)
	{
	}

	float x = 0;
	float y = 0;
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
	Block()
	{
	}

	std::vector<Point> points;
};

struct FloatingBlock
{
	FloatingBlock(std::vector<FloatingPoint> points)
	{
		this->points.reserve(4);
		this->points = points;
	}
	FloatingBlock()
	{
	}

	std::vector<FloatingPoint> points;
};

enum direction { directionUp, directionDown, directionLeft, directionRight };
bool canMoveActivePiecesInDirection(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &blankChar, const char &activeChar, const char &inactiveChar)
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

	return canMoveActivePieces;
}

void moveActivePiecesInDirection(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &blankChar, const char &activeChar, const char &inactiveChar)
{
	//move or don't move pieces after checking yo
	if(canMoveActivePiecesInDirection(board, upDownLeftRight, blankChar, activeChar, inactiveChar))
	{
		switch(upDownLeftRight)
		{
			case directionUp:
			{
				for(int y = 1; y < board.size(); y++)
				{
					for(int x = 0; x < board[y].size(); x++)
					{
						if(board[y][x] == activeChar)
						{
							board[y - 1][x] = activeChar;
							board[y][x] = blankChar;
						}
					}
				}

				break;
			}
			case directionDown:
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

				break;
			}
			case directionLeft:
			{
				for(int y = 0; y < board.size(); y++)
				{
					for(int x = 1; x < board[y].size(); x++)
					{
						if(board[y][x] == activeChar)
						{
							board[y][x - 1] = activeChar;
							board[y][x] = blankChar;
						}
					}
				}

				break;
			}
			case directionRight:
			{
				for(int y = 0; y < board.size(); y++)
				{
					for(int x = board[y].size() - 2; x >= 0; x--)
					{
						if(board[y][x] == activeChar)
						{
							board[y][x + 1] = activeChar;
							board[y][x] = blankChar;
						}
					}
				}

				break;
			}

			default:
			{
				std::cout << "you've reached unreachable code" << std::endl;
				break;
			}
		}
	}
}

void rotateActivePieces(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar, const char &inactiveChar, bool rotateInClockWiseDirection = true)
{
	/*
	stupid math stuff
	(x, y) --> rotate CCW --> (-y, x)
	(x, y) --> rotate CW  --> (y, -x)

	measure distance between point you want to rotate about and the origin, call it newOrigin
	allPoints - newOrigin,
	rotate allPoints,
	allPoints + newOrigin
	*/

	//collect all points
	FloatingBlock transformationBlock;
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(board[y][x] == activeChar)
			{
				transformationBlock.points.push_back(FloatingPoint(x, y));
			}
		}
	}

	//get 'middile point of all points'
	float topMost = transformationBlock.points[0].y;
	float bottomMost = transformationBlock.points[0].y;
	float leftMost = transformationBlock.points[0].x;
	float rightMost = transformationBlock.points[0].x;

	for(int x = 0; x < transformationBlock.points.size(); x++)
	{
		if(transformationBlock.points[x].y > topMost)
		{
			topMost = transformationBlock.points[x].y;
		} else if(transformationBlock.points[x].y < bottomMost)
		{
			bottomMost = transformationBlock.points[x].y;
		}

		if(transformationBlock.points[x].x < leftMost)
		{
			leftMost = transformationBlock.points[x].x;
		} else if(transformationBlock.points[x].x > rightMost)
		{
			rightMost = transformationBlock.points[x].x;
		}
	}
	int tempBlockWidth = rightMost - leftMost;
	int tempBlockHeight = topMost - bottomMost;

	FloatingPoint rotateAboutThisCoordinate(leftMost + ((rightMost - leftMost) / 2), bottomMost + ((topMost - bottomMost) / 2));

	//translate all points by newOrigin crap
	for(int x = 0; x < transformationBlock.points.size(); x++)
	{
		transformationBlock.points[x].x -= rotateAboutThisCoordinate.x;
		transformationBlock.points[x].y -= rotateAboutThisCoordinate.y;
	}

	//rotate all points
	for(int x = 0; x < transformationBlock.points.size(); x++)
	{
		/*
		(x, y) --> rotate CCW --> (-y, x)
		(x, y) --> rotate CW  --> (y, -x)
		*/

		float tempNumberSwapPlaceholder;
		if(rotateInClockWiseDirection)
		{
			tempNumberSwapPlaceholder = transformationBlock.points[x].x;
			transformationBlock.points[x].x = transformationBlock.points[x].y * -1;
			transformationBlock.points[x].y = tempNumberSwapPlaceholder;
		} else
		{
			tempNumberSwapPlaceholder = transformationBlock.points[x].x;
			transformationBlock.points[x].x = transformationBlock.points[x].y;
			transformationBlock.points[x].y = tempNumberSwapPlaceholder * -1;
		}
	}

	//translate back all points by newOrigin crap
	for(int x = 0; x < transformationBlock.points.size(); x++)
	{
		transformationBlock.points[x].x += rotateAboutThisCoordinate.x;
		transformationBlock.points[x].y += rotateAboutThisCoordinate.y;
	}

	//fix weird rotation offset math
	Point rotationOffsetFix(0, 0);
	if(tempBlockWidth != tempBlockHeight)
	{
		if(tempBlockWidth > tempBlockHeight)
		{
			rotationOffsetFix = Point(1, 0);
		} else
		{
			rotationOffsetFix = Point(0, 1);
		}
	}

	Block shimmyOriginalBlock;
	for(int x = 0; x < transformationBlock.points.size(); x++)
	{
		shimmyOriginalBlock.points.push_back(Point(std::floor(transformationBlock.points[x].x + rotationOffsetFix.x), std::floor(transformationBlock.points[x].y + rotationOffsetFix.y)));
	}

	Block shimmyLeftBlock = shimmyOriginalBlock;
	Block shimmyRightBlock = shimmyOriginalBlock;

	bool shimmyLeftBlockPointsArePlaceable;
	bool shimmyRightBlockPointsArePlaceable;

	while(true)
	{
		shimmyLeftBlockPointsArePlaceable = true;
		shimmyRightBlockPointsArePlaceable = true;

		for(int x = 0; x < shimmyLeftBlock.points.size(); x++)
		{
			if(board[shimmyLeftBlock.points[x].y][shimmyLeftBlock.points[x].x] == inactiveChar || shimmyLeftBlock.points[x].x < 0 || shimmyLeftBlock.points[x].x >= board[0].size())
			{
				shimmyLeftBlockPointsArePlaceable = false;
				break;
			}
		}
		for(int x = 0; x < shimmyRightBlock.points.size(); x++)
		{
			if(board[shimmyRightBlock.points[x].y][shimmyRightBlock.points[x].x] == inactiveChar || shimmyRightBlock.points[x].x < 0 || shimmyRightBlock.points[x].x >= board[0].size())
			{
				shimmyRightBlockPointsArePlaceable = false;
				break;
			}
		}

		if(shimmyLeftBlockPointsArePlaceable || shimmyRightBlockPointsArePlaceable)
		{
			break;
		}

		for(int x = 0; x < shimmyLeftBlock.points.size(); x++)
		{
			shimmyLeftBlock.points[x].x += -1;
		}
		for(int x = 0; x < shimmyRightBlock.points.size(); x++)
		{
			shimmyRightBlock.points[x].x += 1;
		}
	}

	//clear all active points and draw new ones
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(board[y][x] == activeChar)
			{
				board[y][x] = blankChar;
			}
		}
	}

	std::cout << std::string(30, '-') << std::endl;
	if(shimmyLeftBlockPointsArePlaceable)
	{
		std::cout << "PLACING LEFT SHIMMY" << std::endl;
		for(int x = 0; x < shimmyLeftBlock.points.size(); x++)
		{
			board[shimmyLeftBlock.points[x].y][shimmyLeftBlock.points[x].x] = activeChar;
		}
	} else if(shimmyRightBlockPointsArePlaceable)
	{
		std::cout << "PLACING RIGHT SHIMMY" << std::endl;
		for(int x = 0; x < shimmyRightBlock.points.size(); x++)
		{
			board[shimmyRightBlock.points[x].y][shimmyRightBlock.points[x].x] = activeChar;
		}
	}
}

//void updateFullRows(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &blankChar, const char &activeChar, const char &inactiveChar)
void updateFullRows(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar, const char &inactiveChar)
{
	for(int y = board.size() - 1; y > 0; y--)
	{
		bool rowIsFull = true;
		for(int x = 0; x < board[y].size(); x++)
		{
			if(board[y][x] != inactiveChar)
			{
				rowIsFull = false;
			}
		}

		if(rowIsFull)
		{
			for(int anotherY = y; anotherY > 0; anotherY--)
			{
				for(int x = 0; x < board[anotherY].size(); x++)
				{
					if(board[anotherY - 1][x] == inactiveChar || board[anotherY - 1][x] == blankChar)
					{
						board[anotherY][x] = board[anotherY - 1][x];
					}
				}
			}
			for(int x = 0; x > board[0].size(); x++)
			{
				if(board[0][x] == inactiveChar)
				{
					board[0][x] = blankChar;
				}
			}

			y++;
		}
	}
}

bool updateBoard(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar, const char &inactiveChar)
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

		return false;
	}

	return true;
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
		if(debug && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){for(int x = 0; x < iBlockCoords.points.size(); x++){board[iBlockCoords.points[x].y][iBlockCoords.points[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){for(int x = 0; x < jBlockCoords.points.size(); x++){board[jBlockCoords.points[x].y][jBlockCoords.points[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){for(int x = 0; x < lBlockCoords.points.size(); x++){board[lBlockCoords.points[x].y][lBlockCoords.points[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){for(int x = 0; x < oBlockCoords.points.size(); x++){board[oBlockCoords.points[x].y][oBlockCoords.points[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){for(int x = 0; x < sBlockCoords.points.size(); x++){board[sBlockCoords.points[x].y][sBlockCoords.points[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){for(int x = 0; x < tBlockCoords.points.size(); x++){board[tBlockCoords.points[x].y][tBlockCoords.points[x].x] = activeChar;}}if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){for(int x = 0; x < zBlockCoords.points.size(); x++){board[zBlockCoords.points[x].y][zBlockCoords.points[x].x] = activeChar;}}
		}

		//bool tick = false;
		if(tickDelta.count() >= tickDeltaThreshold)
		{
			tickDelta = std::chrono::seconds::zero();
			//tick = true;
			//updateBoard(board, blankChar, activeChar, inactiveChar);
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

		//controls
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
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
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			/*
			//potentially dangerous while loop here Wednesday, November 06, 2024, 10:44:24
			while(canMoveActivePiecesInDirection(board, directionDown, blankChar, activeChar, inactiveChar))
			{
				moveActivePiecesInDirection(board, directionDown, blankChar, activeChar, inactiveChar);
			}

			*/

			for(int x = 0; x < board[0].size(); x++)
			{
				board[0][x] = activeChar;
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			while(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{

			}
			rotateActivePieces(board, blankChar, activeChar, inactiveChar, true);
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			while(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{

			}
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
