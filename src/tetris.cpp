#include "tetris.hpp"
#include <random>

namespace Tetris
{

Tetris::Tetris()
{
	board_ = std::vector<std::vector<TetrominoBlock>>{boardHeight_, std::vector<TetrominoBlock>{boardWidth_}};
	for(size_t x = 0; x < tetrominoQueueSize_; ++x)
	{
		tetrominoQueue_.push(randomTetrominoType());
	}
}

Tetris::Tetris(size_t boardWidth, size_t boardHeight)
	: boardWidth_(boardWidth), boardHeight_(boardHeight)
{
	board_ = std::vector<std::vector<TetrominoBlock>>{boardHeight_, std::vector<TetrominoBlock>{boardWidth_}};
	for(size_t x = 0; x < tetrominoQueueSize_; ++x)
	{
		tetrominoQueue_.push(randomTetrominoType());
	}
}

Tetris::~Tetris() {}

TetrominoType Tetris::getCurrentTetrominoType() const
{
	return currentTetrominoType_;
}
const std::vector<std::vector<TetrominoBlock>>& Tetris::getBoard() const
{
	return board_;
}

size_t Tetris::getBoardWidth() const
{
	return boardWidth_;
}

size_t Tetris::getBoardHeight() const
{
	return boardHeight_;
}

std::queue<TetrominoType> Tetris::getTetrominoQueue() const
{
	return tetrominoQueue_;
}

bool Tetris::moveStateBlocksInDirection(TetrominoBlockState state, Direction direction)
{
	if(state == TetrominoBlockState::blank)
	{
		return false;
	}

	for(size_t y = 0; y < board_.size(); ++y)
	{
		for(size_t x = 0; x < board_.at(y).size(); ++x)
		{
			if(board_.at(y).at(x).state_ == state)
			{
				if
				(
					(y == 0 && direction == Direction::up) ||
					(x == 0 && direction == Direction::left) ||
					(y == board_.size() - 1 && direction == Direction::down) ||
					(x == board_.at(0).size() - 1 && direction == Direction::right)
				)
				{
					return false;
				}

				if
				(
					direction == Direction::up &&
					(
						board_.at(y - 1).at(x).state_ != state &&
						board_.at(y - 1).at(x).state_ != TetrominoBlockState::blank
					)
				)
				{
					return false;
				} else if
				(
					direction == Direction::down &&
					(
						board_.at(y + 1).at(x).state_ != state &&
						board_.at(y + 1).at(x).state_ != TetrominoBlockState::blank
					)
				)
				{
					return false;
				} else if
				(
					direction == Direction::left &&
					(
						board_.at(y).at(x - 1).state_ != state &&
						board_.at(y).at(x - 1).state_ != TetrominoBlockState::blank
					)
				)
				{
					return false;
				} else if
				(
					direction == Direction::right &&
					(
						board_.at(y).at(x + 1).state_ != state &&
						board_.at(y).at(x + 1).state_ != TetrominoBlockState::blank
					)
				)
				{
					return false;
				}
			}
		}
	}

	if(direction == Direction::up)
	{
		for(size_t y = 1; y < board_.size(); ++y)
		{
			for(size_t x = 0; x < board_.at(y).size(); ++x)
			{
				if(board_.at(y).at(x).state_ == state)
				{
					board_.at(y - 1).at(x).state_ = state;
					board_.at(y).at(x).state_ = TetrominoBlockState::blank;
				}
			}
		}
	} else if(direction == Direction::down)
	{
		for(size_t y = board_.size() - 2; y >= 0 && y < board_.size(); --y)
		{
			for(size_t x = 0; x < board_.at(y).size(); ++x)
			{
				if(board_.at(y).at(x).state_ == state)
				{
					board_.at(y + 1).at(x).state_ = state;
					board_.at(y).at(x).state_ = TetrominoBlockState::blank;
				}
			}
		}
	} else if(direction == Direction::left)
	{
		for(size_t y = 0; y < board_.size(); ++y)
		{
			for(size_t x = 1; x < board_.at(y).size(); ++x)
			{
				if(board_.at(y).at(x).state_ == state)
				{
					board_.at(y).at(x - 1).state_ = state;
					board_.at(y).at(x).state_ = TetrominoBlockState::blank;
				}
			}
		}
	} else if(direction == Direction::right)
	{
		for(size_t y = 0; y < board_.size(); ++y)
		{
			for(size_t x = board_.at(y).size() - 2; x >= 0 && x < board_.at(y).size(); --x)
			{
				if(board_.at(y).at(x).state_ == state)
				{
					board_.at(y).at(x + 1).state_ = state;
					board_.at(y).at(x).state_ = TetrominoBlockState::blank;
				}
			}
		}
	}

	return true;
}

void Tetris::slamStateBlocksInDirection(TetrominoBlockState state, Direction direction)
{
	while(moveStateBlocksInDirection(state, direction))
	{
		continue;
	}
}

void Tetris::replaceStateBlocks(TetrominoBlockState targetState, TetrominoBlockState replaceWithThisState)
{
	for(size_t y = 0; y < board_.size(); ++y)
	{
		for(size_t x = 0; x < board_.at(y).size(); ++x)
		{
			if(board_.at(y).at(x).state_ == targetState)
			{
				board_.at(y).at(x).state_ = replaceWithThisState;
			}
		}
	}
}

bool Tetris::placeTetromino(TetrominoType tetrominoType, TetrominoRotation tetrominoRotation, size_t placeY, size_t placeX)
{
	currentTetrominoY_ = placeY;
	currentTetrominoX_ = placeX;

	std::array<std::array<TetrominoBlock, 4>, 4> tetromino = TetrominoTypeAndRotationMap.at(tetrominoType).at(tetrominoRotation);
	for(size_t y = 0; y < 4; ++y)
	{
		for(size_t x = 0; x < 4; ++x)
		{
			if
			(
				tetromino.at(y).at(x).state_ == TetrominoBlockState::active &&
				(
					currentTetrominoY_ + y >= board_.size() ||
					currentTetrominoX_ + x >= board_.at(0).size()
				)
			)
			{
				return false;
			}
		}
	}

	for(size_t y = 0; y < 4; ++y)
	{
		for(size_t x = 0; x < 4; ++x)
		{
			if
			(
				tetromino.at(y).at(x).state_ == TetrominoBlockState::active &&
				board_.at(currentTetrominoY_ + y).at(currentTetrominoX_ + x).state_ != TetrominoBlockState::blank
			)
			{
				return false;
			}
		}
	}

	for(size_t y = 0; y < 4; ++y)
	{
		for(size_t x = 0; x < 4; ++x)
		{
			if(tetromino.at(y).at(x).state_ == TetrominoBlockState::active)
			{
				board_.at(currentTetrominoY_ + y).at(currentTetrominoX_ + x) = tetromino.at(y).at(x);
			}
		}
	}

	currentTetrominoType_ = tetrominoType;
	currentTetrominoRotation_ = tetrominoRotation;
	return true;
}

bool Tetris::spawnNextTetromino()
{
	bool placed = placeTetromino
	(
		tetrominoQueue_.front(),
		TetrominoRotation::one,
		0,
		(board_.at(0).size() / 2) - 2
	);
	if(placed)
	{
		tetrominoQueue_.pop();
		tetrominoQueue_.push(randomTetrominoType());
	}
	return placed;
}

bool Tetris::moveCurrentTetromino(Direction direction)
{
	if(moveStateBlocksInDirection(TetrominoBlockState::active, direction))
	{
		if(direction == Direction::up && currentTetrominoY_ != 0)
		{
			currentTetrominoY_ -= 1;
		} else if(direction == Direction::down && currentTetrominoY_ != board_.size() - 1)
		{
			currentTetrominoY_ += 1;
		} else if(direction == Direction::left && currentTetrominoX_ != 0)
		{
			currentTetrominoX_ -= 1;
		} else if(direction == Direction::right && currentTetrominoX_ != board_.at(0).size() - 1)
		{
			currentTetrominoX_ += 1;
		}
		return true;
	}
	return false;
}

bool Tetris::rotateCurrentTetromino(bool counterClockWise)
{
	replaceStateBlocks(TetrominoBlockState::active, TetrominoBlockState::blank);

	TetrominoRotation nextTetrominoRotation = currentTetrominoRotation_;
	if(counterClockWise)
	{
		if(nextTetrominoRotation == TetrominoRotation::four)
		{
			nextTetrominoRotation = TetrominoRotation::one;
		} else
		{
			nextTetrominoRotation = (TetrominoRotation)((int)currentTetrominoRotation_ + 1);
		}
	} else
	{
		if(currentTetrominoRotation_ == TetrominoRotation::one)
		{
			nextTetrominoRotation = TetrominoRotation::four;
		} else
		{
			nextTetrominoRotation = (TetrominoRotation)((int)currentTetrominoRotation_ - 1);
		}
	}
	bool rotated = placeTetromino
	(
		currentTetrominoType_,
		nextTetrominoRotation,
		currentTetrominoY_,
		currentTetrominoX_
	);
	if(!rotated)
	{
		if(!placeTetromino(currentTetrominoType_, currentTetrominoRotation_, currentTetrominoY_, currentTetrominoX_))
		{
			throw "idk man";
		}
	}
	return rotated;
}

void Tetris::slamCurrentTetromino()
{
	slamStateBlocksInDirection(TetrominoBlockState::active, Direction::down);
	replaceStateBlocks(TetrominoBlockState::active, TetrominoBlockState::inactive);
}

int Tetris::randomInt(int minimumInclusive, int maximumInclusive)
{
	std::uniform_int_distribution<int> dist(minimumInclusive, maximumInclusive);
	return dist(mt_);
}

TetrominoType Tetris::randomTetrominoType()
{
	return static_cast<TetrominoType>
	(
		randomInt
		(
			(int)TetrominoType::i,
			(int)TetrominoType::z
		)
	);
}

}; //namespace Tetris
