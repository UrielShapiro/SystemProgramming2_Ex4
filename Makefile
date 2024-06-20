CXX = g++
CXXFLAGS = -Wall -Wextra -g
HEADRS = $(wildcard *.hpp)	

EXE = Demo

all: $(EXE)

$(EXE): $(EXE).cpp $(HEADRS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o $(EXE)

.PHONY: all clean


