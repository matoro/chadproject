CXX = g++
CXXFLAGS = -lmingw32 -lSDL2 -std=c++11 -D'M_PI=3.14159' -D'SDL_MAIN_HANDLED' -static -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc

SONAME 	= game.exe
SRC	= src/test.c		                \
	  src/graphic/screen.c	            \
	  src/graphic/visiblecomponents.c	\
	  src/object/object.c	            \
	  src/object/player.c	            \
	  src/object/enemy.c	            \
	  src/object/bar.c	                \
	  src/object/droppable.c            \
	  src/object/bullet.c               \
      src/utils/charset.c	            \
      src/collision/collision.c         \
      src/userinterface/ui.c            \
      src/gamelogic/gamelogic.c         \
      src/gamelogic/globals.c

#individual objects
OBJS	= $(SRC:.c=.o)
.c.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

#compilation:
$(SONAME): $(OBJS) $(SRC)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(SONAME)

.PHONY: all clean

clean:
	rm -f $(OBJS) $(SONAME) 
all: clean $(SONAME)
