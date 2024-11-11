#ifndef GAMEFUNCTIONS_HPP
#define GAMEFUNCTIONS_HPP

#include <vector>

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

typedef std::vector<Point> Block;
typedef std::vector<FloatingPoint> FloatingBlock;

enum direction { directionUp, directionDown, directionLeft, directionRight };
bool activePiecesExistOnBoard(std::vector<std::vector<char>> &board, const char &activeChar);
bool canMoveActivePiecesInDirection(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &blankChar, const char &activeChar, const char &inactiveChar);
void destroyActivePiecesOnBoard(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar);
void moveActivePiecesInDirection(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &blankChar, const char &activeChar, const char &inactiveChar);
void slamActivePiecesInDirection(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &blankChar, const char &activeChar, const char &inactiveChar);
void rotateActivePieces(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar, const char &inactiveChar, bool rotateInClockWiseDirection = true);
//void updateFullRows(std::vector<std::vector<char>> &board, direction upDownLeftRight, const char &blankChar, const char &activeChar, const char &inactiveChar)
void updateFullRows(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar, const char &inactiveChar);
bool placeBlockAsActivePieces(std::vector<std::vector<char>> &board, Block block, const char &blankChar, const char &activeChar, const char &inactiveChar);
bool updateBoard(std::vector<std::vector<char>> &board, const char &blankChar, const char &activeChar, const char &inactiveChar);
void printBoard(std::vector<std::vector<char>> &board);

#endif
