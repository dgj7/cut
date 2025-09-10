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

# versioning
MAJOR    := 0
MINOR    := 0
PATCH    := 2
GITHASH  := $(shell git rev-parse HEAD)		# short: git rev-parse --short HEAD
VERSION  := $(MAJOR).$(MINOR).$(PATCH)

# tasks that aren't files
.PHONY: build test clean print

# 'build' task
build: $(PROGRAM)

# 'test' task
test: $(TEST)

# build and run the test program; exits if any tests fail
$(TEST): $(TESTSRC)
	@echo -n compiling tests: $^ $@ ...
	@$(CC) $(CFLAGS) -o $@ $^ && echo done!
	@$(TEST)

# build the main program
$(PROGRAM): $(MAINSRC)
	@echo -n compiling main: $^ $@ ...
	@$(CC) $(CFLAGS) -o $@ $^ && echo done!

# 'clean' task
clean:
	@echo -n cleaning...
	@rm -rf $(PROGRAM)
	@rm -rf $(TEST)
	@echo done!

# 'print' task; meant for debugging/understanding
print:
	@echo BUILDDIR: $(BUILDDIR)
	@echo PROGRAM: $(PROGRAM)
	@echo MAINSRC: $(MAINSRC)
	@echo LIBSRC: $(LIBSRC)
	@echo TEST: $(TEST)
	@echo TESTSRC: $(TESTSRC)
	@echo MAJOR: $(MAJOR)
	@echo MINOR: $(MINOR)
	@echo PATCH: $(PATCH)
	@echo GITHASH: $(GITHASH)
	@echo VERSION: $(VERSION)
