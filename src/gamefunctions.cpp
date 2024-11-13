#include "gamefunctions.hpp"

#include <iostream>
#include <vector>
#include <cmath>

bool activePiecesExistOnBoard(std::vector<std::vector<char>> &board, const char &activeChar)
{
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(board[y][x] == activeChar)
			{
				return true;
			}
		}
	}

	return false;
}

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

void destroyActivePiecesOnBoard(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar)
{
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

void slamActivePiecesInDirection(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &blankChar, const char &activeChar, const char &inactiveChar)
{
	while(true)
	{
		if(!canMoveActivePiecesInDirection(board, upDownLeftRight, blankChar, activeChar, inactiveChar))
		{
			break;
		} else
		{
			moveActivePiecesInDirection(board, upDownLeftRight, blankChar, activeChar, inactiveChar);
		}
	}

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

void rotateActivePieces(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar, const char &inactiveChar, bool rotateInClockWiseDirection)
{
	/*
	stupid math stuff
	(x, y) --> rotate CCW --> (-y, x)
	(x, y) --> rotate CW  --> (y, -x)

	measure distance between point you want to rotate about and the origin, call it newOrigin
	al - newOrigin,
	rotate al,
	al + newOrigin
	*/

	//collect all
	Block originalBlock;
	FloatingBlock transformationBlock;
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(board[y][x] == activeChar)
			{
				transformationBlock.push_back(FloatingPoint(x, y));
				originalBlock.push_back(Point(x, y));
			}
		}
	}

	//get 'middile point of all'
	float topMost = transformationBlock[0].y;
	float bottomMost = transformationBlock[0].y;
	float leftMost = transformationBlock[0].x;
	float rightMost = transformationBlock[0].x;

	for(int x = 0; x < transformationBlock.size(); x++)
	{
		if(transformationBlock[x].y > topMost)
		{
			topMost = transformationBlock[x].y;
		} else if(transformationBlock[x].y < bottomMost)
		{
			bottomMost = transformationBlock[x].y;
		}

		if(transformationBlock[x].x < leftMost)
		{
			leftMost = transformationBlock[x].x;
		} else if(transformationBlock[x].x > rightMost)
		{
			rightMost = transformationBlock[x].x;
		}
	}
	int transformationBlockWidth = rightMost - leftMost; if(transformationBlockWidth > 1) { transformationBlockWidth++; }
	int transformationBlockHeight = topMost - bottomMost; if(transformationBlockHeight > 1) { transformationBlockHeight++; }

	FloatingPoint rotateAboutThisCoordinate(leftMost + ((rightMost - leftMost) / 2), bottomMost + ((topMost - bottomMost) / 2));

	//translate all by newOrigin crap
	for(int x = 0; x < transformationBlock.size(); x++)
	{
		transformationBlock[x].x -= rotateAboutThisCoordinate.x;
		transformationBlock[x].y -= rotateAboutThisCoordinate.y;
	}

	//rotate all
	for(int x = 0; x < transformationBlock.size(); x++)
	{
		/*
		(x, y) --> rotate CCW --> (-y, x)
		(x, y) --> rotate CW  --> (y, -x)
		*/

		float tempNumberSwapPlaceholder;
		if(rotateInClockWiseDirection)
		{
			tempNumberSwapPlaceholder = transformationBlock[x].x;
			transformationBlock[x].x = transformationBlock[x].y * -1;
			transformationBlock[x].y = tempNumberSwapPlaceholder;
		} else
		{
			tempNumberSwapPlaceholder = transformationBlock[x].x;
			transformationBlock[x].x = transformationBlock[x].y;
			transformationBlock[x].y = tempNumberSwapPlaceholder * -1;
		}
	}

	//translate back all by newOrigin crap
	for(int x = 0; x < transformationBlock.size(); x++)
	{
		transformationBlock[x].x += rotateAboutThisCoordinate.x;
		transformationBlock[x].y += rotateAboutThisCoordinate.y;
	}

	//fix weird rotation offset math
	Point rotationOffsetFix(0, 0);
	if(transformationBlockWidth != transformationBlockHeight)
	{
		if(transformationBlockWidth > transformationBlockHeight)
		{
			rotationOffsetFix = Point(1, 0);
		} else
		{
			rotationOffsetFix = Point(0, 1);
		}
	}

	Block shimmyOriginalBlock;
	for(int x = 0; x < transformationBlock.size(); x++)
	{
		shimmyOriginalBlock.push_back(Point(std::floor(transformationBlock[x].x + rotationOffsetFix.x), std::floor(transformationBlock[x].y + rotationOffsetFix.y)));
	}


	Block shimmyUpBlock = shimmyOriginalBlock;
	Block shimmyDownBlock = shimmyOriginalBlock;
	Block shimmyLeftBlock = shimmyOriginalBlock;
	Block shimmyRightBlock = shimmyOriginalBlock;

	bool shimmyUpBlocArePlaceable;
	bool shimmyDownBlocArePlaceable;
	bool shimmyLeftBlocArePlaceable;
	bool shimmyRightBlocArePlaceable;

	int shimmyLeftRightN = 3;
	int shimmyUpDownN = 3;

	//clear all active before checking in rotated block area is safe to place
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

	//first try to shimmy up/down up to +/- 1 it's feet/height
	//if doesn't work, try and shimmy the transformed block half its width to left and right
	//if doesn't work, don't rotate at all.

	for(int i = 0; i < shimmyLeftRightN; i++)
	{
		shimmyLeftBlocArePlaceable = true;
		shimmyRightBlocArePlaceable = true;

		for(int x = 0; x < shimmyLeftBlock.size(); x++)
		{
			if(shimmyLeftBlock[x].x < 0 || shimmyLeftBlock[x].x >= board[0].size() ||
				shimmyLeftBlock[x].y < 0 || shimmyLeftBlock[x].y >= board.size())
			{
				shimmyLeftBlocArePlaceable = false;
				break;
			}

			if(board[shimmyLeftBlock[x].y][shimmyLeftBlock[x].x] == inactiveChar || board[shimmyLeftBlock[x].y][shimmyLeftBlock[x].x] != blankChar )
			{
				shimmyLeftBlocArePlaceable = false;
				break;
			}
		}
		for(int x = 0; x < shimmyRightBlock.size(); x++)
		{
			if(shimmyRightBlock[x].x < 0 || shimmyRightBlock[x].x >= board[0].size() ||
				shimmyRightBlock[x].y < 0 || shimmyRightBlock[x].y >= board.size())
			{
				shimmyRightBlocArePlaceable = false;
				break;
			}

			if(board[shimmyRightBlock[x].y][shimmyRightBlock[x].x] == inactiveChar || board[shimmyRightBlock[x].y][shimmyRightBlock[x].x] != blankChar )
			{
				shimmyRightBlocArePlaceable = false;
				break;
			}
		}

		if(shimmyLeftBlocArePlaceable || shimmyRightBlocArePlaceable)
		{
			break;
		}

		for(int x = 0; x < shimmyLeftBlock.size(); x++)
		{
			shimmyLeftBlock[x].x += -1;
		}
		for(int x = 0; x < shimmyRightBlock.size(); x++)
		{
			shimmyRightBlock[x].x += 1;
		}
	}
	for(int i = 0; i < shimmyUpDownN; i++)
	{
		shimmyUpBlocArePlaceable = true;
		shimmyDownBlocArePlaceable = true;

		for(int x = 0; x < shimmyUpBlock.size(); x++)
		{
			if(shimmyUpBlock[x].x < 0 || shimmyUpBlock[x].x >= board[0].size() ||
				shimmyUpBlock[x].y < 0 || shimmyUpBlock[x].y >= board.size())
			{
				shimmyUpBlocArePlaceable = false;
				break;
			}

			if(board[shimmyUpBlock[x].y][shimmyUpBlock[x].x] == inactiveChar || board[shimmyUpBlock[x].y][shimmyUpBlock[x].x] != blankChar )
			{
				shimmyUpBlocArePlaceable = false;
				break;
			}
		}
		for(int x = 0; x < shimmyDownBlock.size(); x++)
		{
			if(shimmyDownBlock[x].x < 0 || shimmyDownBlock[x].x >= board[0].size() ||
				shimmyDownBlock[x].y < 0 || shimmyDownBlock[x].y >= board.size())
			{
				shimmyDownBlocArePlaceable = false;
				break;
			}

			if(board[shimmyDownBlock[x].y][shimmyDownBlock[x].x] == inactiveChar || board[shimmyDownBlock[x].y][shimmyDownBlock[x].x] != blankChar )
			{
				shimmyDownBlocArePlaceable = false;
				break;
			}
		}

		if(shimmyUpBlocArePlaceable || shimmyDownBlocArePlaceable)
		{
			break;
		}

		for(int x = 0; x < shimmyUpBlock.size(); x++)
		{
			shimmyUpBlock[x].y += -1;
		}
		for(int x = 0; x < shimmyDownBlock.size(); x++)
		{
			shimmyDownBlock[x].y += 1;
		}
	}

	if(shimmyDownBlocArePlaceable)
	{
		for(int x = 0; x < shimmyDownBlock.size(); x++)
		{
			board[shimmyDownBlock[x].y][shimmyDownBlock[x].x] = activeChar;
		}
	} else if(shimmyUpBlocArePlaceable)
	{
		for(int x = 0; x < shimmyUpBlock.size(); x++)
		{
			board[shimmyUpBlock[x].y][shimmyUpBlock[x].x] = activeChar;
		}
	} else if(shimmyLeftBlocArePlaceable)
	{
		for(int x = 0; x < shimmyLeftBlock.size(); x++)
		{
			board[shimmyLeftBlock[x].y][shimmyLeftBlock[x].x] = activeChar;
		}
	} else if(shimmyRightBlocArePlaceable)
	{
		for(int x = 0; x < shimmyRightBlock.size(); x++)
		{
			board[shimmyRightBlock[x].y][shimmyRightBlock[x].x] = activeChar;
		}
	} else
	{
		for(int x = 0; x < originalBlock.size(); x++)
		{
			board[originalBlock[x].y][originalBlock[x].x] = activeChar;
		}
	}
}

void hardenActivePieces(std::vector<std::vector<char>> &board, const char &activeChar, const char &inactiveChar)
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

void fakeOverlayShadowChars(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &shadowChar, const char &blankChar, const char &activeChar, const char &inactiveChar, bool showShadowChars)
{
	if(showShadowChars)
	{
		std::vector<std::vector<char>> tempShadowBoard = board;
		while(true)
		{
			if(!canMoveActivePiecesInDirection(tempShadowBoard, upDownLeftRight, blankChar, activeChar, inactiveChar))
			{
				break;
			} else
			{
				moveActivePiecesInDirection(tempShadowBoard, upDownLeftRight, blankChar, activeChar, inactiveChar);
			}
		}

		for(int y = 0; y < tempShadowBoard.size(); y++)
		{
			for(int x = 0; x < tempShadowBoard[y].size(); x++)
			{
				if(tempShadowBoard[y][x] == activeChar && board[y][x] != activeChar)
				{
					board[y][x] = shadowChar;
				}
			}
		}
	} else
	{
		for(int y = 0; y < board.size(); y++)
		{
			for(int x = 0; x < board[y].size(); x++)
			{
				if(board[y][x] == shadowChar)
				{
					board[y][x] = blankChar;
				}
			}
		}
	}
}

//void updateFullRows(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &blankChar, const char &activeChar, const char &inactiveChar)
void clearFullRows(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar, const char &inactiveChar)
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

bool placeBlockAsActivePieces(std::vector<std::vector<char>> &board, Block block, const char &blankChar, const char &activeChar, const char &inactiveChar)
{
	Point offset(4, 0);

	for(int x = 0; x < block.size(); x++)
	{
		if(board[block[x].y + offset.y][block[x].x + offset.x] != blankChar)
		{
			return false;
		}
	}

	for(int x = 0; x < block.size(); x++)
	{
		board[block[x].y + offset.y][block[x].x + offset.x] = activeChar;
	}
	return true;
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
