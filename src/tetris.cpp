#include "tetris.hpp"

#include <iostream>

static int anchorPointY;
static int anchorPointX;

TetrominoState getTetrominoState(TetrominoType tetrominotype, TetrominoDirectionState tetrominoDirectionState)
{
	//CLOCKWISE DIRECTION DEFAULT
	//up = clockwise spin DEFAULT
	//z = counterclockwise spin
	const std::array<TetrominoState, 4> iTetrominoStates =
	{{
		{{
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 1 ,1, 1, 1 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0 ,1, 0, 0 },
		{ 0, 1, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 0 ,0, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0 ,0, 1, 0 },
		{ 0, 0, 1, 0 }
		}},
	}};

	const std::array<TetrominoState, 4> jTetrominoStates =
	{{
		{{
		{ 0, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1 ,1, 1, 1 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0 ,1, 0, 0 },
		{ 0, 1, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 0 ,0, 0, 1 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0 ,0, 1, 0 },
		{ 0, 1, 1, 0 }
		}},
	}};

	const std::array<TetrominoState, 4> lTetrominoStates =
	{{
		{{
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 1 },
		{ 1 ,1, 1, 1 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0 ,1, 0, 0 },
		{ 0, 1, 1, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 1 ,0, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0 ,0, 1, 0 },
		{ 0, 0, 1, 0 }
		}},
	}};

	const std::array<TetrominoState, 4> oTetrominoStates =
	{{
		{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0 ,1, 1, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0 ,1, 1, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0 ,1, 1, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0 ,1, 1, 0 },
		{ 0, 0, 0, 0 }
		}},
	}};

	const std::array<TetrominoState, 4> sTetrominoStates =
	{{
		{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 1 ,1, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0 ,0, 1, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 1 ,1, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0 ,1, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
	}};

	const std::array<TetrominoState, 4> tTetrominoStates =
	{{
		{{
		{ 0, 1, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0 ,0, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0 ,1, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0 ,1, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0 ,1, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
	}};

	const std::array<TetrominoState, 4> zTetrominoStates =
	{{
		{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0 ,0, 1, 1 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0 ,1, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0 ,0, 1, 1 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 1 },
		{ 0, 0, 1, 1 },
		{ 0 ,0, 1, 0 },
		{ 0, 0, 0, 0 }
		}},
	}};

	const std::array<TetrominoState, 4> unknownTetrominoStates =
	{{
		{{
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0 ,0, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0 ,0, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0 ,0, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
		{{
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0 ,0, 0, 0 },
		{ 0, 0, 0, 0 }
		}},
	}};

	switch(tetrominotype)
	{
		case iTetromino:
		{
			return iTetrominoStates[tetrominoDirectionState];
		}

		case jTetromino:
		{
			return jTetrominoStates[tetrominoDirectionState];
		}

		case lTetromino:
		{
			return lTetrominoStates[tetrominoDirectionState];
		}

		case oTetromino:
		{
			return oTetrominoStates[tetrominoDirectionState];
		}

		case sTetromino:
		{
			return sTetrominoStates[tetrominoDirectionState];
		}

		case tTetromino:
		{
			return tTetrominoStates[tetrominoDirectionState];
		}

		case zTetromino:
		{
			return zTetrominoStates[tetrominoDirectionState];
		}

		case unknownTetromino:
		{
			return unknownTetrominoStates[tetrominoDirectionState];
		}
	}
}

bool activePiecesExistOnBoard(std::vector<std::vector<TetrisCube>> &board)
{
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(board[y][x].pointstate == PointStateActive)
			{
				return true;
			}
		}
	}

	return false;
}

bool pointStatePiecesExistOnHiddenGraceAreaOfBoard(std::vector<std::vector<TetrisCube>> &board, int boardHiddenGrace, PointState pointstate, Direction gravityDirection)
{

	switch(gravityDirection)
	{
		case DirectionUp:
		{
			for(int y = board.size(); y > board.size() - 1 - boardHiddenGrace; y--)
			{
				for(int x = 0; x < board[y].size(); x++)
				{
					if(board[y][x].pointstate == pointstate)
					{
						return true;
					}
				}
			}
			break;
		}

		case DirectionDown:
		{
			for(int y = 0; y < boardHiddenGrace; y++)
			{
				for(int x = 0; x < board[y].size(); x++)
				{
					if(board[y][x].pointstate == pointstate)
					{
						return true;
					}
				}
			}
			break;
		}

		case DirectionLeft:
		{
			if(board[0].size() > boardHiddenGrace)
			{
				return false;
			}

			for(int y = 0; y < board.size(); y++)
			{
				for(int x = 0; x < boardHiddenGrace; x++)
				{
					if(board[y][x].pointstate == pointstate)
					{
						return true;
					}
				}
			}
			break;
		}

		case DirectionRight:
		{
			if(board[0].size() > boardHiddenGrace)
			{
				return false;
			}

			for(int y = 0; y < board.size(); y++)
			{
				for(int x = board[0].size() - 1 - boardHiddenGrace; x >= 0; x++)
				{
					if(board[y][x].pointstate == pointstate)
					{
						return true;
					}
				}
			}
			break;
		}

		default:
		{
			break;
		}
	}

	return false;
}

bool canMoveActivePiecesInDirection(std::vector<std::vector<TetrisCube>> &board, Direction direction)
{
	bool canMoveActivePieces = true;
	switch(direction)
	{
		case DirectionUp:
		{
			for(int x = 0; x < board[0].size(); x++)
			{
				if(board[0][x].pointstate == PointStateActive)
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

					if
					(
						board[y][x].pointstate == PointStateActive &&
						board[y - 1][x].pointstate != PointStateBlank &&
						board[y - 1][x].pointstate != PointStateActive
					)
					{
						canMoveActivePieces = false;
					}
				}
			}
			break;
		}

		case DirectionDown:
		{
			for(int x = 0; x < board[board.size() - 1].size(); x++)
			{
				if(board[board.size() - 1][x].pointstate == PointStateActive)
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

					if
					(
						board[y][x].pointstate == PointStateActive &&
						board[y + 1][x].pointstate != PointStateBlank &&
						board[y + 1][x].pointstate != PointStateActive
					)
					{
						canMoveActivePieces = false;
					}
				}
			}
			break;
		}

		case DirectionLeft:
		{
			for(int y = 0; y < board.size(); y++)
			{
				if(board[y][0].pointstate == PointStateActive)
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

					if
					(
						board[y][x].pointstate == PointStateActive &&
						board[y][x - 1].pointstate != PointStateBlank &&
						board[y][x - 1].pointstate != PointStateActive
					)
					{
						canMoveActivePieces = false;
					}
				}
			}
			break;
		}

		case DirectionRight:
		{
			for(int y = 0; y < board.size(); y++)
			{
				if(board[y][board[y].size() - 1].pointstate == PointStateActive)
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

					if
					(
						board[y][x].pointstate == PointStateActive &&
						board[y][x +1 ].pointstate != PointStateBlank &&
						board[y][x +1 ].pointstate != PointStateActive
					)
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
			//std::cout << "invalid direction to move???" << std::endl;
			//std::cout << "you've reached unreachable code" << std::endl;
			break;
		}
	}

	return canMoveActivePieces;
}

void destroyActivePiecesOnBoard(std::vector<std::vector<TetrisCube>> &board)
{
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(board[y][x].pointstate == PointStateActive)
			{
				board[y][x].pointstate = PointStateBlank;
			}
		}
	}
}

bool moveActivePiecesInDirection(std::vector<std::vector<TetrisCube>> &board, Direction direction, bool updateTetrominoAnchors)
{
	//move or don't move pieces after checking yo
	if(canMoveActivePiecesInDirection(board, direction))
	{
		switch(direction)
		{
			case DirectionUp:
			{
				for(int y = 1; y < board.size(); y++)
				{
					for(int x = 0; x < board[y].size(); x++)
					{
						if(board[y][x].pointstate == PointStateActive)
						{
							board[y - 1][x] = board[y][x];
							board[y][x].pointstate = PointStateBlank;
						}
					}
				}

				if(updateTetrominoAnchors)
				{
					anchorPointY--;
				}
				break;
			}

			case DirectionDown:
			{
				for(int y = board.size() - 2; y >= 0; y--)
				{
					for(int x = 0; x < board[y].size(); x++)
					{
						if(board[y][x].pointstate == PointStateActive)
						{
							board[y + 1][x] = board[y][x];
							board[y][x].pointstate = PointStateBlank;
						}
					}
				}

				if(updateTetrominoAnchors)
				{
					anchorPointY++;
				}
				break;
			}

			case DirectionLeft:
			{
				for(int y = 0; y < board.size(); y++)
				{
					for(int x = 1; x < board[y].size(); x++)
					{
						if(board[y][x].pointstate == PointStateActive)
						{
							board[y][x - 1] = board[y][x];
							board[y][x].pointstate = PointStateBlank;
						}
					}
				}

				if(updateTetrominoAnchors)
				{
					anchorPointX--;
				}
				break;
			}

			case DirectionRight:
			{
				for(int y = 0; y < board.size(); y++)
				{
					for(int x = board[y].size() - 2; x >= 0; x--)
					{
						if(board[y][x].pointstate == PointStateActive)
						{
							board[y][x + 1] = board[y][x];
							board[y][x].pointstate = PointStateBlank;
						}
					}
				}

				if(updateTetrominoAnchors)
				{
					anchorPointX++;
				}
				break;
			}

			default:
			{
				//std::cout << "you've reached unreachable code" << std::endl;
				break;
			}
		}

		return true;
	}

	return false;
}

void slamActivePiecesInDireciton(std::vector<std::vector<TetrisCube>> &board, Direction direction)
{
	while(true)
	{
		if(!canMoveActivePiecesInDirection(board, direction))
		{
			break;
		} else
		{
			moveActivePiecesInDirection(board, direction);
		}
	}

	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(board[y][x].pointstate == PointStateActive)
			{
				board[y][x].pointstate = PointStateInactive;
			}
		}
	}
}

void DEBUGPRINT(TetrominoState capturedTetrominoState)
{
	for(int y = 0; y < capturedTetrominoState.size(); y++)
	{
		for(int x = 0; x < capturedTetrominoState[y].size(); x++)
		{
			if(capturedTetrominoState[y][x] == true)
			{
				std::cout << "1 ";
			} else
			{
				std::cout << "0 ";
			}
		}
		std::cout << std::endl;
	}

}

void DEBUGPRINTBOARD(std::vector<std::vector<TetrisCube>> &board)
{
	std::cout << "anchorPointY " << anchorPointY << std::endl;
	std::cout << "anchorPointX " << anchorPointX << std::endl;

	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(anchorPointY == y && anchorPointX == x)
			{
				std::cout << "@ ";
			} else if(board[y][x].pointstate == PointStateActive)
			{
				std::cout << "1 ";
			} else
			{
				std::cout << "0 ";
			}
		}
		std::cout << std::endl;
	}
}

bool rotateActivePieces(std::vector<std::vector<TetrisCube>> &board, bool rotateInClockwiseDirection)
{


	TetrominoState capturedTetrominoState;

	for(int y = 0; y < capturedTetrominoState.size(); y++)
	{
		for(int x = 0; x < capturedTetrominoState[y].size(); x++)
		{
			capturedTetrominoState[y][x] = false;

			if
			(
				anchorPointY + y >= 0 && anchorPointY + y < board.size() &&
				anchorPointX + x >= 0 && anchorPointX + x < board[0].size()
			)
			{
				if(board[anchorPointY + y][anchorPointX + x].pointstate == PointStateActive)
				{
					capturedTetrominoState[y][x] = true;
				}
			}
		}
	}

	TetrominoState nextTetrominoState;
	for(int x = iTetromino; x != unknownTetromino; x++)
	{
		for(int y = TetrominoDirectionStateOne; y != unknownTetrominoDirectionState; y++)
		{
			if(capturedTetrominoState == getTetrominoState(static_cast<TetrominoType>(x), static_cast<TetrominoDirectionState>(y)))
			{
				if(rotateInClockwiseDirection)
				{
					if(static_cast<TetrominoDirectionState>(y + 1) != unknownTetrominoDirectionState)
					{
						nextTetrominoState = getTetrominoState(static_cast<TetrominoType>(x), static_cast<TetrominoDirectionState>(y + 1));
					} else
					{
						nextTetrominoState = getTetrominoState(static_cast<TetrominoType>(x), TetrominoDirectionStateOne);
					}
				} else
				{
					if(y - 1 >= TetrominoDirectionStateOne)
					{
						nextTetrominoState = getTetrominoState(static_cast<TetrominoType>(x), static_cast<TetrominoDirectionState>(y - 1));
					} else
					{
						nextTetrominoState = getTetrominoState(static_cast<TetrominoType>(x), TetrominoDirectionStateFour);
					}
				}
			}
		}
	}

	destroyActivePiecesOnBoard(board);

	const int rotateShimmyYMax = 3;
	const int rotateShimmyYMin = -3;
	const int rotateShimmyXMax = 3;
	const int rotateShimmyXMin = -3;

	for(int y = 0; y <= rotateShimmyYMax; y++)
	{
		for(int x = 0; x <= rotateShimmyXMax; x++)
		{
			if(placeTetrominoStateOnBoard(board, nextTetrominoState, anchorPointY + y, anchorPointX + x))
			{
				anchorPointY = anchorPointY + y;
				anchorPointX = anchorPointX + x;
				return true;
			}
		}
		for(int x = 0; x >= rotateShimmyXMin; x--)
		{
			if(placeTetrominoStateOnBoard(board, nextTetrominoState, anchorPointY + y, anchorPointX + x))
			{
				anchorPointY = anchorPointY + y;
				anchorPointX = anchorPointX + x;
				return true;
			}
		}
	}
	for(int y = 0; y >= rotateShimmyYMin; y--)
	{
		for(int x = 0; x <= rotateShimmyXMax; x++)
		{
			if(placeTetrominoStateOnBoard(board, nextTetrominoState, anchorPointY + y, anchorPointX + x))
			{
				anchorPointY = anchorPointY + y;
				anchorPointX = anchorPointX + x;
				return true;
			}
		}
		for(int x = 0; x >= rotateShimmyXMin; x--)
		{
			if(placeTetrominoStateOnBoard(board, nextTetrominoState, anchorPointY + y, anchorPointX + x))
			{
				anchorPointY = anchorPointY + y;
				anchorPointX = anchorPointX + x;
				return true;
			}
		}
	}

	placeTetrominoStateOnBoard(board, capturedTetrominoState, anchorPointY, anchorPointX);
	return false;
}

void hardenActivePieces(std::vector<std::vector<TetrisCube>> &board)
{
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(board[y][x].pointstate == PointStateActive)
			{
				board[y][x].pointstate = PointStateInactive;
			}
		}
	}
}

void overlayShadow(std::vector<std::vector<TetrisCube>> &board, Direction gravityDirection)
{
	std::vector<std::vector<TetrisCube>> tempShadowBoard = board;
	while(true)
	{
		if(!canMoveActivePiecesInDirection(tempShadowBoard, gravityDirection))
		{
			break;
		} else
		{
			moveActivePiecesInDirection(tempShadowBoard, gravityDirection, false);
		}
	}

	for(int y = 0; y < tempShadowBoard.size(); y++)
	{
		for(int x = 0; x < tempShadowBoard[y].size(); x++)
		{
			if
			(
				tempShadowBoard[y][x].pointstate == PointStateActive &&
				board[y][x].pointstate != PointStateActive
			)
			{
				board[y][x].pointstate = PointStateShadow;
			}
		}
	}
}

void clearShadow(std::vector<std::vector<TetrisCube>> &board)
{
	for(int y = 0; y < board.size(); y++)
	{
		for(int x = 0; x < board[y].size(); x++)
		{
			if(board[y][x].pointstate == PointStateShadow)
			{
				board[y][x].pointstate = PointStateBlank;
			}
		}
	}
}

std::vector<int> clearAndGetFullRowYLevels(std::vector<std::vector<TetrisCube>> &board, Direction gravityDirection)
{
	std::vector<int> rowsCleared;

	switch(gravityDirection)
	{
		case DirectionUp:
		{
			for(int y = 0; y < board.size() - 1; y++)
			{
				bool rowIsFull = true;
				for(int x = 0; x < board[y].size(); x++)
				{
					if(board[y][x].pointstate != PointStateActive)
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
							if
							(
								board[y + 1][x].pointstate == PointStateInactive ||
								board[y + 1][x].pointstate == PointStateBlank
							)
							{
								board[y][x] = board[y + 1][x];
							}
						}
					}

					for(int x = 0; x < board[board.size() - 1].size(); x++)
					{
						if(board[board.size() - 1][x].pointstate == PointStateInactive)
						{
							board[board.size() - 1][x].pointstate = PointStateBlank;
						}
					}

					rowsCleared.push_back(y);
					y--;
				}

			}
			break;
		}
		case DirectionDown:
		{
			for(int y = board.size() - 1; y > 0; y--)
			{
				bool rowIsFull = true;
				for(int x = 0; x < board[y].size(); x++)
				{
					if(board[y][x].pointstate != PointStateInactive)
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
							if
							(
								board[y - 1][x].pointstate == PointStateInactive ||
								board[y - 1][x].pointstate == PointStateBlank
							)
							{
								board[anotherY][x] = board[anotherY - 1][x];
							}
						}
					}

					for(int x = 0; x < board[0].size(); x++)
					{
						if(board[0][x].pointstate == PointStateInactive)
						{
							board[0][x].pointstate = PointStateInactive;
						}
					}

					rowsCleared.push_back(y);
					y++;
				}
			}
			break;
		}
		case DirectionLeft:
		{
			//board should always have same width and height without fail, so as iffy as the following directionLeft and directionRight code is, it should be fine
			for(int x = 0; x < board[0].size() - 1; x++)
			{
				bool rowIsFull = true;
				for(int y = 0; y < board.size(); y++)
				{
					if(board[y][x].pointstate != PointStateInactive)
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
							if
							(
								board[y][anotherX + 1].pointstate == PointStateInactive ||
								board[y][anotherX + 1].pointstate == PointStateBlank
							)
							{
								board[y][anotherX] = board[y][anotherX + 1];
							}
						}
					}
					for(int y = 0; y < board.size(); y++)
					{
						if(board[y][board.size() - 1].pointstate == PointStateInactive)
						{
							board[y][board.size() - 1].pointstate = PointStateInactive;
						}
					}

					rowsCleared.push_back(x);
					x--;
				}
			}
			break;
		}
		case DirectionRight:
		{
			for(int x = board[0].size() - 1; x > 0; x--)
			{
				bool rowIsFull = true;
				for(int y = 0; y < board.size(); y++)
				{
					if(board[y][x].pointstate != PointStateInactive)
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
							if
							(
								board[y][anotherX - 1].pointstate == PointStateInactive ||
								board[y][anotherX - 1].pointstate == PointStateBlank
							)
							{
								board[y][anotherX] = board[y][anotherX - 1];
							}
						}
					}
					for(int y = 0; y < board.size(); y++)
					{
						if(board[y][0].pointstate == PointStateInactive)
						{
							board[y][0].pointstate = PointStateBlank;
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
			//std::cout << "invalid direction to clearAndGetFullRows???" << std::endl;
			//std::cout << "you've reached unreachable code" << std::endl;
			break;
		}

	}

	if(rowsCleared.size() > 1)
	{
		for(int x = rowsCleared.size() - 2; x >= 0; x--)
		{
			rowsCleared[x]--;
		}
	}
	return rowsCleared;
}

bool canPlaceTetrominoStateOnBoard(std::vector<std::vector<TetrisCube>> &board, TetrominoState tetrominostate, int placeY, int placeX)
{
	for(int y = 0; y < tetrominostate.size(); y++)
	{
		for(int x = 0; x < tetrominostate[y].size(); x++)
		{
			if(tetrominostate[y][x] == true)
			{
				if
				(
					placeY + y < 0 || placeY + y >= board.size() ||
					placeX + x < 0 || placeX + x >= board[0].size()
				)
				{
					return false;
				} else if(board[placeY + y][placeX + x].pointstate != PointStateBlank)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool placeTetrominoStateOnBoard(std::vector<std::vector<TetrisCube>> &board, TetrominoState tetrominostate, int placeY, int placeX)
{
	if(!canPlaceTetrominoStateOnBoard(board, tetrominostate, placeY, placeX))
	{
		return false;
	}

	for(int y = 0; y < tetrominostate.size(); y++)
	{
		for(int x = 0; x < tetrominostate[y].size(); x++)
		{
			if(tetrominostate[y][x] == true)
			{
				board[placeY + y][placeX + x].pointstate = PointStateActive;
			}
		}
	}

	return true;
}

bool spawnTetromino(std::vector<std::vector<TetrisCube>> &board, int boardHiddenGrace, Direction gravityDirection, TetrominoType tetrominotype)
{
	const int boardHiddenGraceActivationZone = 4;

	TetrominoState tetrominoToPlace;
	switch(gravityDirection)
	{
		case DirectionUp:
		{
			tetrominoToPlace = getTetrominoState(tetrominotype, TetrominoDirectionStateOne);
			if(pointStatePiecesExistOnHiddenGraceAreaOfBoard(board, boardHiddenGrace + boardHiddenGraceActivationZone, PointStateActive, gravityDirection))
			{
				anchorPointY = board.size() - 1  - 4;
				anchorPointX = (board[0].size() / 2) - 2;
			} else
			{
				anchorPointY = board.size() - 1  - 4 - boardHiddenGrace;
				anchorPointX = (board[0].size() / 2) - 2;
			}
			break;
		}

		case DirectionDown:
		{
			tetrominoToPlace = getTetrominoState(tetrominotype, TetrominoDirectionStateOne);
			if(pointStatePiecesExistOnHiddenGraceAreaOfBoard(board, boardHiddenGrace + boardHiddenGraceActivationZone, PointStateActive, gravityDirection))
			{
				anchorPointY = 0;
				anchorPointX = (board[0].size() / 2) - 2;
			} else
			{
				anchorPointY = 0 + boardHiddenGrace;
				anchorPointX = (board[0].size() / 2) - 2;
			}
			break;
		}

		case DirectionLeft:
		{
			tetrominoToPlace = getTetrominoState(tetrominotype, TetrominoDirectionStateTwo);
			if(pointStatePiecesExistOnHiddenGraceAreaOfBoard(board, boardHiddenGrace + boardHiddenGraceActivationZone, PointStateActive, gravityDirection))
			{
				anchorPointY = (board.size() / 2) - 2;
				anchorPointX = board[0].size() - 1 - 4;
			} else
			{
				anchorPointY = (board.size() / 2) - 2;
				anchorPointX = board[0].size() - 1 - 4 - boardHiddenGrace;
			}
			break;
		}

		case DirectionRight:
		{
			tetrominoToPlace = getTetrominoState(tetrominotype, TetrominoDirectionStateTwo);
			if(pointStatePiecesExistOnHiddenGraceAreaOfBoard(board, boardHiddenGrace + boardHiddenGraceActivationZone, PointStateActive, gravityDirection))
			{
				anchorPointY = (board.size() / 2) - 2;
				anchorPointX = 0;
			} else
			{
				anchorPointY = (board.size() / 2) - 2;
				anchorPointX = 0 + boardHiddenGrace;
			}
			break;
		}
	}

	if(!placeTetrominoStateOnBoard(board, tetrominoToPlace, anchorPointY, anchorPointX))
	{
		return false;
	}

	return true;
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
