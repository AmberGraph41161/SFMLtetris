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
static const std::map<TetrominoType, std::map<TetrominoRotation, Tetromino>> TetrominoTypeAndRotationMap =
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
	Tetris(size_t boardWidth, size_t boardHeight);
	~Tetris();

	TetrominoType getCurrentTetrominoType() const;
	const std::vector<std::vector<TetrominoBlock>>& getBoard() const;
	size_t getBoardWidth() const;
	size_t getBoardHeight() const;
	std::queue<TetrominoType> getTetrominoQueue() const;

	bool moveStateBlocksInDirection(TetrominoBlockState state, Direction direction);
	void slamStateBlocksInDirection(TetrominoBlockState state, Direction direction);
	void replaceStateBlocks(TetrominoBlockState targetState, TetrominoBlockState replaceWithThisState);
	bool placeTetromino(TetrominoType tetrominoType, TetrominoRotation tetrominoRotation, size_t placeY, size_t placeX);
	void placeTetrominoShadow();
	bool getShowTetrominoShadow() const;
	void setShowTetrominoShadow(bool showTetrominoShadow);

	bool spawnNextTetromino();
	bool moveCurrentTetromino(Direction direction);
	bool rotateCurrentTetromino(bool counterClockWise = true);
	void slamCurrentTetromino();

private:
	inline static std::mt19937 mt_{std::random_device{}()};
	int randomInt(int minimumInclusive, int maximumInclusive);
	TetrominoType randomTetrominoType();

private:
	size_t boardWidth_ = 10;
	size_t boardHeight_ = 20;
	std::vector<std::vector<TetrominoBlock>> board_;

	bool showTetrominoShadow_ = true;
	size_t currentTetrominoY_ = 0;
	size_t currentTetrominoX_ = 0;
	TetrominoType currentTetrominoType_ = TetrominoType::i;
	TetrominoRotation currentTetrominoRotation_ = TetrominoRotation::one;
	const inline static int tetrominoRotationShimmyThreshold_ = 2;

	const inline static size_t tetrominoQueueSize_ = 5;
	std::queue<TetrominoType> tetrominoQueue_;
};

}; //namespace Tetris

#endif //TETRIS_HPP
