#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <vector>
#include <array>
#include <SFML/Graphics/Color.hpp>

enum PointState { PointStateBlank, PointStateActive, PointStateInactive, PointStateShadow };
enum TetrominoType { iTetromino, jTetromino, lTetromino, oTetromino, sTetromino, tTetromino, zTetromino, unknownTetromino };
enum TetrominoDirectionState { TetrominoDirectionStateOne = 0, TetrominoDirectionStateTwo = 1, TetrominoDirectionStateThree = 2, TetrominoDirectionStateFour = 3, unknownTetrominoDirectionState };
enum Direction { DirectionUp, DirectionDown, DirectionLeft, DirectionRight };

struct TetrisCube
{
	sf::Color color;
	PointState pointstate = PointStateActive;
};

typedef std::array<std::array<bool, 4>, 4> TetrominoState;

TetrominoState getTetrominoState(TetrominoType tetrominotype, TetrominoDirectionState tetrominoDirectionState);
bool activePiecesExistOnBoard(std::vector<std::vector<TetrisCube>> &board);
bool pointStatePiecesExistOnHiddenGraceAreaOfBoard(std::vector<std::vector<TetrisCube>> &board, int boardHiddenGrace, PointState pointstate);
bool canMoveActivePiecesInDirection(std::vector<std::vector<TetrisCube>> &board, Direction direction);
void destroyActivePiecesOnBoard(std::vector<std::vector<TetrisCube>> &board);
bool moveActivePiecesInDirection(std::vector<std::vector<TetrisCube>> &board, Direction direction);
void slamActivePiecesInDireciton(std::vector<std::vector<TetrisCube>> &board, Direction direction);
bool rotateActivePieces(std::vector<std::vector<TetrisCube>> &board, bool rotateInClockwiseDirection = true);
void hardenActivePieces(std::vector<std::vector<TetrisCube>> &board);
void overlayShadow(std::vector<std::vector<TetrisCube>> &board, Direction gravityDirection);
void clearShadow(std::vector<std::vector<TetrisCube>> &board);
bool canPlaceTetrominoStateOnBoard(std::vector<std::vector<TetrisCube>> &board, TetrominoState tetrominostate, int placeY, int placeX);
bool placeTetrominoStateOnBoard(std::vector<std::vector<TetrisCube>> &board, TetrominoState tetrominostate, int placeY, int placeX);
bool spawnTetromino(std::vector<std::vector<TetrisCube>> &board, int boardHiddenGrace, Direction gravityDirection, TetrominoType tetrominotype);
std::vector<int> clearAndGetFullRowYLevels(std::vector<std::vector<TetrisCube>> &board, Direction gravityDirection);
int calculateScoreFromRowsCleared(int nRowsCleared);

#endif
