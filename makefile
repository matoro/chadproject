CXX = g++
CXXFLAGS = -lSDL2 -lSDL2_mixer -g -std=c++11

SONAME 	= game
SRC	= src/test.c		\
	  src/graphic/screen.c	\
	  src/graphic/visiblecomponents.c	\
	  src/object/object.c	\
	  src/object/player.c	\
	  src/object/enemy.c	\
	  src/object/bar.c	\
	  src/object/droppable.c \
	  src/object/bullet.c	

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
