CXX = g++
CXXFLAGS = -std=c++20

TARGET = kmp
SOURCES = kmp.cpp main.cpp

all: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

test:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	./$(TARGET) < inputs/input1.txt > output1.txt
	diff outputs/output1.txt output1.txt

clean:
	rm -f $(TARGET) output1.txt output0.txt