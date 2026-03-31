cxx = gcc
target = iv
SDL_FLAGS = $(shell sdl2-config --cflags --libs)
cxxFlags = -Wall -Wextra -g -o $(target) $(target).c
filename = i.ppm

all: $(target)

$(target) : $(target).c 
	$(cxx) $(cxxFlags) $(SDL_FLAGS)

r: $(target)
	cat $(filename) | ./$(target)

clean:
	rm -f $(target)
.PHONY: all clean r