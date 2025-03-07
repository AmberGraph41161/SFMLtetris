//started SFML 2.x to SFML 3.x migration code changes as of Thursday, March 06, 2025, 23:20:22
//I am doing this right after migrating SFMLflappybird to SFML 3.x
//ended migraing as of Thursday, March 06, 2025, 23:30:41

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <array>
#include <cmath>
#include <cstdlib>

#include <SFML/Audio.hpp>
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
	srand(std::chrono::system_clock::now().time_since_epoch().count());

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
	bool blankIntRetainColor = false;
	const std::array<sf::Color, 8> defaultColorValues =
	{
		/* CYAN   */ sf::Color::Cyan,
		/* BLUE   */ sf::Color::Blue,
		/* ORANGE */ sf::Color(223, 113, 38, 255),
		/* YELLOW */ sf::Color::Yellow,
		/* GREEN  */ sf::Color::Green,
		/* PURPLE */ sf::Color::Magenta,
		/* RED    */ sf::Color::Red,
		/* CUSTOM */ sf::Color(3, 2, 123, 255),
	};
	const std::array<sf::Color, 8> defaultPastelColorValues =
	{
		//"https://colorkit.co/palette/ffadad-ffd6a5-fdffb6-caffbf-9bf6ff-a0c4ff-bdb2ff-ffc6ff/"
		//"https://rgbacolorpicker.com/hex-to-rgba"

		/* CYAN   */ sf::Color(155, 246, 255, 255),
		/* BLUE   */ sf::Color(160, 196, 255, 255),
		/* ORANGE */ sf::Color(255, 214, 165, 255),
		/* YELLOW */ sf::Color(253, 255, 182, 255),
		/* GREEN  */ sf::Color(202, 255, 191, 255),
		/* PURPLE */ sf::Color(189, 178, 255, 255),
		/* RED    */ sf::Color(255, 173, 173, 255),
		/* CUSTOM */ sf::Color(3, 2, 123, 255),
	};
	const std::array<sf::Color, 8> defaultSuperPastelColorValues =
	{
		//"https://coolors.co/palette/fbf8cc-fde4cf-ffcfd2-f1c0e8-cfbaf0-a3c4f3-90dbf4-8eecf5-98f5e1-b9fbc0"
		//"https://rgbacolorpicker.com/hex-to-rgba"

		/* CYAN   */ sf::Color(142, 236, 245, 255),
		/* BLUE   */ sf::Color(163, 196, 243, 255),
		/* ORANGE */ sf::Color(253, 228, 207, 255),
		/* YELLOW */ sf::Color(251, 248, 204, 255),
		/* GREEN  */ sf::Color(185, 251, 192, 255),
		/* PURPLE */ sf::Color(207, 186, 240, 255),
		/* RED    */ sf::Color(255, 207, 210, 255),
		/* CUSTOM */ sf::Color(3, 2, 123, 255),
	};
	const std::array<sf::Color, 8> defaultHighContrastColorValues =
	{
		//"https://coolors.co/palette/ff0000-ff8700-ffd300-deff0a-a1ff0a-0aff99-0aefff-147df5-580aff-be0aff"
		//"https://rgbacolorpicker.com/hex-to-rgba"

		/* CYAN   */ sf::Color(10, 239, 255, 255),
		/* BLUE   */ sf::Color(88, 10, 255, 255),
		/* ORANGE */ sf::Color(255, 135, 0, 255),
		/* YELLOW */ sf::Color(255, 211, 0, 255),
		/* GREEN  */ sf::Color(161, 255, 10, 255),
		/* PURPLE */ sf::Color(190, 10, 255, 255),
		/* RED    */ sf::Color(255, 0, 0, 255),
		/* CUSTOM */ sf::Color(3, 2, 123, 255),
	};
	std::array<sf::Color, 8> currentColorValues = defaultColorValues;
	const std::pair<int, int> blankIntLowerUpperPair = std::make_pair<int, int>(0, 8); //all these pair values MUST be in sync and in order!!! Friday, November 15, 2024, 13:09:58
	const std::pair<int, int> activeIntLowerUpperPair = std::make_pair<int, int>(10, 18);
	const std::pair<int, int> inactiveIntLowerUpperPair = std::make_pair<int, int>(20, 28);
	const std::pair<int, int> shadowIntLowerUpperPair = std::make_pair<int, int>(30, 38);

	int boardHiddenGrace = 7;
	int boardWarningFade = 5;
	int boardWidth = 10;
	int boardHeight = 20 + boardHiddenGrace;
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

	direction gravityDirection = directionDown;
	direction canMoveDirection = gravityDirection;
	direction moveActiveDirection = gravityDirection;
	direction slamActiveDirection = gravityDirection;
	direction shadowDirection = gravityDirection;
	direction clearFullRowsDirection = gravityDirection;
	direction placeBlocksDirection = gravityDirection;

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
	std::vector<sf::Sound*> vectorOfPoitersToAllSounds;

	sf::SoundBuffer lineClearSFXbuffer;
	std::string lineClearSFXbufferPath = "resources/sounds/default/lineClear1.wav";
	if(!lineClearSFXbuffer.loadFromFile(lineClearSFXbufferPath))
	{
		std::cerr << "[failed to load [lineClearSFXbufferPath] \"" << lineClearSFXbufferPath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Sound lineClearSFX(lineClearSFXbuffer);
	vectorOfPoitersToAllSounds.push_back(&lineClearSFX);
	
	sf::SoundBuffer blockMoveSFXbuffer;
	std::string blockMoveSFXbufferPath = "resources/sounds/default/blockMove0.wav";
	if(!blockMoveSFXbuffer.loadFromFile(blockMoveSFXbufferPath))
	{
		std::cerr << "[failed to load [blockMoveSFXbufferPath] \"" << blockMoveSFXbufferPath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Sound blockMoveSFX(blockMoveSFXbuffer);
	vectorOfPoitersToAllSounds.push_back(&blockMoveSFX);
	
	sf::SoundBuffer blockRotateSFXbuffer;
	std::string blockRotateSFXbufferPath = "resources/sounds/default/blockRotate0.wav";
	if(!blockRotateSFXbuffer.loadFromFile(blockRotateSFXbufferPath))
	{
		std::cerr << "[failed to load [blockRotateSFXbufferPath] \"" << blockRotateSFXbufferPath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Sound blockRotateSFX(blockRotateSFXbuffer);
	vectorOfPoitersToAllSounds.push_back(&blockRotateSFX);
	
	sf::SoundBuffer blockSlamSFXbuffer;
	std::string blockSlamSFXbufferPath = "resources/sounds/default/blockSlam1.wav";
	if(!blockSlamSFXbuffer.loadFromFile(blockSlamSFXbufferPath))
	{
		std::cerr << "[failed to load [blockSlamSFXbufferPath] \"" << blockSlamSFXbufferPath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Sound blockSlamSFX(blockSlamSFXbuffer);
	vectorOfPoitersToAllSounds.push_back(&blockSlamSFX);

	for(int x = 0; x < vectorOfPoitersToAllSounds.size(); x++)
	{
		vectorOfPoitersToAllSounds[x]->setVolume(30);
	}

	const double screenWidth = 1920;
	const double screenHeight = 1080;
	const int screenWidth16PixelScaleToFitMultiplier = 3;
	const int screenHeight16PixelScaleToFitMultiplier = 3;

	//theBlock
	std::string blankIntTexturePath = "resources/textures/default/blank0.png"; //"resources/textures/blocks/wool_colored_pink.png";
	std::string activeIntTexturePath = "resources/textures/default/active0.png"; //"resources/textures/blocks/diamond_ore.png";
	std::string inactiveIntTexturePath = "resources/textures/default/inactive0.png"; //"resources/textures/blocks/diamond_block.png";
	std::string shadowIntTexturePath = "resources/textures/default/shadow0.png"; //"resources/textures/blocks/glass.png";
	std::string warningFadeTexturePath = "resources/textures/default/warningfade.png";
	std::string counterTexturePath = "resources/textures/default/counter-Sheet.png";

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
	sf::Texture warningFadeTexture;
	if(!warningFadeTexture.loadFromFile(warningFadeTexturePath))
	{
		std::cerr << "[failed to load [warningFadeTexturePath] \"" << warningFadeTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Texture counterTexture;
	if(!counterTexture.loadFromFile(counterTexturePath))
	{
		std::cerr << "[failed to load [counterTexturePath] \"" << counterTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Sprite theBlock(activeIntTexture); //assumed that blank, active, inactive, and shadow textures are all the same dimensions btw
	theBlock.setScale(sf::Vector2f(screenWidth16PixelScaleToFitMultiplier, screenHeight16PixelScaleToFitMultiplier));

	//int theBlockStartX = ((float)screenWidth / 2) - ((theBlock.getGlobalBounds().width * boardWidth) / 2);
	//int theBlockStartY = ((float)screenHeight / 2) - ((theBlock.getGlobalBounds().height * boardHeight) / 2);
	const int theBlockStartX = 16 * screenWidth16PixelScaleToFitMultiplier;
	const int theBlockStartY = ((16 + 8) - (16 * boardHiddenGrace))* screenHeight16PixelScaleToFitMultiplier;
	const int theBlockQueuedStartX = ((16 * 2) + (boardWidth * 16)) * screenWidth16PixelScaleToFitMultiplier;
	const int theBlockQueuedStartY = ((16 + 8) + (16 * 2)) * screenHeight16PixelScaleToFitMultiplier;
	const int theBlockSavedStartX = ((16 * 2) + (boardWidth * 16)) * screenWidth16PixelScaleToFitMultiplier;
	const int theBlockSavedStartY = ((16 + 8) + (16 * 7)) * screenHeight16PixelScaleToFitMultiplier;
	const int theBlockCounterStartX = (16 * 17) * screenWidth16PixelScaleToFitMultiplier;
	const int theBlockCounterStartY = ((16 + 8) + (16 * 1)) * screenHeight16PixelScaleToFitMultiplier;

	//background stuff
	sf::Texture backgroundTexture;
	std::string backgroundTexturePath = "resources/textures/default/background0.png";
	if(!backgroundTexture.loadFromFile(backgroundTexturePath))
	{
		std::cerr << "[failed to load [backgroundTexturePath] \"" << backgroundTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	sf::Sprite background(backgroundTexture);
	background.setScale(sf::Vector2f(screenWidth16PixelScaleToFitMultiplier, screenHeight16PixelScaleToFitMultiplier));

	//start button stuff
	sf::Texture startButtonTexture;
	std::string startButtonTexturePath = "resources/textures/default/startbutton-Sheet.png";
	if(!startButtonTexture.loadFromFile(startButtonTexturePath))
	{
		std::cerr << "[failed to load [startButtonTexturePath] \"" << startButtonTexturePath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}
	const int startButtonTextureWidth = 38;
	const int startButtonTextureHeight = 20;
	const int startButtonLastFrameCount = 383;
	int startButtonAnimatedCurrentFrame = 0;
	sf::Sprite startButton(startButtonTexture);
	startButton.setTextureRect(spriteSheetFrame(startButtonTextureWidth, startButtonTextureHeight, startButtonAnimatedCurrentFrame));
	startButton.setScale(sf::Vector2f(20, 20));
	startButton.setOrigin(sf::Vector2f(startButton.getLocalBounds().size.x / 2, startButton.getLocalBounds().size.y / 2));
	startButton.setPosition(sf::Vector2f((float)screenWidth / 2, (float)screenHeight / 2));
	startButton.move(sf::Vector2f(0.1, 0)); // wacky bug fix to fix startButton Pixels Jittering (SFML bug?)) //still broken as of Sunday, December 15, 2024, 18:25:13
	std::chrono::duration<double> startButtonAnimatedTickDelta = std::chrono::seconds::zero();
	const double startButtonAnimatedTickDeltaThreshold = 0.03;

	//"menu bools"
	bool playerIsAlive = false;
	bool pauseMenu = false;
	bool startMenu = true;
	bool resetBackToStartScreen = false;

	sf::Font masterFont;
	std::string masterFontPath = "resources/fonts/Minecraftia-Regular.ttf";
	if(!masterFont.openFromFile(masterFontPath))
	{
		std::cerr << "[failed to load [masterFontPath] \"" << masterFontPath << "\"]" << std::endl;
		exit(EXIT_FAILURE);
	}

	const int dimScreenShapeDefaultDim = 200;
	sf::RectangleShape dimScreenShape(sf::Vector2f(screenWidth * 2, screenHeight * 2)); //because of hiddenGraceAreaViewZoom stuff
	dimScreenShape.setFillColor(sf::Color(0, 0, 0, dimScreenShapeDefaultDim));
	dimScreenShape.setOrigin(sf::Vector2f(dimScreenShape.getLocalBounds().size.x / 2, dimScreenShape.getLocalBounds().size.y / 2));
	dimScreenShape.setPosition(sf::Vector2f(screenWidth / 2, screenHeight / 2));

	sf::Text dimScreenText(masterFont);
	dimScreenText.setCharacterSize(24);
	dimScreenText.setString("Click anywhere to resume...");
	dimScreenText.setOrigin(sf::Vector2f(dimScreenText.getLocalBounds().size.x / 2, dimScreenText.getLocalBounds().size.y / 2));
	dimScreenText.setPosition(sf::Vector2f(screenWidth / 2, screenHeight / 2));
	
	bool slamKeyPressedLastFrame = false;
	bool rotateKeyPressedLastFrame = false;
	bool saveblockKeyPressedLastFrame = false;
	bool saveblockUsedForCurrentBlock = false;

	std::chrono::time_point<std::chrono::system_clock> lastlastframe = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::system_clock> lastframe = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> deltaTime = lastframe - lastlastframe;

	std::chrono::duration<double> fallingBlocksTickDelta = deltaTime;
	double fallingBlocksTickDeltaThreshold = 0.9;
	const double fallingBlocksTickDeltaThresholdMinumum = 0.1;

	std::chrono::duration<double> hardenActivePiecesTickDelta = deltaTime;
	const double hardenActivePiecesTickDeltaThreshold = 1.3;
	const double hardenActivePiecesTickDeltaThresholdMinimum = 0.3;
	
	std::chrono::duration<double> hardenActivePiecesAbsoluteTickDelta = deltaTime;
	const double hardenActivePiecesAbsoluteTickDeltaThreshold = hardenActivePiecesTickDeltaThreshold * 2;

	std::chrono::duration<double> leftRightMovementTickDelta = deltaTime;
	const double leftRightMovementTickDeltaThreshold = 0.1;

	std::chrono::duration<double> hiddenGraceAreaViewZoomTickDelta = deltaTime;
	const double hiddenGraceAreaViewZoomTickDeltaThreshold = 5;

	sf::View view(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(screenWidth, screenHeight)));
	sf::RenderWindow window(sf::VideoMode(sf::Vector2u(screenWidth, screenHeight)), "title goes here lol", sf::Style::Default);
	window.setFramerateLimit(60);
	while(window.isOpen())
	{
		while(std::optional event = window.pollEvent())
		{
			if(event->is<sf::Event::Closed>())
			{
				window.close();
			}
			if(event->is<sf::Event::Resized>())
			{
				//copied and pasted from SFMLflappybird for resizing logic. as of Tuesday, November 05, 2024, 11:40:24
				if((((float)window.getSize().x / 16) * 9) > window.getSize().y)
				{
					view.setViewport(sf::FloatRect(
						sf::Vector2f(0.5 - (((((float)window.getSize().y / 9) * 16) / (float)window.getSize().x) / 2), 0),
						sf::Vector2f((((float)window.getSize().y / 9) * 16) / (float)window.getSize().x, 1)
					));
				} else
				{
					view.setViewport(sf::FloatRect(
						sf::Vector2f(0, 0.5 - (((((float)window.getSize().x / 16) * 9) / (float)window.getSize().y) / 2)),
						sf::Vector2f(1, (((float)window.getSize().x / 16) * 9) / (float)window.getSize().y))
					);
				}
				window.setView(view);
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q))
		{
			window.close();
		}

		if(debug)
		{
			printBoardInt(board, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, shadowIntLowerUpperPair);
		}

		if(startMenu)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if(startButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)))
				{
					playerIsAlive = true;
					startMenu = false;
				}
			}

			startButtonAnimatedTickDelta += deltaTime;
			if(startButtonAnimatedTickDelta.count() >= startButtonAnimatedTickDeltaThreshold)
			{
				startButtonAnimatedTickDelta = std::chrono::seconds::zero();
				startButtonAnimatedCurrentFrame++;
				if(startButtonAnimatedCurrentFrame >= startButtonLastFrameCount)
				{
					startButtonAnimatedCurrentFrame = 0;
				}
				startButton.setTextureRect(spriteSheetFrame(startButtonTextureWidth, startButtonTextureHeight, startButtonAnimatedCurrentFrame));
			}

			lastlastframe = std::chrono::high_resolution_clock::now();
			window.clear(sf::Color::White);
			window.draw(startButton);
			window.display();
			lastframe = std::chrono::high_resolution_clock::now();
			deltaTime = lastframe - lastlastframe;
		} else if(pauseMenu)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				pauseMenu = false;
			}

			//draw stuff
			lastlastframe = std::chrono::high_resolution_clock::now();
			window.clear(sf::Color::Black);

			window.draw(background);
			
			//fake-overlay shadowInts before drawing
			if(activePiecesExistOnBoard(board, activeIntLowerUpperPair))
			{
				fakeOverlayShadowInts(board, shadowDirection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, shadowIntLowerUpperPair, true);
			}
			for(int y = 0; y < board.size(); y++)
			{
				if(y < boardHiddenGrace && !intPiecesExistInHiddenGrace(board, boardHiddenGrace + 1, inactiveIntLowerUpperPair))
				{
					continue;
				}

				for(int x = 0; x < board[y].size(); x++)
				{
					if(withinIntPairRange(board[y][x], blankIntLowerUpperPair))
					{
						theBlock.setTexture(blankIntTexture);
						if(blankIntRetainColor)
						{
							theBlock.setColor(currentColorValues[board[y][x] - blankIntLowerUpperPair.first]);
						} else
						{
							theBlock.setColor(sf::Color::White);
						}
					} else if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
					{
						theBlock.setTexture(activeIntTexture);
						theBlock.setColor(currentColorValues[board[y][x] - activeIntLowerUpperPair.first]);
					} else if(withinIntPairRange(board[y][x], inactiveIntLowerUpperPair))
					{
						theBlock.setTexture(inactiveIntTexture);
						theBlock.setColor(currentColorValues[board[y][x] - inactiveIntLowerUpperPair.first]);
					} else if(withinIntPairRange(board[y][x], shadowIntLowerUpperPair))
					{
						theBlock.setTexture(shadowIntTexture);
						theBlock.setColor(currentColorValues[board[y][x] - shadowIntLowerUpperPair.first]);
					}
					theBlock.setPosition(sf::Vector2f(x * theBlock.getGlobalBounds().size.x, y * theBlock.getGlobalBounds().size.y));
					theBlock.move(sf::Vector2f(theBlockStartX, theBlockStartY));
					window.draw(theBlock);

					if(y <= boardWarningFade)
					{
						theBlock.setTexture(warningFadeTexture);
						theBlock.setColor(sf::Color(255, 0, 0, 230 / (y + 1)));

						theBlock.setPosition(sf::Vector2f(x * theBlock.getGlobalBounds().size.x, y * theBlock.getGlobalBounds().size.y));
						theBlock.move(sf::Vector2f(theBlockStartX, theBlockStartY));
						window.draw(theBlock);
					}
				}
			}

			for(int x = 0; x < blockQueue.front().size(); x++)
			{
				theBlock.setTexture(activeIntTexture);
				theBlock.setPosition(sf::Vector2f(
					(blockQueue.front()[x].x * theBlock.getGlobalBounds().size.x) + theBlockQueuedStartX,
					(blockQueue.front()[x].y * theBlock.getGlobalBounds().size.y) + theBlockQueuedStartY
				));
				theBlock.setColor(currentColorValues[getIntColorFromBlockAndGroupedBLockCollection(blockQueue.front(), groupedBlockCollection)]);
				window.draw(theBlock);
			}
			for(int x = 0; x < savedBlock.size(); x++)
			{
				theBlock.setTexture(activeIntTexture);
				theBlock.setPosition(sf::Vector2f(
					(savedBlock[x].x * theBlock.getGlobalBounds().size.x) + theBlockSavedStartX,
					(savedBlock[x].y * theBlock.getGlobalBounds().size.y) + theBlockSavedStartY
				));
				theBlock.setColor(currentColorValues[getIntColorFromBlockAndGroupedBLockCollection(savedBlock, groupedBlockCollection)]);
				window.draw(theBlock);
			}
			theBlock.setColor(sf::Color::White);

			//remove fake-overlay of shadowInts
			if(activePiecesExistOnBoard(board, activeIntLowerUpperPair))
			{
				fakeOverlayShadowInts(board, shadowDirection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, shadowIntLowerUpperPair, false);
			}

			//draw counter stuff
			std::string counterString = std::to_string(score);
			theBlock.setPosition(sf::Vector2f(theBlockCounterStartX, theBlockCounterStartY));
			theBlock.setTexture(counterTexture);
			theBlock.setTextureRect(spriteSheetFrame(16, 16, 0));
			for(int x = 0; x < counterString.size(); x++)
			{
				theBlock.setTextureRect(spriteSheetFrame(16, 16, counterString[x] - '0'));
				window.draw(theBlock);
				theBlock.move(sf::Vector2f(16 * screenWidth16PixelScaleToFitMultiplier, 0));
			}
			theBlock.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(16, 16)));

			window.draw(dimScreenShape);
			window.draw(dimScreenText);

			window.display();
			lastframe = std::chrono::high_resolution_clock::now();
			deltaTime = lastframe - lastlastframe;
			
		} else if(playerIsAlive)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
			{
				pauseMenu = true;
				continue;
			}

			//falling blocks tick delta
			if(fallingBlocksTickDelta.count() >= fallingBlocksTickDeltaThreshold)
			{
				fallingBlocksTickDelta = std::chrono::seconds::zero();
				moveActivePiecesInDirection(board, moveActiveDirection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
			}
			fallingBlocksTickDelta += deltaTime;

			//hardening blocks tick delta
			if(!canMoveActivePiecesInDirection(board, canMoveDirection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
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
			} else
			{
				hardenActivePiecesTickDelta = std::chrono::seconds::zero();
				hardenActivePiecesAbsoluteTickDelta = std::chrono::seconds::zero();
			}

			//block queue update and stuff
			if(!activePiecesExistOnBoard(board, activeIntLowerUpperPair))
			{
				std::vector<int> rowsCleared = clearAndGetFullRows(board, clearFullRowsDirection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
				if(!rowsCleared.empty())
				{
					lineClearSFX.play();
				}
				totalRowsCleared += rowsCleared.size();
				score += calculateScoreFromRowsCleared(rowsCleared.size());

					//temp debug stuff
					std::cout << "SCORE: " << score << std::endl;
					std::cout << "totalRowsCleared: " << totalRowsCleared << std::endl;

				if(fallingBlocksTickDeltaThreshold > fallingBlocksTickDeltaThresholdMinumum)
				{
					fallingBlocksTickDeltaThreshold -= 0.02;
				}
				/*
				if(hardenActivePiecesTickDeltaThreshold > hardenActivePiecesTickDeltaThresholdMinimum)
				{
					hardenActivePiecesTickDeltaThreshold -= 0.1;
				}
				*/

				wasAbleToPlaceNextBlockSuccessfully = placeBlockAsActivePieces(board, placeBlocksDirection, blockQueue.front(), boardHiddenGrace, groupedBlockCollection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
				currentBlockInPlay = blockQueue.front();
				blockQueue.pop();
				blockQueue.push(groupedBlockCollection[RANDOM(0, groupedBlockCollection.size() - 1)]);

				if(!wasAbleToPlaceNextBlockSuccessfully)
				{
					playerIsAlive = false;
					resetBackToStartScreen = true;
				}

				saveblockUsedForCurrentBlock = false;
			}

			//controls
			if(activePiecesExistOnBoard(board, activeIntLowerUpperPair))
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
				{
					if(leftRightMovementTickDelta.count() == 0)
					{
						if(moveActivePiecesInDirection(board, directionLeft, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
						{
							blockMoveSFX.play();
						}
						leftRightMovementTickDelta += deltaTime;
					} else if(leftRightMovementTickDelta.count() >= leftRightMovementTickDeltaThreshold)
					{
						if(moveActivePiecesInDirection(board, directionLeft, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
						{
							blockMoveSFX.play();
						}
					} else
					{
						leftRightMovementTickDelta += deltaTime;
					}
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
				{
					if(leftRightMovementTickDelta.count() == 0)
					{
						if(moveActivePiecesInDirection(board, directionRight, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
						{
							blockMoveSFX.play();
						}
						leftRightMovementTickDelta += deltaTime;
					} else if(leftRightMovementTickDelta.count() >= leftRightMovementTickDeltaThreshold)
					{
						if(moveActivePiecesInDirection(board, directionRight, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
						{
							blockMoveSFX.play();
						}
					} else
					{
						leftRightMovementTickDelta += deltaTime;
					}
				} else
				{
					leftRightMovementTickDelta = std::chrono::seconds::zero();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
				{
					/*
					if(!canMoveActivePiecesInDirection(board, directionDown, blankInt, activeInt, inactiveInt))
					{
						hardenActivePieces(board, activeInt, inactiveInt);
						hardenActivePiecesTickDelta = std::chrono::seconds::zero();
						hardenActivePiecesAbsoluteTickDelta = std::chrono::seconds::zero();
					}
					*/
					if(moveActivePiecesInDirection(board, directionDown, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
					{
						blockMoveSFX.play();
					}
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
				{
					if(!rotateKeyPressedLastFrame)
					{
						if(rotateActivePieces(board, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, true))
						{
							blockRotateSFX.play();
						}
						rotateKeyPressedLastFrame = true;
						hardenActivePiecesTickDelta = std::chrono::seconds::zero();
					}
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z))
				{
					if(!rotateKeyPressedLastFrame)
					{
						if(rotateActivePieces(board, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, false))
						{
							blockRotateSFX.play();
						}
						rotateKeyPressedLastFrame = true;
						hardenActivePiecesTickDelta = std::chrono::seconds::zero();
					}
				} else
				{
					rotateKeyPressedLastFrame = false;
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C))
				{
					if(!saveblockUsedForCurrentBlock && !saveblockKeyPressedLastFrame)
					{
						destroyActivePiecesOnBoard(board, blankIntLowerUpperPair, activeIntLowerUpperPair);
						if(savedBlock.empty())
						{
							savedBlock = currentBlockInPlay;

							placeBlockAsActivePieces(board, placeBlocksDirection, blockQueue.front(), boardHiddenGrace, groupedBlockCollection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
							currentBlockInPlay = blockQueue.front();
							blockQueue.pop();
							blockQueue.push(groupedBlockCollection[RANDOM(0, groupedBlockCollection.size() - 1)]);
						} else
						{
							placeBlockAsActivePieces(board, placeBlocksDirection, savedBlock, boardHiddenGrace, groupedBlockCollection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
							savedBlock = currentBlockInPlay;
						}

						saveblockUsedForCurrentBlock = true;
					}
					saveblockKeyPressedLastFrame = true;
				} else
				{
					saveblockKeyPressedLastFrame = false;
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
				{
					if(!slamKeyPressedLastFrame)
					{
						blockSlamSFX.play();
						slamActivePiecesInDirection(board, slamActiveDirection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
						slamKeyPressedLastFrame = true;
					}
				} else
				{
					slamKeyPressedLastFrame = false;
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num1))
				{
					currentColorValues = defaultColorValues;
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num2))
				{
					currentColorValues = defaultPastelColorValues;
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num3))
				{
					currentColorValues = defaultSuperPastelColorValues; 
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num4))
				{
					currentColorValues = defaultHighContrastColorValues;
				}
			}

			//draw stuff
			lastlastframe = std::chrono::high_resolution_clock::now();
			window.clear(sf::Color::Black);

			window.draw(background);

			//fake-overlay shadowInts before drawing board
			if(activePiecesExistOnBoard(board, activeIntLowerUpperPair))
			{
				fakeOverlayShadowInts(board, shadowDirection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, shadowIntLowerUpperPair, true);
			}
			for(int y = 0; y < board.size(); y++)
			{
				if(y < boardHiddenGrace && !intPiecesExistInHiddenGrace(board, boardHiddenGrace + 1, inactiveIntLowerUpperPair))
				{
					continue;
				}

				for(int x = 0; x < board[y].size(); x++)
				{
					if(withinIntPairRange(board[y][x], blankIntLowerUpperPair))
					{
						theBlock.setTexture(blankIntTexture);
						if(blankIntRetainColor)
						{
							theBlock.setColor(currentColorValues[board[y][x] - blankIntLowerUpperPair.first]);
						} else
						{
							theBlock.setColor(sf::Color::White);
						}
					} else if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
					{
						theBlock.setTexture(activeIntTexture);
						theBlock.setColor(currentColorValues[board[y][x] - activeIntLowerUpperPair.first]);
					} else if(withinIntPairRange(board[y][x], inactiveIntLowerUpperPair))
					{
						theBlock.setTexture(inactiveIntTexture);
						theBlock.setColor(currentColorValues[board[y][x] - inactiveIntLowerUpperPair.first]);
					} else if(withinIntPairRange(board[y][x], shadowIntLowerUpperPair))
					{
						theBlock.setTexture(shadowIntTexture);
						theBlock.setColor(currentColorValues[board[y][x] - shadowIntLowerUpperPair.first]);
					}
					theBlock.setPosition(sf::Vector2f(x * theBlock.getGlobalBounds().size.x, y * theBlock.getGlobalBounds().size.y));
					theBlock.move(sf::Vector2f(theBlockStartX, theBlockStartY));
					window.draw(theBlock);

					if(y <= boardWarningFade)
					{
						theBlock.setTexture(warningFadeTexture);
						theBlock.setColor(sf::Color(255, 0, 0, 230 / (y + 1)));

						theBlock.setPosition(sf::Vector2f(x * theBlock.getGlobalBounds().size.x, y * theBlock.getGlobalBounds().size.y));
						theBlock.move(sf::Vector2f(theBlockStartX, theBlockStartY));
						window.draw(theBlock);
					}
				}
			}

			for(int x = 0; x < blockQueue.front().size(); x++)
			{
				theBlock.setTexture(activeIntTexture);
				theBlock.setPosition(sf::Vector2f(
					(blockQueue.front()[x].x * theBlock.getGlobalBounds().size.x) + theBlockQueuedStartX,
					(blockQueue.front()[x].y * theBlock.getGlobalBounds().size.y) + theBlockQueuedStartY
				));
				theBlock.setColor(currentColorValues[getIntColorFromBlockAndGroupedBLockCollection(blockQueue.front(), groupedBlockCollection)]);
				window.draw(theBlock);
			}
			for(int x = 0; x < savedBlock.size(); x++)
			{
				theBlock.setTexture(activeIntTexture);
				theBlock.setPosition(sf::Vector2f(
					(savedBlock[x].x * theBlock.getGlobalBounds().size.x) + theBlockSavedStartX,
					(savedBlock[x].y * theBlock.getGlobalBounds().size.y) + theBlockSavedStartY
				));
				theBlock.setColor(currentColorValues[getIntColorFromBlockAndGroupedBLockCollection(savedBlock, groupedBlockCollection)]);
				window.draw(theBlock);
			}
			theBlock.setColor(sf::Color::White);

			if(intPiecesExistInHiddenGrace(board, boardHiddenGrace, inactiveIntLowerUpperPair))
			{
				hiddenGraceAreaViewZoomTickDelta += deltaTime;
				hiddenGraceAreaViewZoomTickDelta = std::chrono::duration<double>(hiddenGraceAreaViewZoomTickDelta.count() * 1.2);
				double zoomMultiplier = ((hiddenGraceAreaViewZoomTickDelta.count() / hiddenGraceAreaViewZoomTickDeltaThreshold) * 0.5) + 1;
				if(hiddenGraceAreaViewZoomTickDelta.count() >= hiddenGraceAreaViewZoomTickDeltaThreshold)
				{
					hiddenGraceAreaViewZoomTickDelta = std::chrono::duration<double>(hiddenGraceAreaViewZoomTickDeltaThreshold);
					zoomMultiplier = 1.5;
				}

				view.setSize(sf::Vector2f(screenWidth * zoomMultiplier, screenHeight * zoomMultiplier));
				window.setView(view);
			} else if(view.getSize().x > screenWidth)
			{
				hiddenGraceAreaViewZoomTickDelta -= deltaTime;
				hiddenGraceAreaViewZoomTickDelta = std::chrono::duration<double>(hiddenGraceAreaViewZoomTickDelta.count() * 0.9);
				double zoomMultiplier = ((hiddenGraceAreaViewZoomTickDelta.count() / hiddenGraceAreaViewZoomTickDeltaThreshold) * 0.5) + 1;
				if(hiddenGraceAreaViewZoomTickDelta.count() <= 0)
				{
					hiddenGraceAreaViewZoomTickDelta = std::chrono::seconds::zero();
					zoomMultiplier = 1;
				}

				view.setSize(sf::Vector2f(screenWidth * zoomMultiplier, screenHeight * zoomMultiplier));
				window.setView(view);
			} else
			{
				hiddenGraceAreaViewZoomTickDelta = std::chrono::seconds::zero();

				view.setSize(sf::Vector2f(screenWidth, screenHeight));
				window.setView(view);
			}
			//remove fake-overlay of shadowInts
			if(activePiecesExistOnBoard(board, activeIntLowerUpperPair))
			{
				fakeOverlayShadowInts(board, shadowDirection, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair, shadowIntLowerUpperPair, false);
			}

			//draw counter stuff
			std::string counterString = std::to_string(score);
			theBlock.setPosition(sf::Vector2f(theBlockCounterStartX, theBlockCounterStartY));
			theBlock.setTexture(counterTexture);
			theBlock.setTextureRect(spriteSheetFrame(16, 16, 0));
			for(int x = 0; x < counterString.size(); x++)
			{
				theBlock.setTextureRect(spriteSheetFrame(16, 16, counterString[x] - '0'));
				window.draw(theBlock);
				theBlock.move(sf::Vector2f(16 * screenWidth16PixelScaleToFitMultiplier, 0));
			}
			theBlock.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(16, 16)));

			window.display();
			lastframe = std::chrono::high_resolution_clock::now();
			deltaTime = lastframe - lastlastframe;

		} else if(resetBackToStartScreen)
		{
			slamKeyPressedLastFrame = false;
			rotateKeyPressedLastFrame = false;
			saveblockKeyPressedLastFrame = false;
			saveblockUsedForCurrentBlock = false;

			totalRowsCleared = 0;
			score = 0;

			savedBlock.clear();
			currentBlockInPlay.clear();

			board.clear();
			for(int y = 0; y < boardHeight; y++)
			{
				std::vector<int> pushBackRowVector(boardWidth);
				for(int x = 0; x < boardWidth; x++)
				{
					pushBackRowVector[x] = blankIntLowerUpperPair.first;
				}
				board.push_back(pushBackRowVector);
			}

			startMenu = true;
		} else
		{
			startMenu = true;
		}
	}

	std::cout << "done!" << std::endl;
	return 0;
}
