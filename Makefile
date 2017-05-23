C++ = g++
CC = gcc
DFLAGS = -Wall -Wextra -ansi -pedantic-errors
OFLAGS = -O3
CFLAGS = $(DFLAGS) $(OFLAGS) $(LFLAGS)

APPLICATIONS = board

COMMON_HEADERS = board.h
MODEL = 
UTIL = 
OBJECT_FILES = $(MODEL) $(UTIL)

all: $(OBJECT_FILES) $(APPLICATIONS)

# Target Applications

$(APPLICATIONS): %: %.c $(UTIL) $(COMMON_HEADERS)
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f *.o $(APPLICATIONS)

