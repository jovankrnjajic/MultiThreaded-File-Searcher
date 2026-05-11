TARGET = build/searcher

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -lpthread

SRC = $(wildcard src/*.cpp)

all: create_dir
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

create_dir:
	mkdir -p build

clean:
	rm -rf build/*