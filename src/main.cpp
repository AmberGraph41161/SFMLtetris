#include <SFML/Graphics/CircleShape.hpp>
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

	//init backend
	enum blockType { iBlock, jBlock, lBlock, oBlock, sBlock, tBlock, zBlock };

	//as of Monday, November 11, 2024, 00:19:43, Block is vector for now. Might change to static array later. Dynamic cuz I might play around with it in future
	Block iBlockCoords({ {0, 0}, {1, 0}, {2, 0}, {3, 0} });
	Block jBlockCoords({ {0, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block lBlockCoords({ {2, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block oBlockCoords({ {0, 0}, {1, 0}, {0, 1}, {1, 1} });
	Block sBlockCoords({ {1, 0}, {2, 0}, {0, 1}, {1, 1} });
	Block tBlockCoords({ {1, 0}, {0, 1}, {1, 1}, {2, 1} });
	Block zBlockCoords({ {0, 0}, {1, 0}, {1, 1}, {2, 1} });
	std::array<Block, 7> groupedBlockCollection = { iBlockCoords, jBlockCoords, lBlockCoords, oBlockCoords, sBlockCoords, tBlockCoords, zBlockCoords };

	std::queue<Block> blockQueue;
	for(int x = 0; x <= 5; x++)
	{
		blockQueue.push(groupedBlockCollection[RANDOM(0, groupedBlockCollection.size() - 1)]);
	}
	Block savedBlock;
	Block currentBlockInPlay;

	bool wasAbleToPlaceNextBlockSuccessfully = false;
	const char blankChar = 'b';
	const char activeChar = 'a';
	const char inactiveChar = 'i';
	const char shadowChar = 's';
	int boardWidth = 10;
	int boardHeight = 20;
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

	//SFML stuff
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	const int screenWidth16PixelScaleToFitMultiplier = 3;
	const int screenHeight16PixelScaleToFitMultiplier = 3;

	sf::Sprite theBlock;
	std::string blankCharTexturePath = "textures/blocks/wool_colored_pink.png";
	std::string activeCharTexturePath = "textures/blocks/diamond_ore.png";
	std::string inactiveCharTexturePath = "textures/blocks/diamond_block.png";
	std::string shadowCharTexturePath = "textures/blocks/glass.png";

	sf::Texture blankCharTexture;
	if(!blankCharTexture.loadFromFile(blankCharTexturePath))
	{
		std::cerr << "[failed to load [blankCharTexturePath] \"" << blankCharTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Texture activeCharTexture;
	if(!activeCharTexture.loadFromFile(activeCharTexturePath))
	{
		std::cerr << "[failed to load [activeCharTexturePath] \"" << activeCharTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Texture inactiveCharTexture;
	if(!inactiveCharTexture.loadFromFile(inactiveCharTexturePath))
	{
		std::cerr << "[failed to load [inactiveCharTexturePath] \"" << inactiveCharTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Texture shadowCharTexture;
	if(!shadowCharTexture.loadFromFile(shadowCharTexturePath))
	{
		std::cerr << "[failed to load [shadowCharTexturePath] \"" << shadowCharTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	theBlock.setTexture(activeCharTexture); //assumed that blank, active, inactive, and shadow textures are all the same dimensions btw
	theBlock.setScale(sf::Vector2f(screenWidth16PixelScaleToFitMultiplier, screenHeight16PixelScaleToFitMultiplier));

	//int theBlockStartX = ((float)screenWidth / 2) - ((theBlock.getGlobalBounds().width * boardWidth) / 2);
	//int theBlockStartY = ((float)screenHeight / 2) - ((theBlock.getGlobalBounds().height * boardHeight) / 2);
	int theBlockStartX = 16 * screenWidth16PixelScaleToFitMultiplier;
	int theBlockStartY = (16 + 8) * screenHeight16PixelScaleToFitMultiplier;
	int theBlockQueuedStartX = ((16 * 2) + (boardWidth * 16)) * screenWidth16PixelScaleToFitMultiplier;
	int theBlockQueuedStartY = ((16 + 8) + (16 * 7)) * screenHeight16PixelScaleToFitMultiplier;
	int theBlockSavedStartX = ((16 * 2) + (boardWidth * 16)) * screenWidth16PixelScaleToFitMultiplier;
	int theBlockSavedStartY = ((16 + 8) + (16 * 2)) * screenHeight16PixelScaleToFitMultiplier;

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

		//falling blocks tick delta
		if(fallingBlocksTickDelta.count() >= fallingBlocksTickDeltaThreshold)
		{
			fallingBlocksTickDelta = std::chrono::seconds::zero();
			//updateBoard(board, blankChar, activeChar, inactiveChar);
			moveActivePiecesInDirection(board, directionDown, blankChar, activeChar, inactiveChar);
		}
		fallingBlocksTickDelta += deltaTime;

		//hardening blocks tick delta
		if(!canMoveActivePiecesInDirection(board, directionDown, blankChar, activeChar, inactiveChar))
		{
			if(hardenActivePiecesTickDelta.count() >= hardenActivePiecesTickDeltaThreshold)
			{
				hardenActivePieces(board, activeChar, inactiveChar);
				hardenActivePiecesTickDelta = std::chrono::seconds::zero();
				hardenActivePiecesAbsoluteTickDelta = std::chrono::seconds::zero();
			} else if(hardenActivePiecesAbsoluteTickDelta.count() >= hardenActivePiecesAbsoluteTickDeltaThreshold)
			{
				hardenActivePieces(board, activeChar, inactiveChar);
				hardenActivePiecesTickDelta = std::chrono::seconds::zero();
				hardenActivePiecesAbsoluteTickDelta = std::chrono::seconds::zero();
			}
			hardenActivePiecesTickDelta += deltaTime;
			hardenActivePiecesAbsoluteTickDelta += deltaTime;
		}

		//block queue update and stuff
		if(!activePiecesExistOnBoard(board, activeChar))
		{
			clearFullRows(board, blankChar, activeChar, inactiveChar);

			wasAbleToPlaceNextBlockSuccessfully = placeBlockAsActivePieces(board, blockQueue.front(), blankChar, activeChar, inactiveChar);
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
		if(activePiecesExistOnBoard(board, activeChar))
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if(leftRightMovementTickDelta.count() == 0)
				{
					moveActivePiecesInDirection(board, directionLeft, blankChar, activeChar, inactiveChar);
					leftRightMovementTickDelta += deltaTime;
				} else if(leftRightMovementTickDelta.count() >= leftRightMovementTickDeltaThreshold)
				{
					moveActivePiecesInDirection(board, directionLeft, blankChar, activeChar, inactiveChar);
				} else
				{
					leftRightMovementTickDelta += deltaTime;
				}
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if(leftRightMovementTickDelta.count() == 0)
				{
					moveActivePiecesInDirection(board, directionRight, blankChar, activeChar, inactiveChar);
					leftRightMovementTickDelta += deltaTime;
				} else if(leftRightMovementTickDelta.count() >= leftRightMovementTickDeltaThreshold)
				{
					moveActivePiecesInDirection(board, directionRight, blankChar, activeChar, inactiveChar);
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
				if(!canMoveActivePiecesInDirection(board, directionDown, blankChar, activeChar, inactiveChar))
				{
					hardenActivePieces(board, activeChar, inactiveChar);
					hardenActivePiecesTickDelta = std::chrono::seconds::zero();
					hardenActivePiecesAbsoluteTickDelta = std::chrono::seconds::zero();
				}
				*/
				moveActivePiecesInDirection(board, directionDown, blankChar, activeChar, inactiveChar);
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if(!rotateKeyPressedLastFrame)
				{
					rotateActivePieces(board, blankChar, activeChar, inactiveChar, true);
					rotateKeyPressedLastFrame = true;
					hardenActivePiecesTickDelta = std::chrono::seconds::zero();
				}
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				if(!rotateKeyPressedLastFrame)
				{
					rotateActivePieces(board, blankChar, activeChar, inactiveChar, false);
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
					destroyActivePiecesOnBoard(board, blankChar, activeChar);
					if(savedBlock.empty())
					{
						savedBlock = currentBlockInPlay;

						placeBlockAsActivePieces(board, blockQueue.front(), blankChar, activeChar, inactiveChar);
						currentBlockInPlay = blockQueue.front();
						blockQueue.pop();
						blockQueue.push(groupedBlockCollection[RANDOM(0, groupedBlockCollection.size() - 1)]);
					} else
					{
						placeBlockAsActivePieces(board, savedBlock, blankChar, activeChar, inactiveChar);
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
					slamActivePiecesInDirection(board, directionDown, blankChar, activeChar, inactiveChar);
					slamKeyPressedLastFrame = true;
				}
			} else
			{
				slamKeyPressedLastFrame = false;
			}
		}

		//fake-overlay shadowChars before drawing
		if(activePiecesExistOnBoard(board, activeChar))
		{
			fakeOverlayShadowChars(board, directionDown, shadowChar, blankChar, activeChar, inactiveChar, true);
		}

		//draw stuff
		lastlastframe = std::chrono::high_resolution_clock::now();
		window.clear(sf::Color::Black);

		window.draw(background);

		for(int y = 0; y < board.size(); y++)
		{
			for(int x = 0; x < board[y].size(); x++)
			{
				if(board[y][x] == blankChar)
				{
					theBlock.setTexture(blankCharTexture);
				} else if(board[y][x] == activeChar)
				{
					theBlock.setTexture(activeCharTexture);
				} else if(board[y][x] == inactiveChar)
				{
					theBlock.setTexture(inactiveCharTexture);
				} else if(board[y][x] == shadowChar)
				{
					theBlock.setTexture(shadowCharTexture);
				}
				theBlock.setPosition(x * theBlock.getGlobalBounds().width, y * theBlock.getGlobalBounds().height);
				theBlock.move(theBlockStartX, theBlockStartY);
				window.draw(theBlock);
			}
		}

		for(int x = 0; x < blockQueue.front().size(); x++)
		{
			theBlock.setTexture(activeCharTexture);
			theBlock.setPosition((blockQueue.front()[x].x * theBlock.getGlobalBounds().width) + theBlockQueuedStartX, (blockQueue.front()[x].y * theBlock.getGlobalBounds().height) + theBlockQueuedStartY);
			window.draw(theBlock);
		}
		for(int x = 0; x < savedBlock.size(); x++)
		{
			theBlock.setTexture(activeCharTexture);
			theBlock.setPosition((savedBlock[x].x * theBlock.getGlobalBounds().width) + theBlockSavedStartX, (savedBlock[x].y * theBlock.getGlobalBounds().height) + theBlockSavedStartY);
			window.draw(theBlock);
		}

		window.display();
		lastframe = std::chrono::high_resolution_clock::now();
		deltaTime = lastframe - lastlastframe;

		//remove fake-overlay of shadowChars
		if(activePiecesExistOnBoard(board, activeChar))
		{
			fakeOverlayShadowChars(board, directionDown, shadowChar, blankChar, activeChar, inactiveChar, false);
		}
	}

	std::cout << "done!" << std::endl;
	return 0;
}
