#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <ncurses.h>
#include "Amber.h"

#define stdtetrisx 10
#define stdtetrisy 24 //20 technically but 24 allow for blocks above the visible height limit of 20
#define stdtetrischar ' ' //10 'x' wide
#define stdblockscount 7
#define stdblocksheight 2
#define stdblockswidth 4

/*

        "standard Tetris board is 10 wide and 20 high"
        "The client code may create a taller board such as 10x24,
        to allow extra space at the top for the pieces to fall into play"

        XXXX    //I-block_LIGHT-BLUE

        X       //J-block_DARK-BLUE
        XXX

          X     //L-block_ORANGE
        XXX

        XX      //O-block_YELLOW
        XX

         XX     //S-block_LIGHT-GREEN
        XX

         X      //T-block_PURPLE
        XXX

        XX      //Z-block_RED
         XX
*/

namespace asciitetris
{

	//Iblock, Jblock, Lblock, Oblock, Sblock, Tblock, Zblock

	//[blocktype][y][x]
	char blocks[stdblockscount][stdblocksheight][stdblockswidth] = /*7 blocks total, 2-tall max, 4-wide max */
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

	struct coord
	{
		int y;
		int x;

		coord()
		{
			y = 0;
			x = 0;
		}
		coord(int y, int x)
		{
			this->y = y;
			this->x = x;
		}
	};

	class board
	{
		/*
		"standard Tetris board is 10 wide and 20 high"
	        "The client code may create a taller board such as 10x24,
	        to allow extra space at the top for the pieces to fall into play"
		*/
		private:
			std::vector<std::vector<char>> plane;
			std::vector<coord> selected;
		public:
			board()
			{
				for(int y = 0; y < stdtetrisy; y++)
				{
					plane.push_back(std::vector<char>());
					for(int x = 0; x < stdtetrisx; x++)
					{
						plane[y].push_back(stdtetrischar);
					}
				}
			}
			board(int X, int Y)
			{
				for(int y = 0; y < Y; y++)
				{
					plane.push_back(std::vector<char>());
					for(int x = 0; x < X; x++)
					{
						plane[y].push_back(stdtetrischar);
					}
				}
			}

			void print()
			{
				move(0, 0);
				for(int y = 0; y < plane.size(); y++)
				{
					for(int x = 0; x < plane[0].size(); x++)
					{
						printw("%c", plane[y][x]);
					}
					printw("\n");
				}
			}

			void place(int blocktype, int Y, int X)
			{
				selected.clear(); //clear block selection to place a new one
				for(int y = 0; y < stdblocksheight; y++)
				{
					for(int x = 0; x < stdblockswidth; x++)
					{
						if(blocks[blocktype][y][x] != stdtetrischar) //don't place ' ' characters
						{
							plane[Y + y][X + x] = blocks[blocktype][y][x];
							selected.push_back(coord(y, x));
						}
					}
				}
			}

			bool update() //if returned false, dead. if returned true, everything is ok
			{
				int lines = 0;

				for(int x = 0; x < plane[0].size(); x++) //check top line first and if full, game over
				{
					if(plane[0][x] == stdtetrischar)
					{
						break;
					} else if(x >= plane[0].size())
					{
						return false;
					}
				}

				//check and remove any full lines
				for(int y = plane.size() - 1; y > 0; y--) //move from bottom of plane to top
				{
					bool lineclear = true;
					bool dead = false;
					for(int x = 0; x < plane[0].size(); x++)
					{
						if(plane[y][x] == stdtetrischar) //if any blank spaces found, don't clear line
						{
							lineclear = false;
							break;
						}
					}
					if(lineclear)
					{
						lines++;
						for(int Y = 0; Y < plane.size(); Y++)
						{
							for(int X = 0; X < plane[0].size(); X++)
							{
								plane[Y][X] = stdtetrischar;
							}
						}
					}
				}

				//move everything down by 'lines' ammount after removing 'lines' ammount of lines
				for(int z = 0; z < lines; z++) //for every line we removed...
				{
					plane.pop_back();
					plane.push_back(plane[0]);
				}
				return true;
			}

			bool mv(int y, int x) //move selected blocks
			{
				if(selected.empty() == false)
				{
					//check if space ahead is empty first
					for(int i = 0; i < selected.size(); i++)
					{
						if(plane[selected[i].y + 1][selected[i].x + 1] != stdtetrischar)
						{
							return false;
						}
					}
					//place blocks after confirming that space ahead is empty
					for(int i = 0; i < selected.size(); i++)
					{
						selected[i].x += x;
						selected[i].y += y;
					}
				}
				return true;
			}

			bool isselected()
			{
				if(selected.empty())
				{
					return false;
				}
				return true;
			}
	};
}


void taco() //ESCAPE TACO AHAHAHAHAHAAKSDHFLAKF;SALJFDS;ALKFJSALKJFLSAKJDFLASJD F
{
	while(true)
	{
		char tacos = getch();
		if(tacos == '`')
		{
			endwin();
			exit(EXIT_FAILURE);
		}
	}
}

//temp runner code
int main()
{
	//ncurses init
	initscr();
	raw();
	keypad(stdscr, true);
	noecho();








	//THREADING ESCAPE KEY JUST IN CASE PROLLY GONNA GET RID OF THIS LATER IDK
	std::thread burrito(taco);








	//main vars
	bool quit = false;
	int maxscreenx;
	int maxscreeny;
	getmaxyx(stdscr, maxscreeny, maxscreenx);

	//make sure screen is large enough first
	if(maxscreeny < stdtetrisy)
	{
		quit = true;
		mvprintw(0, 0, "[ERROR \"maxscreeny < stdtetrisy\"]");
	} else
	{
		mvprintw(0, 0, "[maxscreeny >= stdtetrisy]");
	}
	if(maxscreenx < stdtetrisx)
	{
		quit = true;
		mvprintw(1, 0, "[ERROR \"maxscreenx < stdtetrisx\"]");
	} else
	{
		mvprintw(1, 0, "[maxscreenx >= stdtetrisx]");
	}
	refresh();
	AMBER::SLEEP(1.0); //sleep so you actually have time to read it lol
	clear();
	if(quit) //if any errors, quit
	{
		//MAKE SURE TO END CURSES MODE!!!
		endwin();
		exit(EXIT_FAILURE);
	}

	//if no errors, play as normal:
	srand(time(0));
	asciitetris::board Board;

	while(true)
	{
		refresh(); //refresh screen so that they can actually see things lol

		int key = getch();
		switch(key)
		{
			case 3: //KEY_UP
				//nothing for now lol 9/16/2022 12:39:54PM
				log("KEY_UP");
				break;
			case 2: //KEY_DOWN
				log("KEY_DOWN");
				Board.mv(1, 0);
				break;
			case 4: //KEY_LEFT
				log("KEY_LEFT");
				Board.mv(0, -1);
				break;
			case 5: //KEY_RIGHT
				log("KEY_RIGHT");
				Board.mv(0, 1);
				break;
		}
	}

	//end ncurses
	endwin();
}
