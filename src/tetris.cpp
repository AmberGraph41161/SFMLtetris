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
	board_.at(2).at(3).state_ = TetrominoBlockState::active;
	board_.at(1).at(4).state_ = TetrominoBlockState::active;

	board_.at(5).at(9).state_ = TetrominoBlockState::inactive;
	board_.at(6).at(9).state_ = TetrominoBlockState::shadow;
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

void Tetris::moveStateBlocksInDirection(TetrominoBlockState state, Direction direction)
{
	if(state == TetrominoBlockState::blank)
	{
		return;
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
					return;
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
					return;
				} else if
				(
					direction == Direction::down &&
					(
						board_.at(y + 1).at(x).state_ != state &&
						board_.at(y + 1).at(x).state_ != TetrominoBlockState::blank
					)
				)
				{
					return;
				} else if
				(
					direction == Direction::left &&
					(
						board_.at(y).at(x - 1).state_ != state &&
						board_.at(y).at(x - 1).state_ != TetrominoBlockState::blank
					)
				)
				{
					return;
				} else if
				(
					direction == Direction::right &&
					(
						board_.at(y).at(x + 1).state_ != state &&
						board_.at(y).at(x + 1).state_ != TetrominoBlockState::blank
					)
				)
				{
					return;
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
