WARNING_FLAGS = -Wall -Wextra -ansi -pedantic-errors
OPTIMIZATION_FLAGS = -O3
LINKER_FLAGS = -lcunit
CFLAGS = $(WARNING_FLAGS) $(OPTIMIZATION_FLAGS) $(LINKER_FLAGS)

CROSS_PLATFORM_APPLICATIONS = board
TESTS = tests_short tests_int
COMMON_HEADERS = board_rotation.h
COMMON_HEADERS += board_int.h
COMMON_HEADERS += board_short.h

APPLICATIONS = $(CROSS_PLATFORM_APPLICATIONS) $(TESTS)

.PHONY: all clean

all: $(APPLICATIONS)

clean:
	rm -f *.o *.exe $(APPLICATIONS)

test: $(TESTS)
	$(foreach theTest,$(TESTS),./$(theTest);)

$(TESTS): %: %.c $(COMMON_HEADERS) tests.c
	$(LINK.c) -o $@ $<

# sudo apt-get install mingw32
$(CROSS_PLATFORM_APPLICATIONS): %: %.c $(COMMON_HEADERS)
	$(LINK.c) -o $@ $<
	i686-w64-mingw32-gcc $(WARNING_FLAGS) $(OPTIMIZATION_FLAGS) -o $@.exe $<
