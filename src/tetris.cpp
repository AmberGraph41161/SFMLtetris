#include "tetris.hpp"

namespace Tetris
{

Tetris::Tetris()
{
	board_ = std::vector<std::vector<TetrominoBlock>>{boardHeight_, std::vector<TetrominoBlock>{boardWidth_}};
}

Tetris::Tetris(size_t boardWidth, size_t boardHeight)
	: boardWidth_(boardWidth), boardHeight_(boardHeight)
{
	board_ = std::vector<std::vector<TetrominoBlock>>{boardHeight_, std::vector<TetrominoBlock>{boardWidth_}};
	board_.at(1).at(1).state_ = TetrominoBlockState::active;
	board_.at(1).at(2).state_ = TetrominoBlockState::active;
	board_.at(1).at(3).state_ = TetrominoBlockState::active;
	board_.at(1).at(4).state_ = TetrominoBlockState::active;
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

bool Tetris::boardIsStateInDirectionFromPoint(size_t y, size_t x, Direction direction, TetrominoBlockState state)
{
	if(y >= board_.size() - 1 && direction == Direction::down)
	{
		return false;
	} else if(x >= board_.at(0).size() - 1 && direction == Direction::right)
	{
		return false;
	} else if(y <= 0 && direction == Direction::up)
	{
		return false;
	} else if(x <= 0 && direction == Direction::left)
	{
		return false;
	}

	return
	(
		direction == Direction::up &&
		board_.at(y - 1).at(x).state_ == state
	) ||
	(
		direction == Direction::down &&
		board_.at(y + 1).at(x).state_ == state
	) ||
	(
		direction == Direction::left &&
		board_.at(y).at(x - 1).state_ == state
	) ||
	(
		direction == Direction::right &&
		board_.at(y).at(x + 1).state_ == state
	);
}
void Tetris::moveStateBlocksInDirection(TetrominoBlockState state, Direction direction)
{
	if(state == TetrominoBlockState::blank)
	{
		return;
	}

	if(direction == Direction::up)
	{
		for(size_t x = 0; x < board_.at(0).size(); ++x)
		{
			if(board_.at(0).at(x).state_ == state)
			{
				return;
			}
		}
	} else if(direction == Direction::down)
	{
		for(size_t x = 0; x < board_.at(board_.size() - 1).size(); ++x)
		{
			if(board_.at(board_.size() - 1).at(x).state_ == state)
			{
				return;
			}
		}
	} else if(direction == Direction::left)
	{
		for(size_t y = 0; y < board_.size(); ++y)
		{
			if(board_.at(y).at(0).state_ == state)
			{
				return;
			}
		}
	} else if(direction == Direction::right)
	{
		for(size_t y = 0; y < board_.size(); ++y)
		{
			if(board_.at(y).at(board_.at(y).size() - 1).state_ == state)
			{
				return;
			}
		}
	}

	for(int y = 1; y < board_.size() - 1; ++y)
	{
		for(int x = 1; x < board_.at(y).size() - 1; ++x)
		{
			if
			(
				board_.at(y).at(x).state_ == state &&
				(
					!boardIsStateInDirectionFromPoint(y, x, direction, TetrominoBlockState::blank) &&
					!boardIsStateInDirectionFromPoint(y, x, direction, state)
				)
			)
			{
				return;
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

}; //namespace Tetris
