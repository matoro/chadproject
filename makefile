CXX = g++
CXXFLAGS = -lSDL2 -lSDL2_mixer -std=c++11

all: object.o player.o screen.o bar.o
	$(CXX) object.o player.o screen.o bar.o test.c -o game $(CXXFLAGS)

test.o: test.c
	$(CXX) -c test.c $(CXXFLAGS)
object.o: object.c
	$(CXX) -c object.c $(CXXFLAGS)
player.o: player.c
	$(CXX) -c player.c $(CXXFLAGS)
screen.o: screen.c
	$(CXX) -c screen.c $(CXXFLAGS)
bar.o: bar.c
	$(CXX) -c bar.c $(CXXFLAGS)

clean:
	rm -f *.o game
