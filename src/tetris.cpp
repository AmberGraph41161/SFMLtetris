#include "tetris.hpp"

namespace Tetris
{

Tetris::Tetris()
{
	board_ = std::vector<std::vector<TetrominoBlock>>{boardHeight_, std::vector<TetrominoBlock>{boardWidth_}};
	for(std::size_t x = 0; x < tetrominoQueueSize_; ++x)
	{
		tetrominoQueue_.push(randomTetrominoType());
	}
}

Tetris::Tetris(std::size_t boardWidth, std::size_t boardHeight)
	: boardWidth_(boardWidth), boardHeight_(boardHeight)
{
	board_ = std::vector<std::vector<TetrominoBlock>>{boardHeight_, std::vector<TetrominoBlock>{boardWidth_}};
	for(std::size_t x = 0; x < tetrominoQueueSize_; ++x)
	{
		tetrominoQueue_.push(randomTetrominoType());
	}
}

Tetris::~Tetris() {}

void Tetris::colorTetrominoType(TetrominoType tetrominoType, const ColorRGBA color) const
{
	TetrominoRotation rot = TetrominoRotation::one;
	while(rot != TetrominoRotation::unknown)
	{
		Tetromino& tetromino = TetrominoTypeAndRotationMap.at(tetrominoType).at(rot);
		for(std::size_t y = 0; y < tetromino.size(); ++y)
		{
			for(std::size_t x = 0; x < tetromino.at(y).size(); ++x)
			{
				if(tetromino.at(y).at(x).state_ == TetrominoBlockState::active)
				{
					tetromino.at(y).at(x).color_ = color;
				}
			}
		}
		rot = static_cast<TetrominoRotation>((std::size_t)rot + 1);
	}
}

TetrominoType Tetris::getSavedTetrominoType() const
{
	return savedTetrominoType_;
}

TetrominoType Tetris::getCurrentTetrominoType() const
{
	return currentTetrominoType_;
}

Tetromino Tetris::getTetromino(TetrominoType tetrominoType, TetrominoRotation tetrominoRotation) const
{
	return TetrominoTypeAndRotationMap.at(tetrominoType).at(tetrominoRotation);
}

const std::vector<std::vector<TetrominoBlock>>& Tetris::getBoard() const
{
	return board_;
}

std::size_t Tetris::getBoardWidth() const
{
	return boardWidth_;
}

std::size_t Tetris::getBoardHeight() const
{
	return boardHeight_;
}

std::queue<TetrominoType> Tetris::getTetrominoQueue() const
{
	return tetrominoQueue_;
}

void Tetris::setTetrominoTypeColor(TetrominoType tetrominoType, ColorRGBA color)
{
	//for(size_t y = 0; y < TetrominoTypeAndRotationMap.at(tetrominoType).at(TetrominoRotation::one);
}

bool Tetris::moveStateBlocksInDirection(TetrominoBlockState state, Direction direction, bool checkOnly)
{
	if(state == TetrominoBlockState::blank)
	{
		return false;
	}

	for(std::size_t y = 0; y < board_.size(); ++y)
	{
		for(std::size_t x = 0; x < board_.at(y).size(); ++x)
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
						board_.at(y - 1).at(x).state_ != TetrominoBlockState::blank &&
						board_.at(y - 1).at(x).state_ != TetrominoBlockState::shadow
					)
				)
				{
					return false;
				} else if
				(
					direction == Direction::down &&
					(
						board_.at(y + 1).at(x).state_ != state &&
						board_.at(y + 1).at(x).state_ != TetrominoBlockState::blank &&
						board_.at(y + 1).at(x).state_ != TetrominoBlockState::shadow
					)
				)
				{
					return false;
				} else if
				(
					direction == Direction::left &&
					(
						board_.at(y).at(x - 1).state_ != state &&
						board_.at(y).at(x - 1).state_ != TetrominoBlockState::blank &&
						board_.at(y).at(x - 1).state_ != TetrominoBlockState::shadow
					)
				)
				{
					return false;
				} else if
				(
					direction == Direction::right &&
					(
						board_.at(y).at(x + 1).state_ != state &&
						board_.at(y).at(x + 1).state_ != TetrominoBlockState::blank &&
						board_.at(y).at(x + 1).state_ != TetrominoBlockState::shadow
					)
				)
				{
					return false;
				}
			}
		}
	}

	if(checkOnly)
	{
		return true;
	}

	if(direction == Direction::up)
	{
		for(std::size_t y = 1; y < board_.size(); ++y)
		{
			for(std::size_t x = 0; x < board_.at(y).size(); ++x)
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
		for(std::size_t y = board_.size() - 2; y >= 0 && y < board_.size(); --y)
		{
			for(std::size_t x = 0; x < board_.at(y).size(); ++x)
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
		for(std::size_t y = 0; y < board_.size(); ++y)
		{
			for(std::size_t x = 1; x < board_.at(y).size(); ++x)
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
		for(std::size_t y = 0; y < board_.size(); ++y)
		{
			for(std::size_t x = board_.at(y).size() - 2; x >= 0 && x < board_.at(y).size(); --x)
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
	for(std::size_t y = 0; y < board_.size(); ++y)
	{
		for(std::size_t x = 0; x < board_.at(y).size(); ++x)
		{
			if(board_.at(y).at(x).state_ == targetState)
			{
				board_.at(y).at(x).state_ = replaceWithThisState;
			}
		}
	}
}

bool Tetris::placeTetromino(TetrominoType tetrominoType, TetrominoRotation tetrominoRotation, std::int64_t placeY, std::int64_t placeX)
{
	std::array<std::array<TetrominoBlock, 4>, 4> tetromino = TetrominoTypeAndRotationMap.at(tetrominoType).at(tetrominoRotation);
	for(std::size_t y = 0; y < tetromino.size(); ++y)
	{
		for(std::size_t x = 0; x < tetromino.at(y).size(); ++x)
		{
			if
			(
				tetromino.at(y).at(x).state_ == TetrominoBlockState::active &&
				(
					placeY + y < 0 ||
					placeX + x < 0 ||
					placeY + y >= board_.size() ||
					placeX + x >= board_.at(0).size() ||
					(
						board_.at(placeY + y).at(placeX + x).state_ != TetrominoBlockState::blank &&
						board_.at(placeY + y).at(placeX + x).state_ != TetrominoBlockState::shadow
					)
				)
			)
			{
				return false;
			}
		}
	}

	for(std::size_t y = 0; y < tetromino.size(); ++y)
	{
		for(std::size_t x = 0; x < tetromino.at(y).size(); ++x)
		{
			if(tetromino.at(y).at(x).state_ == TetrominoBlockState::active)
			{
				board_.at(placeY + y).at(placeX + x) = tetromino.at(y).at(x);
			}
		}
	}

	currentTetrominoY_ = placeY;
	currentTetrominoX_ = placeX;
	currentTetrominoType_ = tetrominoType;
	currentTetrominoRotation_ = tetrominoRotation;
	return true;
}

void Tetris::placeTetrominoShadow()
{
	replaceStateBlocks(TetrominoBlockState::active, TetrominoBlockState::shadow);
	slamStateBlocksInDirection(TetrominoBlockState::shadow, Direction::down);
	placeTetromino(currentTetrominoType_, currentTetrominoRotation_, currentTetrominoY_, currentTetrominoX_);
}

bool Tetris::getShowTetrominoShadow() const
{
	return showTetrominoShadow_;
}

void Tetris::setShowTetrominoShadow(bool showTetrominoShadow)
{
	if(showTetrominoShadow)
	{
		placeTetrominoShadow();
	} else
	{
		replaceStateBlocks(TetrominoBlockState::shadow, TetrominoBlockState::blank);
	}
	showTetrominoShadow_ = showTetrominoShadow;
}

void Tetris::pinchRow(std::size_t nthRow, Direction upOrDown)
{
	if(nthRow >= board_.size())
	{
		return;
	}
	if(upOrDown == Direction::up)
	{
		for(std::size_t row = nthRow; row < board_.size() - 1; ++row)
		{
			board_.at(row) = board_.at(row + 1);
		}
	} else if(upOrDown == Direction::down)
	{
		for(std::size_t row = nthRow; row > 0; --row)
		{
			board_.at(row) = board_.at(row - 1);
		}
	}
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
		if(showTetrominoShadow_)
		{
			replaceStateBlocks(TetrominoBlockState::shadow, TetrominoBlockState::blank);
			placeTetrominoShadow();
		}
	}
	return placed;
}

bool Tetris::moveCurrentTetromino(Direction direction)
{
	if(moveStateBlocksInDirection(TetrominoBlockState::active, direction))
	{
		if(direction == Direction::up)
		{
			currentTetrominoY_ -= 1;
		} else if(direction == Direction::down)
		{
			currentTetrominoY_ += 1;
		} else if(direction == Direction::left)
		{
			currentTetrominoX_ -= 1;
		} else if(direction == Direction::right)
		{
			currentTetrominoX_ += 1;
		}
		if(showTetrominoShadow_)
		{
			replaceStateBlocks(TetrominoBlockState::shadow, TetrominoBlockState::blank);
			placeTetrominoShadow();
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

	int rotationShimmyLeft = 0;
	int rotationShimmyRight = 0;
	int rotationShimmyUp = 0;
	int rotationShimmyDown = 0;
	while
	(
		!rotated &&
		(
			rotationShimmyLeft <= tetrominoRotationShimmyThreshold_ ||
			rotationShimmyRight <= tetrominoRotationShimmyThreshold_ ||
			rotationShimmyUp <= tetrominoRotationShimmyThreshold_ ||
			rotationShimmyDown <= tetrominoRotationShimmyThreshold_
		)
	)
	{
		if(++rotationShimmyLeft <= tetrominoRotationShimmyThreshold_)
		{
			rotated = placeTetromino
			(
				currentTetrominoType_,
				nextTetrominoRotation,
				currentTetrominoY_,
				currentTetrominoX_ - rotationShimmyLeft
			);
		} else if(++rotationShimmyRight <= tetrominoRotationShimmyThreshold_)
		{
			rotated = placeTetromino
			(
				currentTetrominoType_,
				nextTetrominoRotation,
				currentTetrominoY_,
				currentTetrominoX_ + rotationShimmyRight
			);
		} else if(++rotationShimmyUp <= tetrominoRotationShimmyThreshold_)
		{
			rotated = placeTetromino
			(
				currentTetrominoType_,
				nextTetrominoRotation,
				currentTetrominoY_ - rotationShimmyUp,
				currentTetrominoX_
			);
		} else if(++rotationShimmyDown <= tetrominoRotationShimmyThreshold_)
		{
			rotated = placeTetromino
			(
				currentTetrominoType_,
				nextTetrominoRotation,
				currentTetrominoY_ + rotationShimmyDown,
				currentTetrominoX_
			);
		}
	}

	if(!rotated)
	{
		if(!placeTetromino(currentTetrominoType_, currentTetrominoRotation_, currentTetrominoY_, currentTetrominoX_))
		{
			//should be unreachable
			//throw "something has gone wrong";
		}
	} else if(showTetrominoShadow_)
	{
		replaceStateBlocks(TetrominoBlockState::shadow, TetrominoBlockState::blank);
		placeTetrominoShadow();
	}
	return rotated;
}

void Tetris::slamCurrentTetromino()
{
	slamStateBlocksInDirection(TetrominoBlockState::active, Direction::down);
	replaceStateBlocks(TetrominoBlockState::active, TetrominoBlockState::inactive);
}

bool Tetris::swapCurrentAndSavedTetromino()
{
	replaceStateBlocks(TetrominoBlockState::active, TetrominoBlockState::blank);
	if(showTetrominoShadow_)
	{
		replaceStateBlocks(TetrominoBlockState::shadow, TetrominoBlockState::blank);
	}

	TetrominoType savedTetromino = savedTetrominoType_;
	savedTetrominoType_ = currentTetrominoType_;
	if(savedTetromino == TetrominoType::unknown)
	{
		return spawnNextTetromino();
	}
	return placeTetromino
	(
		savedTetromino,
		TetrominoRotation::one,
		0,
		(board_.at(0).size() / 2) - 2
	);
}

std::vector<std::size_t> Tetris::clearRowsAndGetClearedRowsYLevels()
{
	std::size_t clearedRows = 0;
	std::vector<std::size_t> clearedRowYLevels;

	for(std::size_t y = board_.size() - 1; y >= 0 && y < board_.size(); --y)
	{
		bool rowIsFull = true;
		for(std::size_t x = 0; x < board_.at(y).size(); ++x)
		{
			if(board_.at(y).at(x).state_ != TetrominoBlockState::inactive)
			{
				rowIsFull = false;
				break;
			}
		}
		if(rowIsFull)
		{
			++clearedRows;
			clearedRowYLevels.push_back(y);
		}
	}

	size_t pinchedNRows = 0;
	for(int x = 0; x < clearedRowYLevels.size(); ++x)
	{
		pinchRow(clearedRowYLevels.at(x - pinchedNRows), Direction::down);
		++pinchedNRows;
	}

	return clearedRowYLevels;
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
