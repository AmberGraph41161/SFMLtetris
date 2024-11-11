all:
	clang++ -Wall -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o main src/main.cpp src/gamefunctions.cpp
