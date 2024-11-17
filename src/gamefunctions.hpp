#ifndef GAMEFUNCTIONS_HPP
#define GAMEFUNCTIONS_HPP

#include <vector>

struct Point
{
	Point(int x, int y) : x(x), y(y)
	{
	}

	bool operator==(const Point &point) const
	{
		if(point.x == this->x && point.y == this->y)
		{
			return true;
		}

		return false;
	}

	int x = 0;
	int y = 0;
};

struct FloatingPoint
{
	FloatingPoint(float x, float y) : x(x), y(y)
	{
	}

	bool operator==(const FloatingPoint &floatingPoint) const
	{
		if(floatingPoint.x == this->x && floatingPoint.y == this->y)
		{
			return true;
		}

		return false;
	}

	float x = 0;
	float y = 0;
};

typedef std::vector<Point> Block;
typedef std::vector<FloatingPoint> FloatingBlock;

enum intColor { intColorCyan = 0, intColorBlue, intColorOrange, intColorYellow, intColorGreen, intColorPurple, intColorRed, intColorCustom };
intColor getIntColorFromBlockAndGroupedBLockCollection(Block block, const std::array<const Block, 7> &groupedBlockCollection);
bool withinIntPairRange(int number, const std::pair<int, int> &intLowerUpperPair);

enum direction { directionUp, directionDown, directionLeft, directionRight };
bool activePiecesExistOnBoard(std::vector<std::vector<int>> &board, const std::pair<int, int> &activeIntLowerUpperPair);
bool intPiecesExistInHiddenGrace(std::vector<std::vector<int>> &board, int boardHiddenGrace,
		const std::pair<int, int> &intPiecesLowerUpperPair);
bool canMoveActivePiecesInDirection(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair);
void destroyActivePiecesOnBoard(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair);
bool moveActivePiecesInDirection(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair);
void slamActivePiecesInDirection(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair);
bool rotateActivePieces(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankintlowerupperpair,
		const std::pair<int, int> &activeintlowerupperpair,
		const std::pair<int, int> &inactiveintlowerupperpair, bool rotateInClockWiseDirection = true);
void hardenActivePieces(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair);
void fakeOverlayShadowInts(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair,
		const std::pair<int, int> &shadowIntLowerUpperPair,
		bool showShadowChars);
std::vector<int> clearAndGetFullRows(std::vector<std::vector<int>> &board, direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair);
int calculateScoreFromRowsCleared(int nRowsCleared);
bool placeBlockAsActivePieces(std::vector<std::vector<int>> &board, direction gravityDirection, const Block &block, int boardHiddenGrace,
		const std::array<const Block, 7> &groupedBlockCollection,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair);
void printBoard(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair,
		const std::pair<int, int> &shadowIntLowerUpperPair);
void printBoardInt(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair,
		const std::pair<int, int> &shadowIntLowerUpperPair);
#endif
