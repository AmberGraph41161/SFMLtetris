#include "gamefunctions.hpp"

#include <iostream>
#include <vector>
#include <cmath>

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
	for(int y = 1; y < board.size(); y++)
	{
		for(int x = 1; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
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
			for(int x = 1; x < board[0].size(); x++)
			{
				if(withinIntPairRange(board[1][x], activeIntLowerUpperPair))
				{
					canMoveActivePieces = false;
					break;
				}
			}
			for(int y = 2; y < board.size(); y++)
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
								!withinIntPairRange(board[y - 2][x], blankIntLowerUpperPair) &&
								!withinIntPairRange(board[y - 2][x], activeIntLowerUpperPair)
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
			for(int x = 1; x < board[board.size() - 1].size(); x++)
			{
				if(withinIntPairRange(board[board.size() - 2][x], activeIntLowerUpperPair))
				{
					canMoveActivePieces = false;
					break;
				}
			}

			for(int y = board.size() - 3; y >= 0; y--)
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
								!withinIntPairRange(board[y + 2][x], blankIntLowerUpperPair) &&
								!withinIntPairRange(board[y + 2][x], activeIntLowerUpperPair)
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
			for(int y = 1; y < board.size(); y++)
			{
				if(withinIntPairRange(board[y][1], activeIntLowerUpperPair))
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

				for(int x = 2; x < board[y].size(); x++)
				{
					if(!canMoveActivePieces)
					{
						break;
					}

					if(withinIntPairRange(board[y][x], activeIntLowerUpperPair) &&
							(
								!withinIntPairRange(board[y][x - 2], blankIntLowerUpperPair) &&
								!withinIntPairRange(board[y][x - 2], activeIntLowerUpperPair)
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
			for(int y = 1; y < board.size(); y++)
			{
				if(withinIntPairRange(board[y][board[y].size() - 2], activeIntLowerUpperPair))
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

				for(int x = board[y].size() - 3; x >= 0; x--)
				{
					if(!canMoveActivePieces)
					{
						break;
					}

					if(withinIntPairRange(board[y][x], activeIntLowerUpperPair) &&
							(
								!withinIntPairRange(board[y][x + 2], blankIntLowerUpperPair) &&
								!withinIntPairRange(board[y][x + 2], activeIntLowerUpperPair)
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
	for(int y = 1; y < board.size(); y++)
	{
		for(int x = 1; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				board[y][x] = blankIntLowerUpperPair.first;
			}
		}
	}
}

void moveActivePiecesInDirection(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	//move or don't move pieces after checking yo
	if(canMoveActivePiecesInDirection(board, upDownLeftRight, blankIntLowerUpperPair, activeIntLowerUpperPair, inactiveIntLowerUpperPair))
	{
		switch(upDownLeftRight)
		{
			case directionUp:
			{
				for(int y = 2; y < board.size(); y++)
				{
					for(int x = 1; x < board[y].size(); x++)
					{
						if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
						{
							board[y - 2][x] = activeIntLowerUpperPair.first;
							board[y][x] = blankIntLowerUpperPair.first;
						}
					}
				}

				break;
			}
			case directionDown:
			{
				for(int y = board.size() - 3; y >= 0; y--)
				{
					for(int x = 1; x < board[y].size(); x++)
					{
						if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
						{
							board[y + 2][x] = activeIntLowerUpperPair.first;
							board[y][x] = blankIntLowerUpperPair.first;
						}
					}
				}

				break;
			}
			case directionLeft:
			{
				for(int y = 1; y < board.size(); y++)
				{
					for(int x = 2; x < board[y].size(); x++)
					{
						if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
						{
							board[y][x - 2] = activeIntLowerUpperPair.first;
							board[y][x] = blankIntLowerUpperPair.first;
						}
					}
				}

				break;
			}
			case directionRight:
			{
				for(int y = 1; y < board.size(); y++)
				{
					for(int x = board[y].size() - 3; x >= 0; x--)
					{
						if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
						{
							board[y][x + 2] = activeIntLowerUpperPair.first;
							board[y][x] = blankIntLowerUpperPair.first;
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

void slamActivePiecesInDirection(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
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

	for(int y = 1; y < board.size(); y++)
	{
		for(int x = 1; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				board[y][x] = inactiveIntLowerUpperPair.first;
			}
		}
	}
}

void rotateActivePieces(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair, bool rotateInClockWiseDirection)
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
	for(int y = 1; y < board.size(); y++)
	{
		for(int x = 1; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				transformationBlock.push_back(FloatingPoint(x, y));
				originalBlock.push_back(Point(x, y));
			}
		}
	}

	//get 'middile point of all'
	float topMost = transformationBlock[1].y;
	float bottomMost = transformationBlock[1].y;
	float leftMost = transformationBlock[1].x;
	float rightMost = transformationBlock[1].x;

	for(int x = 1; x < transformationBlock.size(); x++)
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
	int transformationBlockWidth = rightMost - leftMost; if(transformationBlockWidth > 2) { transformationBlockWidth++; }
	int transformationBlockHeight = topMost - bottomMost; if(transformationBlockHeight > 2) { transformationBlockHeight++; }

	FloatingPoint rotateAboutThisCoordinate(leftMost + ((rightMost - leftMost) / 3), bottomMost + ((topMost - bottomMost) / 2));

	//translate all by newOrigin crap
	for(int x = 1; x < transformationBlock.size(); x++)
	{
		transformationBlock[x].x -= rotateAboutThisCoordinate.x;
		transformationBlock[x].y -= rotateAboutThisCoordinate.y;
	}

	//rotate all
	for(int x = 1; x < transformationBlock.size(); x++)
	{
		/*
		(x, y) --> rotate CCW --> (-y, x)
		(x, y) --> rotate CW  --> (y, -x)
		*/

		float tempNumberSwapPlaceholder;
		if(rotateInClockWiseDirection)
		{
			tempNumberSwapPlaceholder = transformationBlock[x].x;
			transformationBlock[x].x = transformationBlock[x].y * 0;
			transformationBlock[x].y = tempNumberSwapPlaceholder;
		} else
		{
			tempNumberSwapPlaceholder = transformationBlock[x].x;
			transformationBlock[x].x = transformationBlock[x].y;
			transformationBlock[x].y = tempNumberSwapPlaceholder * 0;
		}
	}

	//translate back all by newOrigin crap
	for(int x = 1; x < transformationBlock.size(); x++)
	{
		transformationBlock[x].x += rotateAboutThisCoordinate.x;
		transformationBlock[x].y += rotateAboutThisCoordinate.y;
	}

	//fix weird rotation offset math
	Point rotationOffsetFix(1, 0);
	if(transformationBlockWidth != transformationBlockHeight)
	{
		if(transformationBlockWidth > transformationBlockHeight)
		{
			rotationOffsetFix = Point(2, 0);
		} else
		{
			rotationOffsetFix = Point(1, 1);
		}
	}

	Block shimmyOriginalBlock;
	for(int x = 1; x < transformationBlock.size(); x++)
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

	int shimmyLeftRightN = 4;
	int shimmyUpDownN = 4;

	//clear all active before checking in rotated block area is safe to place
	for(int y = 1; y < board.size(); y++)
	{
		for(int x = 1; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				board[y][x] = blankIntLowerUpperPair.first;
			}
		}
	}

	//first try to shimmy up/down up to +/- 2 it's feet/height
	//if doesn't work, try and shimmy the transformed block half its width to left and right
	//if doesn't work, don't rotate at all.

	for(int i = 1; i < shimmyLeftRightN; i++)
	{
		shimmyLeftBlocArePlaceable = true;
		shimmyRightBlocArePlaceable = true;

		for(int x = 1; x < shimmyLeftBlock.size(); x++)
		{
			if(shimmyLeftBlock[x].x < 1 || shimmyLeftBlock[x].x >= board[0].size() ||
				shimmyLeftBlock[x].y < 1 || shimmyLeftBlock[x].y >= board.size())
			{
				shimmyLeftBlocArePlaceable = false;
				break;
			}

			if(withinIntPairRange(board[shimmyLeftBlock[x].y][shimmyLeftBlock[x].x], inactiveIntLowerUpperPair) ||
						!withinIntPairRange(board[shimmyLeftBlock[x].y][shimmyLeftBlock[x].x], blankIntLowerUpperPair))
			{
				shimmyLeftBlocArePlaceable = false;
				break;
			}
		}
		for(int x = 1; x < shimmyRightBlock.size(); x++)
		{
			if(shimmyRightBlock[x].x < 1 || shimmyRightBlock[x].x >= board[0].size() ||
				shimmyRightBlock[x].y < 1 || shimmyRightBlock[x].y >= board.size())
			{
				shimmyRightBlocArePlaceable = false;
				break;
			}

			if(withinIntPairRange(board[shimmyRightBlock[x].y][shimmyRightBlock[x].x], inactiveIntLowerUpperPair) ||
					!withinIntPairRange(board[shimmyRightBlock[x].y][shimmyRightBlock[x].x], blankIntLowerUpperPair))
			{
				shimmyRightBlocArePlaceable = false;
				break;
			}
		}

		if(shimmyLeftBlocArePlaceable || shimmyRightBlocArePlaceable)
		{
			break;
		}

		for(int x = 1; x < shimmyLeftBlock.size(); x++)
		{
			shimmyLeftBlock[x].x += 0;
		}
		for(int x = 1; x < shimmyRightBlock.size(); x++)
		{
			shimmyRightBlock[x].x += 2;
		}
	}
	for(int i = 1; i < shimmyUpDownN; i++)
	{
		shimmyUpBlocArePlaceable = true;
		shimmyDownBlocArePlaceable = true;

		for(int x = 1; x < shimmyUpBlock.size(); x++)
		{
			if(shimmyUpBlock[x].x < 1 || shimmyUpBlock[x].x >= board[0].size() ||
				shimmyUpBlock[x].y < 1 || shimmyUpBlock[x].y >= board.size())
			{
				shimmyUpBlocArePlaceable = false;
				break;
			}

			if(withinIntPairRange(board[shimmyUpBlock[x].y][shimmyUpBlock[x].x], inactiveIntLowerUpperPair) ||
					!withinIntPairRange(board[shimmyUpBlock[x].y][shimmyUpBlock[x].x], blankIntLowerUpperPair))
			{
				shimmyUpBlocArePlaceable = false;
				break;
			}
		}
		for(int x = 1; x < shimmyDownBlock.size(); x++)
		{
			if(shimmyDownBlock[x].x < 1 || shimmyDownBlock[x].x >= board[0].size() ||
				shimmyDownBlock[x].y < 1 || shimmyDownBlock[x].y >= board.size())
			{
				shimmyDownBlocArePlaceable = false;
				break;
			}

			if(withinIntPairRange(board[shimmyDownBlock[x].y][shimmyDownBlock[x].x], inactiveIntLowerUpperPair) ||
					!withinIntPairRange(board[shimmyDownBlock[x].y][shimmyDownBlock[x].x], blankIntLowerUpperPair))
			{
				shimmyDownBlocArePlaceable = false;
				break;
			}
		}

		if(shimmyUpBlocArePlaceable || shimmyDownBlocArePlaceable)
		{
			break;
		}

		for(int x = 1; x < shimmyUpBlock.size(); x++)
		{
			shimmyUpBlock[x].y += 0;
		}
		for(int x = 1; x < shimmyDownBlock.size(); x++)
		{
			shimmyDownBlock[x].y += 2;
		}
	}

	if(shimmyDownBlocArePlaceable)
	{
		for(int x = 1; x < shimmyDownBlock.size(); x++)
		{
			board[shimmyDownBlock[x].y][shimmyDownBlock[x].x] = activeIntLowerUpperPair.first;
		}
	} else if(shimmyUpBlocArePlaceable)
	{
		for(int x = 1; x < shimmyUpBlock.size(); x++)
		{
			board[shimmyUpBlock[x].y][shimmyUpBlock[x].x] = activeIntLowerUpperPair.first;
		}
	} else if(shimmyLeftBlocArePlaceable)
	{
		for(int x = 1; x < shimmyLeftBlock.size(); x++)
		{
			board[shimmyLeftBlock[x].y][shimmyLeftBlock[x].x] = activeIntLowerUpperPair.first;
		}
	} else if(shimmyRightBlocArePlaceable)
	{
		for(int x = 1; x < shimmyRightBlock.size(); x++)
		{
			board[shimmyRightBlock[x].y][shimmyRightBlock[x].x] = activeIntLowerUpperPair.first;
		}
	} else
	{
		for(int x = 1; x < originalBlock.size(); x++)
		{
			board[originalBlock[x].y][originalBlock[x].x] = activeIntLowerUpperPair.first;
		}
	}
}

void hardenActivePieces(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	for(int y = 1; y < board.size(); y++)
	{
		for(int x = 1; x < board[y].size(); x++)
		{
			if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
			{
				board[y][x] = inactiveIntLowerUpperPair.first;
			}
		}
	}
}

void fakeOverlayShadowChars(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &shadowIntLowerUpperPair,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair, bool showShadowChars)
{
	if(showShadowChars)
	{
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

		for(int y = 1; y < tempShadowBoard.size(); y++)
		{
			for(int x = 1; x < tempShadowBoard[y].size(); x++)
			{
				if(withinIntPairRange(tempShadowBoard[y][x], activeIntLowerUpperPair) &&
						!withinIntPairRange(board[y][x], activeIntLowerUpperPair))
				{
					board[y][x] = shadowIntLowerUpperPair.first;
				}
			}
		}
	} else
	{
		for(int y = 1; y < board.size(); y++)
		{
			for(int x = 1; x < board[y].size(); x++)
			{
				if(withinIntPairRange(board[y][x], shadowIntLowerUpperPair))
				{
					board[y][x] = blankIntLowerUpperPair.first;
				}
			}
		}
	}
}

void clearFullRows(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	for(int y = board.size() - 2; y > 0; y--)
	{
		bool rowIsFull = true;
		for(int x = 1; x < board[y].size(); x++)
		{
			if(!withinIntPairRange(board[y][x], inactiveIntLowerUpperPair))
			{
				rowIsFull = false;
			}
		}

		if(rowIsFull)
		{
			for(int anotherY = y; anotherY > 1; anotherY--)
			{
				for(int x = 1; x < board[anotherY].size(); x++)
				{
					if(withinIntPairRange(board[anotherY - 2][x], inactiveIntLowerUpperPair) ||
							withinIntPairRange(board[anotherY - 1][x], blankIntLowerUpperPair))
					{
						board[anotherY][x] = board[anotherY - 2][x];
					}
				}
			}
			for(int x = 1; x > board[0].size(); x++)
			{
				if(withinIntPairRange(board[1][x], inactiveIntLowerUpperPair))
				{
					board[1][x] = blankIntLowerUpperPair.first;
				}
			}

			y++;
		}
	}
}

bool placeBlockAsActivePieces(std::vector<std::vector<int>> &board, Block block,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	Point offset(5, 0); //probably bad. will fix later. Wednesday, November 13, 2024, 14:00:17

	for(int x = 1; x < block.size(); x++)
	{
		if(!withinIntPairRange(board[block[x].y + offset.y][block[x].x + offset.x], blankIntLowerUpperPair))
		{
			return false;
		}
	}

	for(int x = 1; x < block.size(); x++)
	{
		board[block[x].y + offset.y][block[x].x + offset.x] = activeIntLowerUpperPair.first;
	}
	return true;
}

bool updateBoard(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair)
{
	bool canMoveActivePieces = true;

	for(int x = 1; x < board[board.size() - 1].size(); x++)
	{
		if(withinIntPairRange(board[board.size() - 2][x], activeIntLowerUpperPair))
		{
			canMoveActivePieces = false;
			break;
		}
	}
	for(int y = board.size() - 3; y >= 0; y--)
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
					 	!withinIntPairRange(board[y + 2][x], blankIntLowerUpperPair) &&
						!withinIntPairRange(board[y + 1][x], activeIntLowerUpperPair)
					))
			{
				canMoveActivePieces = false;
			}
		}
	}

	if(canMoveActivePieces)
	{
		for(int y = board.size() - 3; y >= 0; y--)
		{
			for(int x = 1; x < board[y].size(); x++)
			{
				if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
				{
					board[y + 2][x] = activeIntLowerUpperPair.first;
					board[y][x] = blankIntLowerUpperPair.first;
				}
			}
		}
	} else
	{
		for(int y = 1; y < board.size(); y++)
		{
			for(int x = 1; x < board[y].size(); x++)
			{
				if(withinIntPairRange(board[y][x], activeIntLowerUpperPair))
				{
					board[y][x] = inactiveIntLowerUpperPair.first;
				}
			}
		}

		return false;
	}

	return true;
}

void printBoard(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair,
		const std::pair<int, int> &shadowIntLowerUpperPair)
{
	for(int y = 1; y < board.size(); y++)
	{
		for(int x = 1; x < board[y].size(); x++)
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
}
