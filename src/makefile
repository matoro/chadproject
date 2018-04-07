CXX = g++
CXXFLAGS = -lSDL2 -lSDL2_mixer -std=c++11

SONAME 	= game
SRC	= test.c		\
	  graphic/screen.c	\
	  object/object.c	\
	  object/player.c	\
	  object/enemy.c	\
	  object/bar.c		\
	  object/droppable.c


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
