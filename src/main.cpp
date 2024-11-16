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

double RANDOMDOUBLE(double minimum, double maximum)
{
	return (((double)rand() / RAND_MAX) * (maximum - minimum)) + minimum;
}

int main()
{
	srand(time(0));

	bool debug = false;

	//init backend
	int totalRowsCleared = 0;
	int score = 0;

	enum blockType { iBlock, jBlock, lBlock, oBlock, sBlock, tBlock, zBlock, customBlock };

	//as of Monday, November 11, 2024, 00:19:43, Block is vector for now. Might change to static array later. Dynamic cuz I might play around with it in future
	const Block iBlockCoords({ {0, 0}, {1, 0}, {2, 0}, {3, 0} }); //1. cyan
	const Block jBlockCoords({ {0, 0}, {0, 1}, {1, 1}, {2, 1} }); //2. blue (dark)
	const Block lBlockCoords({ {2, 0}, {0, 1}, {1, 1}, {2, 1} }); //3. orange
	const Block oBlockCoords({ {0, 0}, {1, 0}, {0, 1}, {1, 1} }); //4. yellow
	const Block sBlockCoords({ {1, 0}, {2, 0}, {0, 1}, {1, 1} }); //5. green (lime)
	const Block tBlockCoords({ {1, 0}, {0, 1}, {1, 1}, {2, 1} }); //6. purple
	const Block zBlockCoords({ {0, 0}, {1, 0}, {1, 1}, {2, 1} }); //7. red
															//8. [custom block color goes here]
	const std::array<const Block, 7> groupedBlockCollection = { iBlockCoords, jBlockCoords, lBlockCoords, oBlockCoords, sBlockCoords, tBlockCoords, zBlockCoords };

	std::queue<Block> blockQueue;
	for(int x = 0; x <= 5; x++)
	{
		blockQueue.push(groupedBlockCollection[RANDOM(0, groupedBlockCollection.size() - 1)]);
	}
	Block savedBlock;
	Block currentBlockInPlay;

	bool wasAbleToPlaceNextBlockSuccessfully = false;
		/*
		SFML DEFAULT SET COLORS:
			1. Red
			2. Blue
			3. Cyan
			4. Black
			5. Green
			6. White
			7. Yellow
			8. Magenta
			9. Transparent

			all color channels (RGBA) are from [0 - 255]
		*/
	const std::array<sf::Color, 8> sfColorValues =
	{
		sf::Color::Cyan, //cyan
		sf::Color::Blue, //blue
		sf::Color(223, 113, 38, 255), //orange
		sf::Color::Yellow, //yellow
		sf::Color::Green, //green
		sf::Color::Magenta, //purple
		sf::Color::Red, //red
		sf::Color(3, 2, 123, 255), //custom
	};
	const std::pair<int, int> blankIntLowerUpperPair = std::make_pair<int, int>(0, 8); //all these pair values MUST be in sync and in order!!! Friday, November 15, 2024, 13:09:58
	const std::pair<int, int> activeIntLowerUpperPair = std::make_pair<int, int>(10, 18);
	const std::pair<int, int> inactiveIntLowerUpperPair = std::make_pair<int, int>(20, 28);
	const std::pair<int, int> shadowIntLowerUpperPair = std::make_pair<int, int>(30, 38);

	int boardWidth = 10;
	int boardHeight = 20;
	std::vector<std::vector<int>> board; //as of Wednesday, November 06, 2024, 10:25:44, I am reconsidering my choices as to have board[y][x]... maybe I will regret this later
	for(int y = 0; y < boardHeight; y++)
	{
		std::vector<int> pushBackRowVector(boardWidth);
		for(int x = 0; x < boardWidth; x++)
		{
			pushBackRowVector[x] = blankIntLowerUpperPair.first;
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
						(10, 20) bottom right of the board
	
		when moving active pieces, start from bottom of the board to the top of the board when shimming pieces down.
	*/

	//SFML stuff
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	const int screenWidth16PixelScaleToFitMultiplier = 3;
	const int screenHeight16PixelScaleToFitMultiplier = 3;

	sf::Sprite theBlock;
	std::string blankIntTexturePath = "textures/blocks/wool_colored_pink.png";
	std::string activeIntTexturePath = "textures/blocks/diamond_ore.png";
	std::string inactiveIntTexturePath = "textures/blocks/diamond_block.png";
	std::string shadowIntTexturePath = "textures/blocks/glass.png";

	sf::Texture blankIntTexture;
	if(!blankIntTexture.loadFromFile(blankIntTexturePath))
	{
		std::cerr << "[failed to load [blankIntTexturePath] \"" << blankIntTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Texture activeIntTexture;
	if(!activeIntTexture.loadFromFile(activeIntTexturePath))
	{
		std::cerr << "[failed to load [activeIntTexturePath] \"" << activeIntTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Texture inactiveIntTexture;
	if(!inactiveIntTexture.loadFromFile(inactiveIntTexturePath))
	{
		std::cerr << "[failed to load [inactiveIntTexturePath] \"" << inactiveIntTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Texture shadowIntTexture;
	if(!shadowIntTexture.loadFromFile(shadowIntTexturePath))
	{
		std::cerr << "[failed to load [shadowIntTexturePath] \"" << shadowIntTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	theBlock.setTexture(activeIntTexture); //assumed that blank, active, inactive, and shadow textures are all the same dimensions btw
	theBlock.setScale(sf::Vector2f(screenWidth16PixelScaleToFitMultiplier, screenHeight16PixelScaleToFitMultiplier));

	//int theBlockStartX = ((float)screenWidth / 2) - ((theBlock.getGlobalBounds().width * boardWidth) / 2);
	//int theBlockStartY = ((float)screenHeight / 2) - ((theBlock.getGlobalBounds().height * boardHeight) / 2);
	int theBlockStartX = 16 * screenWidth16PixelScaleToFitMultiplier;
	int theBlockStartY = (16 + 8) * screenHeight16PixelScaleToFitMultiplier;
	int theBlockQueuedStartX = ((16 * 2) + (boardWidth * 16)) * screenWidth16PixelScaleToFitMultiplier;
	int theBlockQueuedStartY = ((16 + 8) + (16 * 2)) * screenHeight16PixelScaleToFitMultiplier;
	int theBlockSavedStartX = ((16 * 2) + (boardWidth * 16)) * screenWidth16PixelScaleToFitMultiplier;
	int theBlockSavedStartY = ((16 + 8) + (16 * 7)) * screenHeight16PixelScaleToFitMultiplier;

	sf::Sprite background;
	sf::Texture backgroundTexture;
	std::string backgroundTexturePath = "textures/default/background.png";
	if(!backgroundTexture.loadFromFile(backgroundTexturePath))
	{
		std::cerr << "[failed to load [backgroundTexturePath] \"" << backgroundTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	background.setTexture(backgroundTexture);
	background.setScale(sf::Vector2f(screenWidth16PixelScaleToFitMultiplier, screenHeight16PixelScaleToFitMultiplier));
	
	bool slamKeyPressedLastFrame = false;
	bool rotateKeyPressedLastFrame = false;
	bool saveblockKeyPressedLastFrame = false;
	bool saveblockUsedForCurrentBlock = false;

	std::chrono::time_point<std::chrono::system_clock> lastlastframe = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::system_clock> lastframe = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> deltaTime = lastframe - lastlastframe;

	std::chrono::duration<double> fallingBlocksTickDelta = deltaTime;
	double fallingBlocksTickDeltaThreshold = 0.4;

	std::chrono::duration<double> hardenActivePiecesTickDelta = deltaTime;
	double hardenActivePiecesTickDeltaThreshold = 1.3;
	
	std::chrono::duration<double> hardenActivePiecesAbsoluteTickDelta = deltaTime;
	double hardenActivePiecesAbsoluteTickDeltaThreshold = hardenActivePiecesTickDeltaThreshold * 2;

	std::chrono::duration<double> leftRightMovementTickDelta = deltaTime;
	double leftRightMovementTickDeltaThreshold = 0.1;

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

		if(debug)
		{
			printBoardInt(board, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, shadowIntLowerUpperPair);
		}

		//falling blocks tick delta
		if(fallingBlocksTickDelta.count() >= fallingBlocksTickDeltaThreshold)
		{
			fallingBlocksTickDelta = std::chrono::seconds::zero();
			moveActivePiecesInDirection(board, directionDown, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
		}
		fallingBlocksTickDelta += deltaTime;

		//hardening blocks tick delta
		if(!canMoveActivePiecesInDirection(board, directionDown, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
		{
			if(hardenActivePiecesTickDelta.count() >= hardenActivePiecesTickDeltaThreshold)
			{
				hardenActivePieces(board, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
				hardenActivePiecesTickDelta = std::chrono::seconds::zero();
				hardenActivePiecesAbsoluteTickDelta = std::chrono::seconds::zero();
			} else if(hardenActivePiecesAbsoluteTickDelta.count() >= hardenActivePiecesAbsoluteTickDeltaThreshold)
			{
				hardenActivePieces(board, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
				hardenActivePiecesTickDelta = std::chrono::seconds::zero();
				hardenActivePiecesAbsoluteTickDelta = std::chrono::seconds::zero();
			}
			hardenActivePiecesTickDelta += deltaTime;
			hardenActivePiecesAbsoluteTickDelta += deltaTime;
		}

		//block queue update and stuff
		if(!activePiecesExistOnBoard(board, activeIntLowerUpperPair))
		{
			std::vector<int> rowsCleared = clearAndGetFullRows(board, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
			totalRowsCleared += rowsCleared.size();
			score += calculateScoreFromRowsCleared(rowsCleared.size());

			std::cout << "SCORE: " << score << std::endl;
			std::cout << "totalRowsCleared: " << totalRowsCleared << std::endl;

			wasAbleToPlaceNextBlockSuccessfully = placeBlockAsActivePieces(board, blockQueue.front(), groupedBlockCollection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
			currentBlockInPlay = blockQueue.front();
			blockQueue.pop();
			blockQueue.push(groupedBlockCollection[RANDOM(0, groupedBlockCollection.size() - 1)]);

			if(!wasAbleToPlaceNextBlockSuccessfully)
			{
				break; //for now. Wednesday, November 13, 2024, 14:02:51
			}

			saveblockUsedForCurrentBlock = false;
		}

		//controls
		if(activePiecesExistOnBoard(board, activeIntLowerUpperPair))
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if(leftRightMovementTickDelta.count() == 0)
				{
					moveActivePiecesInDirection(board, directionLeft, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
					leftRightMovementTickDelta += deltaTime;
				} else if(leftRightMovementTickDelta.count() >= leftRightMovementTickDeltaThreshold)
				{
					moveActivePiecesInDirection(board, directionLeft, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
				} else
				{
					leftRightMovementTickDelta += deltaTime;
				}
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if(leftRightMovementTickDelta.count() == 0)
				{
					moveActivePiecesInDirection(board, directionRight, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
					leftRightMovementTickDelta += deltaTime;
				} else if(leftRightMovementTickDelta.count() >= leftRightMovementTickDeltaThreshold)
				{
					moveActivePiecesInDirection(board, directionRight, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
				} else
				{
					leftRightMovementTickDelta += deltaTime;
				}
			} else
			{
				leftRightMovementTickDelta = std::chrono::seconds::zero();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				/*
				if(!canMoveActivePiecesInDirection(board, directionDown, blankInt, activeInt, inactiveInt))
				{
					hardenActivePieces(board, activeInt, inactiveInt);
					hardenActivePiecesTickDelta = std::chrono::seconds::zero();
					hardenActivePiecesAbsoluteTickDelta = std::chrono::seconds::zero();
				}
				*/
				moveActivePiecesInDirection(board, directionDown, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if(!rotateKeyPressedLastFrame)
				{
					rotateActivePieces(board, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, true);
					rotateKeyPressedLastFrame = true;
					hardenActivePiecesTickDelta = std::chrono::seconds::zero();
				}
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				if(!rotateKeyPressedLastFrame)
				{
					rotateActivePieces(board, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, false);
					rotateKeyPressedLastFrame = true;
					hardenActivePiecesTickDelta = std::chrono::seconds::zero();
				}
			} else
			{
				rotateKeyPressedLastFrame = false;
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				if(!saveblockUsedForCurrentBlock && !saveblockKeyPressedLastFrame)
				{
					destroyActivePiecesOnBoard(board, blankIntLowerUpperPair, activeIntLowerUpperPair);
					if(savedBlock.empty())
					{
						savedBlock = currentBlockInPlay;

						placeBlockAsActivePieces(board, blockQueue.front(), groupedBlockCollection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
						currentBlockInPlay = blockQueue.front();
						blockQueue.pop();
						blockQueue.push(groupedBlockCollection[RANDOM(0, groupedBlockCollection.size() - 1)]);
					} else
					{
						placeBlockAsActivePieces(board, savedBlock, groupedBlockCollection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
						savedBlock = currentBlockInPlay;
					}

					saveblockUsedForCurrentBlock = true;
				}
				saveblockKeyPressedLastFrame = true;
			} else
			{
				saveblockKeyPressedLastFrame = false;
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if(!slamKeyPressedLastFrame)
				{
					slamActivePiecesInDirection(board, directionDown, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
					slamKeyPressedLastFrame = true;
				}
			} else
			{
				slamKeyPressedLastFrame = false;
			}
		}

		//fake-overlay shadowInts before drawing
		if(activePiecesExistOnBoard(board, activeIntLowerUpperPair))
		{
			fakeOverlayShadowInts(board, directionDown, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, shadowIntLowerUpperPair, true);
		}
		
		//draw stuff
		lastlastframe = std::chrono::high_resolution_clock::now();
		window.clear(sf::Color::Black);

		window.draw(background);

		for(int y = 0; y < board.size(); y++)
		{
			for(int x = 0; x < board[y].size(); x++)
			{
				if(withinIntPairRange(board[y][x], blankIntLowerUpperPair))
				{
					theBlock.setTexture(blankIntTexture);
					//theBlock.setColor(sfColorValues[board[y][x] - blankIntLowerUpperPair.first]);
					theBlock.setColor(sf::Color::White);
				} else if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
				{
					theBlock.setTexture(activeIntTexture);
					theBlock.setColor(sfColorValues[board[y][x] - activeIntLowerUpperPair.first]);
				} else if(withinIntPairRange(board[y][x], inactiveIntLowerUpperPair))
				{
					theBlock.setTexture(inactiveIntTexture);
					theBlock.setColor(sfColorValues[board[y][x] - inactiveIntLowerUpperPair.first]);
				} else if(withinIntPairRange(board[y][x], shadowIntLowerUpperPair))
				{
					theBlock.setTexture(shadowIntTexture);
					theBlock.setColor(sfColorValues[board[y][x] - shadowIntLowerUpperPair.first]);
				}
				theBlock.setPosition(x * theBlock.getGlobalBounds().width, y * theBlock.getGlobalBounds().height);
				theBlock.move(theBlockStartX, theBlockStartY);
				window.draw(theBlock);
			}
		}

		for(int x = 0; x < blockQueue.front().size(); x++)
		{
			theBlock.setTexture(activeIntTexture);
			theBlock.setPosition((blockQueue.front()[x].x * theBlock.getGlobalBounds().width) + theBlockQueuedStartX, (blockQueue.front()[x].y * theBlock.getGlobalBounds().height) + theBlockQueuedStartY);
			theBlock.setColor(sfColorValues[getIntColorFromBlockAndGroupedBLockCollection(blockQueue.front(), groupedBlockCollection)]);
			window.draw(theBlock);
		}
		for(int x = 0; x < savedBlock.size(); x++)
		{
			theBlock.setTexture(activeIntTexture);
			theBlock.setPosition((savedBlock[x].x * theBlock.getGlobalBounds().width) + theBlockSavedStartX, (savedBlock[x].y * theBlock.getGlobalBounds().height) + theBlockSavedStartY);
			theBlock.setColor(sfColorValues[getIntColorFromBlockAndGroupedBLockCollection(savedBlock, groupedBlockCollection)]);
			window.draw(theBlock);
		}
		theBlock.setColor(sf::Color::White);

		window.display();
		lastframe = std::chrono::high_resolution_clock::now();
		deltaTime = lastframe - lastlastframe;

		//remove fake-overlay of shadowInts
		if(activePiecesExistOnBoard(board, activeIntLowerUpperPair))
		{
			fakeOverlayShadowInts(board, directionDown, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, shadowIntLowerUpperPair, false);
		}
	}

	std::cout << "done!" << std::endl;
	return 0;
}
