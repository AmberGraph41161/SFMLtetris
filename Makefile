CXXFLAGS := -std=c++17 -Wall
CXXLINKLIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main: obj/main.o obj/tetris.o obj/particle.o
	clang++ $(CXXFLAGS) $(CXXLINKLIBS) -o main $^

obj/main.o: src/main.cpp
	clang++ $(CXXFLAGS) $(CXXLINKLIBS) -c -o $@ $^

obj/tetris.o: src/tetris.cpp
	clang++ $(CXXFLAGS) $(CXXLINKLIBS) -c -o $@ $^

obj/particle.o: src/particle.cpp
	clang++ $(CXXFLAGS) $(CXXLINKLIBS) -c -o $@ $^
