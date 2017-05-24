C++ = g++
CC = gcc
DFLAGS = -Wall -Wextra -ansi -pedantic-errors
OFLAGS = -O3
LFLAGS = -lcunit
CFLAGS = $(DFLAGS) $(OFLAGS) $(LFLAGS)

APPLICATIONS = board tests

COMMON_HEADERS = board.h board_rotation.h board_print.h
MODEL =
UTIL =
OBJECT_FILES = $(MODEL) $(UTIL)

all: $(OBJECT_FILES) $(APPLICATIONS)

# Target Applications

$(APPLICATIONS): %: %.c $(UTIL) $(COMMON_HEADERS)
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f *.o $(APPLICATIONS)
