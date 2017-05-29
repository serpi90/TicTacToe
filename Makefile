CFLAGS = -Wall -Wextra -ansi -pedantic-errors -O3

SRCDIR = src
TESTDIR = test

APPLICATIONS = app
TESTS = test_suite

OBJS = board.o board_rotation.o
TEST_OBJS = board_test.o board_rotation_test.o

.PHONY : all clean test

all : $(APPLICATIONS) $(TESTS)

app : $(SRCDIR)/app.c $(OBJS)
	$(LINK.c) -o $@ $^ -I$(SRCDIR)

test_suite : $(TESTDIR)/test_suite.c $(OBJS) $(TEST_OBJS)
	$(LINK.c) -o $@ $^ -lcunit -I$(TESTDIR)

%.o : $(SRCDIR)/%.c $(SRCDIR)/%.h
	$(LINK.c) -c $< -o $@

%.o : $(TESTDIR)/%.c $(TESTDIR)/%.h
	$(LINK.c) -c $< -o $@

clean:
	rm -f *.o $(APPLICATIONS) $(TESTS)

test: $(TESTS)
	$(foreach theTest,$(TESTS),./$(theTest);)

