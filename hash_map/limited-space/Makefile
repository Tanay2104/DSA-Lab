# Makefile for Dictionary + LimitedDictionary tests
SHELL := /bin/bash

# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++20 -Wno-unused-parameter -Wno-unused-private-field -Werror

# Executable name
EXEC = limited-space

# Source files
SOURCES = main.cpp dictionary.cpp limitedDictionary.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Test configuration
TCDIR = tests
NUM_TEST_CASES = 8   # update if you add more test folders (test1...testN)

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
			echo -e "diff -Bw output.txt $(TCDIR)/test$$i/output.txt"; \
			diff -Bw output.txt $(TCDIR)/test$$i/output.txt; \
			echo -e "\033[0;31mFAILED\033[0m"; \
		fi; \
	done
	@rm -f output.txt

# Clean target
clean:
	rm -f $(EXEC) $(OBJECTS) output.txt

.PHONY: all build runtests clean

