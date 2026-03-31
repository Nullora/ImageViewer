cxx = gcc
target = iv
SDL_FLAGS = $(shell sdl2-config --cflags --libs)
cxxFlags = -Wall -Wextra -g -o $(target) $(target).c

all: $(target)

$(target) : $(target).c 
	$(cxx) $(cxxFlags) $(SDL_FLAGS)

r: $(target)
	./$(target)

clean:
	rm -f $(target)
.PHONY: all clean r