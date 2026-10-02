#include <iostream>
#include "tetris.hpp"

void print(const std::vector<std::vector<Tetris::TetrominoBlock>> board)
{
	for(size_t y = 0; y < board.size(); ++y)
	{
		for(size_t x = 0; x < board.at(y).size(); ++x)
		{
			if(board.at(y).at(x).state_ == Tetris::TetrominoBlockState::active)
			{
				std::cout << 'a';
			} else if(board.at(y).at(x).state_ == Tetris::TetrominoBlockState::inactive)
			{
				std::cout << 'i';
			} else if(board.at(y).at(x).state_ == Tetris::TetrominoBlockState::blank)
			{
				std::cout << '.';
			} else if(board.at(y).at(x).state_ == Tetris::TetrominoBlockState::shadow)
			{
				std::cout << 's';
			}
		}
		std::cout << std::endl;
	}
}

int main()
{
	Tetris::Tetris tetris(10, 20);
	if(!tetris.spawnNextTetromino())
	{
		std::cout << "failed to place tetromino" << std::endl;
	}
	print(tetris.getBoard());

	std::string getlinestring = "";
	while(getlinestring != "exit")
	{
		std::getline(std::cin, getlinestring);
		if(getlinestring == "w")
		{
			std::cout << "----------------------------------" << std::endl;
			tetris.moveCurrentTetromino(Tetris::Direction::up);
			print(tetris.getBoard());
		} else if(getlinestring == "s")
		{
			std::cout << "----------------------------------" << std::endl;
			tetris.moveCurrentTetromino(Tetris::Direction::down);
			print(tetris.getBoard());
		} else if(getlinestring == "a")
		{
			std::cout << "----------------------------------" << std::endl;
			tetris.moveCurrentTetromino(Tetris::Direction::left);
			print(tetris.getBoard());
		} else if(getlinestring == "d")
		{
			std::cout << "----------------------------------" << std::endl;
			tetris.moveCurrentTetromino(Tetris::Direction::right);
			print(tetris.getBoard());
		} else if(getlinestring == " ")
		{
			std::cout << "----------------------------------" << std::endl;
			tetris.slamCurrentTetromino();
			tetris.clearRowsAndGetClearedRowsYLevels();
			if(!tetris.spawnNextTetromino())
			{
				std::cout << "failed to place tetromino" << std::endl;
			}
			print(tetris.getBoard());
		} else if(getlinestring == "r")
		{
			std::cout << "----------------------------------" << std::endl;
			if(tetris.rotateCurrentTetromino())
			{
				std::cout << "rotated" << std::endl;
			} else
			{
				std::cout << "failed to rotate" << std::endl;
			}
			print(tetris.getBoard());
		} else if(getlinestring == "rr")
		{
			std::cout << "----------------------------------" << std::endl;
			if(tetris.rotateCurrentTetromino(false))
			{
				std::cout << "rotated" << std::endl;
			} else
			{
				std::cout << "failed to rotate" << std::endl;
			}
			print(tetris.getBoard());
		} else if(getlinestring == "c")
		{
			std::cout << "----------------------------------" << std::endl;
			if(tetris.swapCurrentAndSavedTetromino())
			{
				std::cout << "tetris.swapCurrentAndSavedTetromino(): true" << std::endl;
			} else
			{
				std::cout << "tetris.swapCurrentAndSavedTetromino(): false" << std::endl;
			}
			std::cout << "tetris.getCurrentTetrominoType(): " << (int)tetris.getCurrentTetrominoType() << std::endl;
			std::cout << "tetris.getSavedTetrominoType(): " << (int)tetris.getSavedTetrominoType() << std::endl;
			print(tetris.getBoard());
		} else if(getlinestring == "ss")
		{
			tetris.setShowTetrominoShadow(false);
			std::cout << "----------------------------------" << std::endl;
			print(tetris.getBoard());
		} else if(getlinestring == "sS")
		{
			tetris.setShowTetrominoShadow(true);
			std::cout << "----------------------------------" << std::endl;
			print(tetris.getBoard());
		}
	}
}
