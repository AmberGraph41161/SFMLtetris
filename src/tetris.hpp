#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <cstdint>
#include <random>
#include <vector>
#include <array>
#include <map>
#include <queue>

namespace Tetris
{

enum class TetrominoBlockState { blank, active, inactive, shadow };
struct ColorRGBA
{
	ColorRGBA() {};
	ColorRGBA(uint8_t R, uint8_t G, uint8_t B, uint8_t A)
		: R(R), G(G), B(B), A(A) {};
	ColorRGBA& operator=(const ColorRGBA& rhs)
	{
		if(this == &rhs)
		{
			return *this;
		}
		R = rhs.R;
		G = rhs.G;
		B = rhs.B;
		A = rhs.A;
		return *this;
	}
	uint8_t R = 0;
	uint8_t G = 0;
	uint8_t B = 0;
	uint8_t A = 0;
};
struct TetrominoBlock
{
	TetrominoBlock() {};
	TetrominoBlock(TetrominoBlockState state) : state_(state) {}
	TetrominoBlock(TetrominoBlockState state, ColorRGBA color) : state_(state), color_(color) {}
	TetrominoBlockState state_ = TetrominoBlockState::blank;
	ColorRGBA color_;
};

typedef std::array<std::array<TetrominoBlock, 4>, 4> Tetromino;
enum class TetrominoType { i, j, l, o, s, t, z, unknown };
enum class TetrominoRotation { one, two, three, four, unknown };

static const TetrominoBlock a = TetrominoBlock(TetrominoBlockState::active);
static const TetrominoBlock b = TetrominoBlock(TetrominoBlockState::blank);
static std::map<TetrominoType, std::map<TetrominoRotation, Tetromino>> TetrominoTypeAndRotationMap =
{
	{
		TetrominoType::i,
		{
			{
				TetrominoRotation::one,
				{{
				{ b, b, b, b },
				{ b, b, b, b },
				{ a ,a, a, a },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::two,
				{{
				{ b, a, b, b },
				{ b, a, b, b },
				{ b ,a, b, b },
				{ b, a, b, b }
				}},
			},
			{
				TetrominoRotation::three,
				{{
				{ b, b, b, b },
				{ a, a, a, a },
				{ b ,b, b, b },
				{ b, b, b, b }
				}},
			},
			{
				TetrominoRotation::four,
				{{
				{ b, b, a, b },
				{ b, b, a, b },
				{ b ,b, a, b },
				{ b, b, a, b }
				}},
			}
		},
	},

	{
		TetrominoType::j,
		{
			{
				TetrominoRotation::one,
				{{
				{ b, b, b, b },
				{ a, b, b, b },
				{ a ,a, a, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::two,
				{{
				{ b, b, b, b },
				{ b, a, a, b },
				{ b ,a, b, b },
				{ b, a, b, b }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ b, b, b, b },
				{ a, a, a, b },
				{ b ,b, a, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ b, b, b, b },
				{ b, b, a, b },
				{ b ,b, a, b },
				{ b, a, a, b }
				}}
			}
		}
	},

	{
		TetrominoType::l,
		{
			{
				TetrominoRotation::one,
				{{
				{ b, b, b, b },
				{ b, b, a, b },
				{ a ,a, a, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::two,
				{{
				{ b, b, b, b },
				{ b, a, b, b },
				{ b ,a, b, b },
				{ b, a, a, b }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ b, b, b, b },
				{ a, a, a, b },
				{ a ,b, b, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ b, a, a, b },
				{ b, b, a, b },
				{ b ,b, a, b },
				{ b, b, b, b }
				}}
			}
		}
	},

	{
		TetrominoType::o,
		{
			{
				TetrominoRotation::one,
				{{
				{ b, b, b, b },
				{ b, a, a, b },
				{ b ,a, a, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::two,
				{{
				{ b, b, b, b },
				{ b, a, a, b },
				{ b ,a, a, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ b, b, b, b },
				{ b, a, a, b },
				{ b ,a, a, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ b, b, b, b },
				{ b, a, a, b },
				{ b ,a, a, b },
				{ b, b, b, b }
				}}
			}
		}
	},

	{
		TetrominoType::s,
		{
			{
				TetrominoRotation::one,
				{{
				{ b, b, b, b },
				{ b, a, a, b },
				{ a ,a, b, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::two,
				{{
				{ b, a, b, b },
				{ b, a, a, b },
				{ b ,b, a, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ b, b, b, b },
				{ b, a, a, b },
				{ a ,a, b, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ a, b, b, b },
				{ a, a, b, b },
				{ b ,a, b, b },
				{ b, b, b, b }
				}}
			}
		}
	},

	{
		TetrominoType::t,
		{
			{
				TetrominoRotation::one,
				{{
				{ b, a, b, b },
				{ a, a, a, b },
				{ b ,b, b, b },
				{ b, b, b, b }
				}},
			},
			{
				TetrominoRotation::two,
				{{
				{ b, a, b, b },
				{ b, a, a, b },
				{ b ,a, b, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ b, b, b, b },
				{ a, a, a, b },
				{ b ,a, b, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ b, a, b, b },
				{ a, a, b, b },
				{ b ,a, b, b },
				{ b, b, b, b }
				}}
			},
		}
	},

	{
		TetrominoType::z,
		{
			{
				TetrominoRotation::one,
				{{
				{ b, b, b, b },
				{ b, a, a, b },
				{ b ,b, a, a },
				{ b, b, b, b }
				}},
			},
			{
				TetrominoRotation::two,
				{{
				{ b, b, a, b },
				{ b, a, a, b },
				{ b ,a, b, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ b, b, b, b },
				{ b, a, a, b },
				{ b ,b, a, a },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ b, b, b, a },
				{ b, b, a, a },
				{ b ,b, a, b },
				{ b, b, b, b }
				}}
			},
		}
	},

	{
		TetrominoType::unknown,
		{
			{
				TetrominoRotation::one,
				{{
				{ b, b, b, b },
				{ b, b, b, b },
				{ b ,b, b, b },
				{ b, b, b, b }
				}},
			},
			{
				TetrominoRotation::two,
				{{
				{ b, b, b, b },
				{ b, b, b, b },
				{ b ,b, b, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ b, b, b, b },
				{ b, b, b, b },
				{ b ,b, b, b },
				{ b, b, b, b }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ b, b, b, b },
				{ b, b, b, b },
				{ b ,b, b, b },
				{ b, b, b, b }
				}}
			},
		}
	},
};

enum class Direction { up, down, left, right };

class Tetris
{
public:
	Tetris();
	Tetris(std::size_t boardWidth, std::size_t boardHeight);
	~Tetris();

	void colorTetrominoType(TetrominoType tetrominoType, const ColorRGBA color) const;

	TetrominoType getSavedTetrominoType() const;
	TetrominoType getCurrentTetrominoType() const;
	Tetromino getTetromino(TetrominoType tetrominoType, TetrominoRotation tetrominoRotation) const;
	const std::vector<std::vector<TetrominoBlock>>& getBoard() const;
	std::size_t getBoardWidth() const;
	std::size_t getBoardHeight() const;
	std::queue<TetrominoType> getTetrominoQueue() const;

	void setTetrominoTypeColor(TetrominoType tetrominoType, ColorRGBA color);
	bool moveStateBlocksInDirection(TetrominoBlockState state, Direction direction, bool checkOnly = false);
	void slamStateBlocksInDirection(TetrominoBlockState state, Direction direction);
	void replaceStateBlocks(TetrominoBlockState targetState, TetrominoBlockState replaceWithThisState);
	bool placeTetromino(TetrominoType tetrominoType, TetrominoRotation tetrominoRotation, std::int64_t placeY, std::int64_t placeX);
	void placeTetrominoShadow();
	bool getShowTetrominoShadow() const;
	void setShowTetrominoShadow(bool showTetrominoShadow);
	void pinchRow(std::size_t nthRow, Direction upOrDown = Direction::down);

	bool spawnNextTetromino();
	bool moveCurrentTetromino(Direction direction);
	bool rotateCurrentTetromino(bool counterClockWise = true);
	void slamCurrentTetromino();
	bool swapCurrentAndSavedTetromino();
	std::vector<std::size_t> clearRowsAndGetClearedRowsYLevels();

private:
	inline static std::mt19937 mt_{std::random_device{}()};
	int randomInt(int minimumInclusive, int maximumInclusive);
	TetrominoType randomTetrominoType();

private:
	std::size_t boardWidth_ = 10;
	std::size_t boardHeight_ = 20;
	std::vector<std::vector<TetrominoBlock>> board_;

	bool showTetrominoShadow_ = true;
	std::uint64_t currentTetrominoY_ = 0;
	std::uint64_t currentTetrominoX_ = 0;
	TetrominoType savedTetrominoType_ = TetrominoType::unknown;
	TetrominoType currentTetrominoType_ = TetrominoType::i;
	TetrominoRotation currentTetrominoRotation_ = TetrominoRotation::one;
	const inline static int tetrominoRotationShimmyThreshold_ = 2;

	const inline static std::size_t tetrominoQueueSize_ = 5;
	std::queue<TetrominoType> tetrominoQueue_;
};

}; //namespace Tetris

#endif //TETRIS_HPP
