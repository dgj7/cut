# compile
CC = gcc
CFLAGS = -Wall -g

# build variables
LIBSRC   := $(filter-out src/main.c, $(shell find src -name "*.c"))
MAINSRC  := $(shell find src -name "*.c")
TESTSRC  := $(LIBSRC) $(shell find test -name "*.c")
BUILDDIR := target
PROGRAM  := $(BUILDDIR)/main.exe
TEST     := $(BUILDDIR)/test.exe

# tasks
.PHONY: all build test clean print
all: clean test build
build: $(PROGRAM)
test: $(TEST)

# build and run the test program; exits if any tests fail
$(TEST): $(TESTSRC)
	@echo -n compiling tests: $^ $@ ...
	@$(CC) $(CFLAGS) -o $@ $^ && echo done!
	@$(TEST)

# build the main program
$(PROGRAM): $(MAINSRC) $(HEADER)
	@echo -n compiling main: $^ $@ ...
	@$(CC) $(CFLAGS) -o $@ $^ && echo done!

# 'clean' task
clean:
	@echo -n cleaning...
	@rm -rf $(PROGRAM)
	@rm -rf $(TEST)
	@rm -rf $(HEADER)
	@echo done!
	@echo -n creating target directory ...
	@mkdir -p target && echo done!

# 'print' task; meant for debugging/understanding
print:
	@echo BUILDDIR: $(BUILDDIR)
	@echo PROGRAM: $(PROGRAM)
	@echo MAINSRC: $(MAINSRC)
	@echo LIBSRC: $(LIBSRC)
	@echo TEST: $(TEST)
	@echo TESTSRC: $(TESTSRC)
