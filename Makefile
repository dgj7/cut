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
HEADER   := src/version.h

# versioning
MAJOR    := 0
MINOR    := 0
PATCH    := 5
GITHASH  := $(shell git rev-parse HEAD)
VERSION  := $(MAJOR).$(MINOR).$(PATCH).$(GITHASH)

# tasks that aren't files
.PHONY: vh build test clean print

# 'build' task
build: $(PROGRAM)

# 'test' task
test: $(TEST)

# 'header' task
vh: $(HEADER)

# build and run the test program; exits if any tests fail
$(TEST): $(TESTSRC)
	@echo -n creating target directory ...
	@mkdir -p target && echo done!
	@echo -n compiling tests: $^ $@ ...
	@$(CC) $(CFLAGS) -o $@ $^ && echo done!
	@$(TEST)

# build the main program
$(PROGRAM): $(MAINSRC) $(HEADER)
	@echo -n creating target directory ...
	@mkdir -p target && echo done!
	@echo -n compiling main: $^ $@ ...
	@$(CC) $(CFLAGS) -o $@ $^ && echo done!

# create version header file
$(HEADER):
	@echo -n creating version header file ...
	@echo "#ifndef VERSION__HEADER__DG__H__" > $(HEADER)
	@echo "#define VERSION__HEADER__DG__H__" >> $(HEADER)
	@echo "" >> $(HEADER)
	@echo '#define VERSION "$(VERSION)"' >> $(HEADER)
	@echo "" >> $(HEADER)
	@echo "#endif" >> $(HEADER)
	@echo done!

# 'clean' task
clean:
	@echo -n cleaning...
	@rm -rf $(PROGRAM)
	@rm -rf $(TEST)
	@rm -rf $(HEADER)
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
	@echo GITHASH: [$(GITHASH)]
	@echo VERSION: [$(VERSION)]
