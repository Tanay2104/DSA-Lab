# Makefile
SHELL := /bin/bash

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -Wall -Wextra -std=c++20

# Executable
EXEC = dictionary

# Source files
SOURCES = dictionary.cpp main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Number of Test Cases
NUM_TEST_CASES = 7

# Testcase Files
TCDIR = tests


# Default target build exec
all: build runtests

# Build target
build: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp dictionary.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run test cases (mode 3 for test handler)
runtests: $(EXEC)
	@echo -e "Running Test Cases"
	@for i in `seq 1 $(NUM_TEST_CASES)`; do \
		echo -e "\033[0;36m\nTestcase $$i\033[0m"; \
		./$(EXEC) 3 < $(TCDIR)/test$$i/input.txt > output.txt; \
		if diff -Bw output.txt $(TCDIR)/test$$i/output.txt > /dev/null; then \
			echo -e "\033[0;32mPASSED\033[0m"; \
		else \
			echo -e "diff -Bw output.txt $(TCDIR)/test$$i/output.txt"; \
			diff -Bw output.txt $(TCDIR)/test$$i/output.txt; \
			echo -e "\033[0;31mFAILED\033[0m"; \
		fi \
	done
	@rm -f output.txt

# Random mode (mode 1)
random: $(EXEC)
	python3 sampler.py > sample.txt
	./$(EXEC) 1 > results.txt
	python3 plot.py

# English words mode (mode 2)
english: $(EXEC)
	./$(EXEC) 2 > results.txt
	python3 plot.py

# Clean up object files and executables
clean:
	rm -f $(OBJECTS) $(EXEC) sample.txt results.txt Hash.png *.o
	find . -type f -name '*~' -exec rm {} +

.PHONY: all build runtests random english clean
