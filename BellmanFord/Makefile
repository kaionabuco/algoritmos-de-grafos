CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=bellman-ford

all: $(TARGET)

$(TARGET): bellman-ford.cpp
	$(CXX) $(CXXFLAGS) bellman-ford.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)