CXX = g++
CXXFLAGS = -g -Wall -O2

TARGET = blk_io

all: $(TARGET).out

%.out: %.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET).out

clean:
	rm -f $(TARGET).out
