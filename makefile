all:
	g++ src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o main
	g++ src/asciitetris.cpp src/Amber.cpp -lncurses -o asciitetris
sfmltetris:
	g++ src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o main

asciitetris:
	g++ src/asciitetris.cpp src/Amber.cpp -lncurses -o asciitetris
clean:
	echo "Cleaning ./main and ./asciitetris"
	rm main
	rm asciitetris
