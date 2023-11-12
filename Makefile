CC := gcc # Compiler to use

# Include path for SDL2 and SDL2_ttf
SDL2_INCLUDE_PATH := $(shell sdl2-config --cflags)
SDL2_TTF_INCLUDE_PATH := -I/Users/stefano/.brew/Cellar/sdl2_ttf/2.20.2/include/SDL2

# Flags for compiler
CFLAGS := $(SDL2_INCLUDE_PATH) $(SDL2_TTF_INCLUDE_PATH) -Wall -Wextra -Werror

# Library paths for SDL2 and SDL2_ttf
SDL2_LIB_PATH := $(shell sdl2-config --libs)
SDL2_TTF_LIB_PATH := -L/Users/stefano/.brew/Cellar/sdl2_ttf/2.20.2/lib -lSDL2_ttf

# SDL2 library flags
LDFLAGS := $(SDL2_LIB_PATH) $(SDL2_TTF_LIB_PATH)

# Source files
SRC := $(wildcard *.c)

# Object files
OBJ := $(SRC:.c=.o)

# Executable name
EXEC := myprogram

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re

