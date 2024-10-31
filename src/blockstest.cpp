#include <iostream>

int main()
{
	char blocks[7][2][4] = /*7 blocks total, 2-tall max, 4-wide max */
	{
		{
			{'X','X','X','X'}, //I_block
			{' ',' ',' ',' '},
		},
		{
			{'X',' ',' ',' '}, //J_block
			{'X','X','X',' '}
		},
		{
			{' ',' ','X',' '}, //L_block
			{'X','X','X',' '}
		},
		{
			{'X','X',' ',' '}, //O_block
			{'X','X',' ',' '}
		},
		{
			{' ','X','X',' '}, //S_block
			{'X','X',' ',' '}
		},
		{
			{' ','X',' ',' '}, //T_block
			{'X','X','X',' '}
		},
		{
			{'X','X',' ',' '}, //Z_block
			{' ','X','X',' '}
		},
	};

	std::cout << "sizeof(blocks)/sizeof(char) = " << sizeof(blocks)/sizeof(char) << std::endl;
	std::cout << "sizeof(blocks[0])/sizeof(char) = " << sizeof(blocks[0])/sizeof(char) << std::endl;
	std::cout << "sizeof(blocks[0][0])/sizeof(char) = " << sizeof(blocks[0][0])/sizeof(char) << std::endl;
	std::cout << "blocks = " << blocks << std::endl;
	for(int z = 0; z < 7; z++)
	{
		for(int y = 0; y < 2; y++)
		{
			for(int x = 0; x < 4; x++)
			{
				if(blocks[z][y][x] == ' ')
				{
					std::cout << '_';
				} else
				{
					std::cout << blocks[z][y][x];
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	/*
	for(int z = 0; z < sizeof(blocks)/sizeof(char); z++)
	{
		for(int y = 0; y < sizeof(blocks[0])/sizeof(char); y++)
		{
			for(int x = 0; x < sizeof(blocks[0][0])/sizeof(char); x++)
			{
				std::cout << blocks[z][y][z];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	*/
}
