#include "gamefunctions.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <cmath>

intColor getIntColorFromBlockAndGroupedBLockCollection(Block block, const std::array<const Block, 7> &groupedBlockCollection)
{
	intColor color;
	if(block == groupedBlockCollection[0]) //kind of gross, but this array should be const throughout the entire execution of the program so ye...
	{
		color = intColorCyan;
	} else if(block == groupedBlockCollection[1])
	{
		color = intColorBlue;
	} else if(block == groupedBlockCollection[2])
	{
		color = intColorOrange;
	} else if(block == groupedBlockCollection[3])
	{
		color = intColorYellow;
	} else if(block == groupedBlockCollection[4])
	{
		color = intColorGreen;
	} else if(block == groupedBlockCollection[5])
	{
		color = intColorPurple;
	} else if(block == groupedBlockCollection[6])
	{
		color = intColorRed;
	} else
	{
		color = intColorCustom;
	}

	return color;
}

bool withinIntPairRange(int number, const std::pair<int, int> &intLowerUpperPair)
{
	if(number >= intLowerUpperPair.first && number <= intLowerUpperPair.second)
	{
		return true;
	}
	return false;
}

bool activePiecesExistOnBoard(std::vector<std::vector<int>> &board, const std::pair<int, int> &activeIntLowerUpperPair)
{
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				return true;
			}
		}
	}

	return false;
}

bool intPiecesExistInHiddenGrace(std::vector<std::vector<int>> &board, int boardHiddenGrace,
		const std::pair<int, int> &intPiecesLowerUpperPair)
{
	for(int y = 0; y < boardHiddenGrace; y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], intPiecesLowerUpperPair))
			{
				return true;
			}
		}
	}

	return false;
}

bool canMoveActivePiecesInDirection(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	bool canMoveActivePieces = true;
	switch(upDownLeftRight)
	{
		case directionUp:
		{
			for(int x = 0; x < board[0].size(); x++)
			{
				if(withinIntPairRange(board[0][x], activeIntLowerUpperPair))
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

					if(withinIntPairRange(board[y][x], activeIntLowerUpperPair) &&
							(
								!withinIntPairRange(board[y - 1][x], blankIntLowerUpperPair) &&
								!withinIntPairRange(board[y - 1][x], activeIntLowerUpperPair)
							))
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
				if(withinIntPairRange(board[board.size() - 1][x], activeIntLowerUpperPair))
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

					if(withinIntPairRange(board[y][x], activeIntLowerUpperPair) &&
							(
								!withinIntPairRange(board[y + 1][x], blankIntLowerUpperPair) &&
								!withinIntPairRange(board[y + 1][x], activeIntLowerUpperPair)
							))
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
				if(withinIntPairRange(board[y][0], activeIntLowerUpperPair))
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

					if(withinIntPairRange(board[y][x], activeIntLowerUpperPair) &&
							(
								!withinIntPairRange(board[y][x - 1], blankIntLowerUpperPair) &&
								!withinIntPairRange(board[y][x - 1], activeIntLowerUpperPair)
							))
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
				if(withinIntPairRange(board[y][board[y].size() - 1], activeIntLowerUpperPair))
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

					if(withinIntPairRange(board[y][x], activeIntLowerUpperPair) &&
							(
								!withinIntPairRange(board[y][x + 1], blankIntLowerUpperPair) &&
								!withinIntPairRange(board[y][x + 1], activeIntLowerUpperPair)
							))
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

void destroyActivePiecesOnBoard(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair)
{
	int intLowerUpperPairJumpDistanceActiveToBlank = blankIntLowerUpperPair.first - activeIntLowerUpperPair.first;

	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				board[y][x] += intLowerUpperPairJumpDistanceActiveToBlank;
			}
		}
	}
}

bool moveActivePiecesInDirection(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	int intLowerUpperPairJumpDistanceActiveToBlank = blankIntLowerUpperPair.first - activeIntLowerUpperPair.first;

	//move or don't move pieces after checking yo
	if(canMoveActivePiecesInDirection(board, upDownLeftRight, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
	{
		switch(upDownLeftRight)
		{
			case directionUp:
			{
				for(int y = 1; y < board.size(); y++)
				{
					for(int x = 0; x < board[y].size(); x++)
					{
						if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
						{
							board[y - 1][x] = board[y][x];
							board[y][x] += intLowerUpperPairJumpDistanceActiveToBlank;
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
						if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
						{
							board[y + 1][x] = board[y][x];
							board[y][x] += intLowerUpperPairJumpDistanceActiveToBlank;
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
						if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
						{
							board[y][x - 1] = board[y][x];
							board[y][x] += intLowerUpperPairJumpDistanceActiveToBlank;
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
						if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
						{
							board[y][x + 1] = board[y][x];
							board[y][x] += intLowerUpperPairJumpDistanceActiveToBlank;
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

		return true;
	}

	return false;
}

void slamActivePiecesInDirection(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	int intLowerUpperPairJumpDistanceActiveToInactive = inactiveIntLowerUpperPair.first - activeIntLowerUpperPair.first;

	while(true)
	{
		if(!canMoveActivePiecesInDirection(board, upDownLeftRight, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
		{
			break;
		} else
		{
			moveActivePiecesInDirection(board, upDownLeftRight, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
		}
	}

	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				board[y][x] += intLowerUpperPairJumpDistanceActiveToInactive;
			}
		}
	}
}

bool rotateActivePieces(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair, bool rotateInClockWiseDirection)
{
	int intLowerUpperPairJumpDistanceActiveToBlank = blankIntLowerUpperPair.first - activeIntLowerUpperPair.first;
	int originalActiveInt = -1;

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
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				transformationBlock.push_back(FloatingPoint(x, y));
				originalBlock.push_back(Point(x, y));

				if(originalActiveInt == -1)
				{
					originalActiveInt = board[y][x];
				}
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

	bool shimmyUpBlockArePlaceable;
	bool shimmyDownBlockArePlaceable;
	bool shimmyLeftBlockArePlaceable;
	bool shimmyRightBlockArePlaceable;

	int shimmyLeftRightN = 3;
	int shimmyUpDownN = 3;

	//clear all active before checking in rotated block area is safe to place
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				board[y][x] += intLowerUpperPairJumpDistanceActiveToBlank;
			}
		}
	}

	//first try to shimmy up/down up to +/- 2 it's feet/height
	//if doesn't work, try and shimmy the transformed block half its width to left and right
	//if doesn't work, don't rotate at all.

	for(int i = 0; i < shimmyLeftRightN; i++)
	{
		shimmyLeftBlockArePlaceable = true;
		shimmyRightBlockArePlaceable = true;

		for(int x = 0; x < shimmyLeftBlock.size(); x++)
		{
			if(shimmyLeftBlock[x].x < 0 || shimmyLeftBlock[x].x >= board[0].size() ||
				shimmyLeftBlock[x].y < 0 || shimmyLeftBlock[x].y >= board.size())
			{
				shimmyLeftBlockArePlaceable = false;
				break;
			}

			if(withinIntPairRange(board[shimmyLeftBlock[x].y][shimmyLeftBlock[x].x], inactiveIntLowerUpperPair) ||
						!withinIntPairRange(board[shimmyLeftBlock[x].y][shimmyLeftBlock[x].x], blankIntLowerUpperPair))
			{
				shimmyLeftBlockArePlaceable = false;
				break;
			}
		}
		for(int x = 0; x < shimmyRightBlock.size(); x++)
		{
			if(shimmyRightBlock[x].x < 0 || shimmyRightBlock[x].x >= board[0].size() ||
				shimmyRightBlock[x].y < 0 || shimmyRightBlock[x].y >= board.size())
			{
				shimmyRightBlockArePlaceable = false;
				break;
			}

			if(withinIntPairRange(board[shimmyRightBlock[x].y][shimmyRightBlock[x].x], inactiveIntLowerUpperPair) ||
					!withinIntPairRange(board[shimmyRightBlock[x].y][shimmyRightBlock[x].x], blankIntLowerUpperPair))
			{
				shimmyRightBlockArePlaceable = false;
				break;
			}
		}

		if(shimmyLeftBlockArePlaceable || shimmyRightBlockArePlaceable)
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
		shimmyUpBlockArePlaceable = true;
		shimmyDownBlockArePlaceable = true;

		for(int x = 0; x < shimmyUpBlock.size(); x++)
		{
			if(shimmyUpBlock[x].x < 0 || shimmyUpBlock[x].x >= board[0].size() ||
				shimmyUpBlock[x].y < 0 || shimmyUpBlock[x].y >= board.size())
			{
				shimmyUpBlockArePlaceable = false;
				break;
			}

			if(withinIntPairRange(board[shimmyUpBlock[x].y][shimmyUpBlock[x].x], inactiveIntLowerUpperPair) ||
					!withinIntPairRange(board[shimmyUpBlock[x].y][shimmyUpBlock[x].x], blankIntLowerUpperPair))
			{
				shimmyUpBlockArePlaceable = false;
				break;
			}
		}
		for(int x = 0; x < shimmyDownBlock.size(); x++)
		{
			if(shimmyDownBlock[x].x < 0 || shimmyDownBlock[x].x >= board[0].size() ||
				shimmyDownBlock[x].y < 0 || shimmyDownBlock[x].y >= board.size())
			{
				shimmyDownBlockArePlaceable = false;
				break;
			}

			if(withinIntPairRange(board[shimmyDownBlock[x].y][shimmyDownBlock[x].x], inactiveIntLowerUpperPair) ||
					!withinIntPairRange(board[shimmyDownBlock[x].y][shimmyDownBlock[x].x], blankIntLowerUpperPair))
			{
				shimmyDownBlockArePlaceable = false;
				break;
			}
		}

		if(shimmyUpBlockArePlaceable || shimmyDownBlockArePlaceable)
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

	if(shimmyDownBlockArePlaceable)
	{
		for(int x = 0; x < shimmyDownBlock.size(); x++)
		{
			board[shimmyDownBlock[x].y][shimmyDownBlock[x].x] = originalActiveInt;
		}
	} else if(shimmyUpBlockArePlaceable)
	{
		for(int x = 0; x < shimmyUpBlock.size(); x++)
		{
			board[shimmyUpBlock[x].y][shimmyUpBlock[x].x] = originalActiveInt;
		}
	} else if(shimmyLeftBlockArePlaceable)
	{
		for(int x = 0; x < shimmyLeftBlock.size(); x++)
		{
			board[shimmyLeftBlock[x].y][shimmyLeftBlock[x].x] = originalActiveInt;
		}
	} else if(shimmyRightBlockArePlaceable)
	{
		for(int x = 0; x < shimmyRightBlock.size(); x++)
		{
			board[shimmyRightBlock[x].y][shimmyRightBlock[x].x] = originalActiveInt;
		}
	} else
	{
		for(int x = 0; x < originalBlock.size(); x++)
		{
			board[originalBlock[x].y][originalBlock[x].x] = originalActiveInt;
		}
		return false;
	}

	return true;
}

void hardenActivePieces(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	int intLowerUpperPairJumpDistanceActiveToInactive = inactiveIntLowerUpperPair.first - activeIntLowerUpperPair.first;

	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				board[y][x] += intLowerUpperPairJumpDistanceActiveToInactive;
			}
		}
	}
}

void fakeOverlayShadowInts(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair,
		const std::pair<int, int> &shadowIntLowerUpperPair,
		bool showShadowChars)
{

	if(showShadowChars)
	{
		int intLowerUpperPairJumpDistanceActiveToShadow = shadowIntLowerUpperPair.first - activeIntLowerUpperPair.first;

		int originalActiveInt = -1;
		for(int y = 0; y < board.size(); y++)
		{
			for(int x = 0; x < board[y].size(); x++)
			{
				if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
				{
					originalActiveInt = board[y][x];
					break;
				}
			}

			if(originalActiveInt != -1)
			{
				break;
			}
		}

		std::vector<std::vector<int>> tempShadowBoard = board;
		while(true)
		{
			if(!canMoveActivePiecesInDirection(tempShadowBoard, upDownLeftRight, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
			{
				break;
			} else
			{
				moveActivePiecesInDirection(tempShadowBoard, upDownLeftRight, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair);
			}
		}

		for(int y = 0; y < tempShadowBoard.size(); y++)
		{
			for(int x = 0; x < tempShadowBoard[y].size(); x++)
			{
				if(withinIntPairRange(tempShadowBoard[y][x], activeIntLowerUpperPair) &&
						!withinIntPairRange(board[y][x], activeIntLowerUpperPair))
				{
					board[y][x] = originalActiveInt + intLowerUpperPairJumpDistanceActiveToShadow;
				}
			}
		}
	} else
	{
		int intLowerUpperPairJumpDistanceShadowToBlank = blankIntLowerUpperPair.first - shadowIntLowerUpperPair.first;

		for(int y = 0; y < board.size(); y++)
		{
			for(int x = 0; x < board[y].size(); x++)
			{
				if(withinIntPairRange(board[y][x], shadowIntLowerUpperPair))
				{
					board[y][x] += intLowerUpperPairJumpDistanceShadowToBlank;
				}
			}
		}
	}
}

std::vector<int> clearAndGetFullRows(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	std::vector<int> rowsCleared;

	int intLowerUpperPairJumpDistanceInactiveToBlank = blankIntLowerUpperPair.first - inactiveIntLowerUpperPair.first;

	switch(upDownLeftRight)
	{
		case directionUp:
		{
			for(int y = 0; y < board.size() - 1; y++)
			{
				bool rowIsFull = true;
				for(int x = 0; x < board[y].size(); x++)
				{
					if(!withinIntPairRange(board[y][x], activeIntLowerUpperPair))
					{
						rowIsFull = false;
						break;
					}
				}

				if(rowIsFull)
				{
					for(int anotherY = y; anotherY < board.size() - 1; anotherY++)
					{
						for(int x = 0; x < board[anotherY].size(); anotherY++)
						{
							if(withinIntPairRange(board[y + 1][x], inactiveIntLowerUpperPair) ||
									withinIntPairRange(board[y + 1][x], blankIntLowerUpperPair))
							{
								board[y][x] = board[y + 1][x];
							}
						}
					}
					for(int x = 0; x < board[board.size() - 1][x]; x++)
					{
						if(withinIntPairRange(board[board.size() - 1][x], inactiveIntLowerUpperPair))
						{
							board[board.size() - 1][x] += intLowerUpperPairJumpDistanceInactiveToBlank;
						}
					}

					rowsCleared.push_back(y);
					y--;
				}

			}
			break;
		}
		case directionDown:
		{
			for(int y = board.size() - 1; y > 0; y--)
			{
				bool rowIsFull = true;
				for(int x = 0; x < board[y].size(); x++)
				{
					if(!withinIntPairRange(board[y][x], inactiveIntLowerUpperPair))
					{
						rowIsFull = false;
						break;
					}
				}

				if(rowIsFull)
				{
					for(int anotherY = y; anotherY > 0; anotherY--)
					{
						for(int x = 0; x < board[anotherY].size(); x++)
						{
							if(withinIntPairRange(board[anotherY - 1][x], inactiveIntLowerUpperPair) ||
									withinIntPairRange(board[anotherY - 1][x], blankIntLowerUpperPair))
							{
								board[anotherY][x] = board[anotherY - 1][x];
							}
						}
					}
					for(int x = 0; x < board[0].size(); x++)
					{
						if(withinIntPairRange(board[0][x], inactiveIntLowerUpperPair))
						{
							board[0][x] += intLowerUpperPairJumpDistanceInactiveToBlank;
						}
					}

					rowsCleared.push_back(y);
					y++;
				}
			}
			break;
		}
		case directionLeft:
		{
			//board should always have same width and height without fail, so as iffy as the following directionLeft and directionRight code is, it should be fine
			for(int x = 0; x < board[0].size() - 1; x++)
			{
				bool rowIsFull = true;
				for(int y = 0; y < board.size(); y++)
				{
					if(!withinIntPairRange(board[y][x], inactiveIntLowerUpperPair))
					{
						rowIsFull = false;
						break;
					}
				}

				if(rowIsFull)
				{
					for(int anotherX = x; anotherX < board[0].size() - 1; anotherX++)
					{
						for(int y = 0; y < board.size(); y++)
						{
							if(withinIntPairRange(board[y][anotherX + 1], inactiveIntLowerUpperPair) ||
									withinIntPairRange(board[y][anotherX + 1], blankIntLowerUpperPair))
							{
								board[y][anotherX] = board[y][anotherX + 1];
							}
						}
					}
					for(int y = 0; y < board.size(); y++)
					{
						if(withinIntPairRange(board[y][board.size() - 1], inactiveIntLowerUpperPair))
						{
							board[y][board.size() - 1] += intLowerUpperPairJumpDistanceInactiveToBlank;
						}
					}

					rowsCleared.push_back(x);
					x--;
				}
			}
			break;
		}
		case directionRight:
		{
			for(int x = board[0].size() - 1; x > 0; x--)
			{
				bool rowIsFull = true;
				for(int y = 0; y < board.size(); y++)
				{
					if(!withinIntPairRange(board[y][x], inactiveIntLowerUpperPair))
					{
						rowIsFull = false;
						break;
					}
				}

				if(rowIsFull)
				{
					for(int anotherX = x; anotherX > 0; anotherX--)
					{
						for(int y = 0; y < board.size(); y++)
						{
							if(withinIntPairRange(board[y][anotherX - 1], inactiveIntLowerUpperPair) ||
									withinIntPairRange(board[y][anotherX - 1], blankIntLowerUpperPair))
							{
								board[y][anotherX] = board[y][anotherX - 1];
							}
						}
					}
					for(int y = 0; y < board.size(); y++)
					{
						if(withinIntPairRange(board[y][0], inactiveIntLowerUpperPair))
						{
							board[y][0] += intLowerUpperPairJumpDistanceInactiveToBlank;
						}
					}

					rowsCleared.push_back(x);
					x++;
				}
			}

			break;
		}

		default:
		{
			std::cout << "invalid direction to clearAndGetFullRows???" << std::endl;
			std::cout << "you've reached unreachable code" << std::endl;
			break;
		}

	}

	return rowsCleared;
}

int calculateScoreFromRowsCleared(int nRowsCleared)
{
	static int fourRowsClearedLastTimeScoreMultiplier = 0; //might change this later idk... seems iffy. Friday, November 15, 2024, 22:11:21
	static bool fourRowsClearedLastTime = false;

	if(nRowsCleared == 1)
	{
		fourRowsClearedLastTime = false;
		return 100;
	} else if(nRowsCleared == 2)
	{
		fourRowsClearedLastTime = false;
		return 150;
	} else if(nRowsCleared == 3)
	{
		fourRowsClearedLastTime = false;
		return 200;
	} else if(nRowsCleared == 4 && fourRowsClearedLastTime)
	{
		fourRowsClearedLastTime = true;
		fourRowsClearedLastTimeScoreMultiplier++;
		return 400 * fourRowsClearedLastTimeScoreMultiplier;
	} else if(nRowsCleared == 4)
	{
		fourRowsClearedLastTime = true;
		fourRowsClearedLastTimeScoreMultiplier++;
		return 400;
	}

	if(!fourRowsClearedLastTime)
	{
		fourRowsClearedLastTimeScoreMultiplier = 0;
	}

	return 0;
}

bool placeBlockAsActivePieces(std::vector<std::vector<int>> &board, direction gravityDirection, const Block &block, int boardHiddenGrace,
		const std::array<const Block, 7> &groupedBlockCollection,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	int highestBlockYLevel = -1; //for future custom block placements and what not in non-down direction
	int rightMostBlockXLevel = -1;
	for(int x = 0; x < block.size(); x++)
	{
		if(block[x].y > highestBlockYLevel)
		{
			highestBlockYLevel = block[x].y;
		}
		if(block[x].x > rightMostBlockXLevel)
		{
			rightMostBlockXLevel = block[x].x;
		}
	}

	Point offset(0, 0);
	if(intPiecesExistInHiddenGrace(board, boardHiddenGrace + 3, inactiveIntLowerUpperPair))
	{
		switch(gravityDirection)
		{
			case directionUp:
				offset = Point((board[0].size() / 2) - ((rightMostBlockXLevel + 1) / 2), board.size() - (highestBlockYLevel + 1));
				break;
			case directionDown:
				offset = Point((board[0].size() / 2) - ((rightMostBlockXLevel + 1) / 2), 0);
				break;
			case directionLeft:
				offset = Point(board[0].size() - (rightMostBlockXLevel + 1), (board.size() / 2) - ((rightMostBlockXLevel + 1) / 2));
				break;
			case directionRight:
				offset = Point(0, (board.size() / 2) - ((rightMostBlockXLevel + 1) / 2));
				break;
			default:
				std::cout << "invalid direction to move???" << std::endl;
				std::cout << "you've reached unreachable code" << std::endl;
				break;
		}
	} else
	{
		//note to self:
		//for now, the code assumes that the boardHiddenGrace area is "above" the board (top of your screen IRL)
		//change this later if you chang the boardHiddenGrace functionality; Sunday, November 17, 2024, 00:25:18

		switch(gravityDirection)
		{
			case directionUp:
				offset = Point((board[0].size() / 2) - ((rightMostBlockXLevel + 1) / 2), board.size() - (highestBlockYLevel + 1));
				break;
			case directionDown:
				offset = Point((board[0].size() / 2) - ((rightMostBlockXLevel + 1) / 2), boardHiddenGrace);
				break;
			case directionLeft:
				offset = Point(board[0].size() - (rightMostBlockXLevel + 1), (board.size() / 2) - ((rightMostBlockXLevel + 1) / 2));
				break;
			case directionRight:
				offset = Point(0, (board.size() / 2) - ((rightMostBlockXLevel + 1) / 2));
				break;
			default:
				std::cout << "invalid direction to move???" << std::endl;
				std::cout << "you've reached unreachable code" << std::endl;
				break;
		}
	}

	for(int x = 0; x < block.size(); x++)
	{
		if(!withinIntPairRange(board[block[x].y + offset.y][block[x].x + offset.x], blankIntLowerUpperPair))
		{
			return false;
		}
	}

	intColor color = getIntColorFromBlockAndGroupedBLockCollection(block, groupedBlockCollection);

	for(int x = 0; x < block.size(); x++)
	{
		board[block[x].y + offset.y][block[x].x + offset.x] = activeIntLowerUpperPair.first + color;
	}
	return true;
}

void printBoard(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair,
		const std::pair<int, int> &shadowIntLowerUpperPair)
{
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], blankIntLowerUpperPair))
			{
				std::cout << 'b';
			} else if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				std::cout << 'a';
			} else if(withinIntPairRange(board[y][x], inactiveIntLowerUpperPair))
			{
				std::cout << 'i';
			} else if(withinIntPairRange(board[y][x], shadowIntLowerUpperPair))
			{
				std::cout << 's';
			}

		}
		std::cout << std::endl;
	}

	std::cout << std::string(board[0].size(), '-') << std::endl;
}

void printBoardInt(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair,
		const std::pair<int, int> &shadowIntLowerUpperPair)
{

	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			std::cout << std::setw(3) << std::setfill(' ') << board[y][x];
		}
		std::cout << std::endl;
	}

	std::cout << std::setw(3 * board[0].size()) << std::setfill('-') << "" << std::endl;
	std::cout << std::setw(0) << std::setfill('0') << "" << std::endl;
}
