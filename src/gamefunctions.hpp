#ifndef GAMEFUNCTIONS_HPP
#define GAMEFUNCTIONS_HPP

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

enum PointState { PointStateBlank, PointStateActive, PointStateInactive, PointStateShadow };

struct Block
{
	bool operator==(const Block &block) const
	{
		if(block.color == this->color && block.pointstate == this->pointstate)
		{
			return true;
		}

		return false;
	}

	sf::Color color;
	PointState pointstate = PointStateActive;
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
	
	sf::Color color;
	PointState pointstate;
};

typedef std::array<Block, 4> TetrisBlock;
typedef std::vector<FloatingPoint> FloatingBlock;

sf::IntRect spriteSheetFrame(int spriteFrameWidth, int spriteFrameHeight, int frameNumber); //this is only for sprite sheet left to right horiztonal etc etc;

enum Direction { DirectionUp, DirectionDown, DirectionLeft, DirectionRight };
bool activePiecesExistOnBoard(std::vector<std::vector<int>> &board, const std::pair<int, int> &activeIntLowerUpperPair);
bool intPiecesExistInHiddenGrace(std::vector<std::vector<int>> &board, int boardHiddenGrace,
		const std::pair<int, int> &intPiecesLowerUpperPair);
bool canMoveActivePiecesInDirection(std::vector<std::vector<int>> &board, Direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair);
void destroyActivePiecesOnBoard(std::vector<std::vector<int>> &board,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair);
bool moveActivePiecesInDirection(std::vector<std::vector<int>> &board, Direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair);
void slamActivePiecesInDirection(std::vector<std::vector<int>> &board, Direction upDownLeftRight,
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
void fakeOverlayShadowInts(std::vector<std::vector<int>> &board, Direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair,
		const std::pair<int, int> &shadowIntLowerUpperPair,
		bool showShadowChars);
std::vector<int> clearAndGetFullRows(std::vector<std::vector<int>> &board, Direction upDownLeftRight,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair);
int calculateScoreFromRowsCleared(int nRowsCleared);
bool placeBlockAsActivePieces(std::vector<std::vector<int>> &board, Direction gravityDirection, const Block &block, int boardHiddenGrace,
		const std::array<const Block, 7> &groupedBlockCollection,
		const std::pair<int, int> &blankIntLowerUpperPair,
		const std::pair<int, int> &activeIntLowerUpperPair,
		const std::pair<int, int> &inactiveIntLowerUpperPair);
#endif
