# Makefile for trie program
SHELL := /bin/bash

# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++20 -Wno-unused-parameter -Werror

# Executable name
EXEC = all-topological

# Source files
SOURCES = main.cpp all-topological.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Test configuration
TCDIR = tests
NUM_TEST_CASES = 11

# Default target
all: build runtests

# Build target
build: $(EXEC)

# Link executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile object files
%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run all tests
runtests: $(EXEC)
	@echo -e "Running Test Cases"
	@for i in `seq 1 $(NUM_TEST_CASES)`; do \
		echo -e "\n\033[0;36mTestcase $$i\033[0m"; \
		./$(EXEC) < $(TCDIR)/test$$i/input.txt > output.txt; \
		if diff -Bw output.txt $(TCDIR)/test$$i/output.txt > /dev/null; then \
			echo -e "\033[0;32mPASSED\033[0m"; \
		else \
			echo -e "diff -Bw"; \
			diff -Bw output.txt $(TCDIR)/test$$i/output.txt; \
			echo -e "\033[0;31mFAILED\033[0m"; \
		fi; \
	done
	@rm -f output.txt

# Clean target
clean:
	rm -f $(EXEC) $(OBJECTS) output.txt g.dot

.PHONY: all build runtests clean
