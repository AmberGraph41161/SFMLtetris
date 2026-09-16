#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <cstdint>
#include <vector>
#include <array>
#include <map>

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
static const TetrominoBlock i = TetrominoBlock(TetrominoBlockState::inactive);
static const std::map<TetrominoType, std::map<TetrominoRotation, Tetromino>> TetrominoTypeAndRotationMap =
{
	{
		TetrominoType::i,
		{
			{
				TetrominoRotation::one,
				{{
				{ i, i, i, i },
				{ i, i, i, i },
				{ a ,a, a, a },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::two,
				{{
				{ i, a, i, i },
				{ i, a, i, i },
				{ i ,a, i, i },
				{ i, a, i, i }
				}},
			},
			{
				TetrominoRotation::three,
				{{
				{ i, i, i, i },
				{ a, a, a, a },
				{ i ,i, i, i },
				{ i, i, i, i }
				}},
			},
			{
				TetrominoRotation::four,
				{{
				{ i, i, a, i },
				{ i, i, a, i },
				{ i ,i, a, i },
				{ i, i, a, i }
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
				{ i, i, i, i },
				{ a, i, i, i },
				{ a ,a, a, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::two,
				{{
				{ i, i, i, i },
				{ i, a, a, i },
				{ i ,a, i, i },
				{ i, a, i, i }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ i, i, i, i },
				{ a, a, a, i },
				{ i ,i, a, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ i, i, i, i },
				{ i, i, a, i },
				{ i ,i, a, i },
				{ i, a, a, i }
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
				{ i, i, i, i },
				{ i, i, a, i },
				{ a ,a, a, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::two,
				{{
				{ i, i, i, i },
				{ i, a, i, i },
				{ i ,a, i, i },
				{ i, a, a, i }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ i, i, i, i },
				{ a, a, a, i },
				{ a ,i, i, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ i, a, a, i },
				{ i, i, a, i },
				{ i ,i, a, i },
				{ i, i, i, i }
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
				{ i, i, i, i },
				{ i, a, a, i },
				{ i ,a, a, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::two,
				{{
				{ i, i, i, i },
				{ i, a, a, i },
				{ i ,a, a, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ i, i, i, i },
				{ i, a, a, i },
				{ i ,a, a, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ i, i, i, i },
				{ i, a, a, i },
				{ i ,a, a, i },
				{ i, i, i, i }
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
				{ i, i, i, i },
				{ i, a, a, i },
				{ a ,a, i, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::two,
				{{
				{ i, a, i, i },
				{ i, a, a, i },
				{ i ,i, a, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ i, i, i, i },
				{ i, a, a, i },
				{ a ,a, i, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ a, i, i, i },
				{ a, a, i, i },
				{ i ,a, i, i },
				{ i, i, i, i }
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
				{ i, a, i, i },
				{ a, a, a, i },
				{ i ,i, i, i },
				{ i, i, i, i }
				}},
			},
			{
				TetrominoRotation::two,
				{{
				{ i, a, i, i },
				{ i, a, a, i },
				{ i ,a, i, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ i, i, i, i },
				{ a, a, a, i },
				{ i ,a, i, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ i, a, i, i },
				{ a, a, i, i },
				{ i ,a, i, i },
				{ i, i, i, i }
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
				{ i, i, i, i },
				{ i, a, a, i },
				{ i ,i, a, a },
				{ i, i, i, i }
				}},
			},
			{
				TetrominoRotation::two,
				{{
				{ i, i, a, i },
				{ i, a, a, i },
				{ i ,a, i, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ i, i, i, i },
				{ i, a, a, i },
				{ i ,i, a, a },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ i, i, i, a },
				{ i, i, a, a },
				{ i ,i, a, i },
				{ i, i, i, i }
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
				{ i, i, i, i },
				{ i, i, i, i },
				{ i ,i, i, i },
				{ i, i, i, i }
				}},
			},
			{
				TetrominoRotation::two,
				{{
				{ i, i, i, i },
				{ i, i, i, i },
				{ i ,i, i, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::three,
				{{
				{ i, i, i, i },
				{ i, i, i, i },
				{ i ,i, i, i },
				{ i, i, i, i }
				}}
			},
			{
				TetrominoRotation::four,
				{{
				{ i, i, i, i },
				{ i, i, i, i },
				{ i ,i, i, i },
				{ i, i, i, i }
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

	bool boardIsStateInDirectionFromPoint(size_t y, size_t x, Direction direction, TetrominoBlockState state);
	void moveStateBlocksInDirection(TetrominoBlockState state, Direction direction);
	void replaceStateBlocks(TetrominoBlockState targetState, TetrominoBlockState replaceWithThisState);

private:
	size_t boardWidth_ = 10;
	size_t boardHeight_ = 20;
	std::vector<std::vector<TetrominoBlock>> board_;

	TetrominoType currentTetrominoType_ = TetrominoType::i;
	TetrominoRotation currentTetrominoRotation_ = TetrominoRotation::one;
};

}; //namespace Tetris

#endif //TETRIS_HPP
