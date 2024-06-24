CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wno-comment
HEADRS = $(wildcard *.hpp)	
HEADRS := $(filter-out Complex.hpp , $(HEADRS))

Complex = Complex

demo = Demo
EXE = tree

all: $(EXE)

$(EXE): $(demo).cpp $(Complex).o $(HEADRS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(Complex).o: $(Complex).cpp $(Complex).hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	rm -f *.o $(EXE) $(Complex).o

.PHONY: all clean


