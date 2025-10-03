CXX = g++
CXXFLAGS = -g -std=c++20

TARGET = rb
SOURCES = rb.cpp main.cpp

all: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

test:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) 
	./$(TARGET) $(n) > output.txt
	python3 plot.py $(n)

clean:
	rm -f $(TARGET) output.txt