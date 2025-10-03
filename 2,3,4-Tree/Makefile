# Makefile for TTF Lab
SHELL := /bin/bash

# Compiler and flags - Modern C++20
CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++20

# Executable name
EXEC = two_three_four

# Source files
SOURCES = $(EXEC).cpp main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Test configuration
NUM_TEST_CASES = 9
TCDIR = tests

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

# Run all test cases
runtests: $(EXEC)
	@echo -e "Running Test Cases"
	@for i in `seq 1 $(NUM_TEST_CASES)`; do \
		echo -e "\n\033[0;36mTestcase $$i\033[0m"; \
		echo -e "./$(EXEC) < $(TCDIR)/test$$i/input.txt"; \
		./$(EXEC) < $(TCDIR)/test$$i/input.txt > output.txt; \
		if diff -Bw output.txt $(TCDIR)/test$$i/output.txt > /dev/null; then \
			echo -e "\033[0;32mPASSED\033[0m"; \
		else \
			echo -e "diff -Bw output.txt $(TCDIR)/test$$i/output.txt";\
			diff -Bw output.txt $(TCDIR)/test$$i/output.txt; \
			echo -e "\033[0;31mFAILED\033[0m"; \
		fi \
	done
	@rm -f output.txt

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(EXEC) output.txt
	find . -type f -name '*~' -delete


.PHONY: all build runtests clean
