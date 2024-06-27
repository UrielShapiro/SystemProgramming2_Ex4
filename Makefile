CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wno-comment
GUIFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
HEADRS = $(wildcard *.hpp)	
# HEADRS := $(filter-out Complex.hpp , $(HEADRS))

Test = Test

demo = Demo
EXE = tree

all: $(EXE) $(Test)

$(EXE): $(demo).cpp $(HEADRS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GUIFLAGS)

# $(Complex).o: $(Complex).cpp $(Complex).hpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@ 

$(Test): $(Test).cpp $(HEADRS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

clean:
	rm -f *.o $(EXE) $(Test)

.PHONY: all clean


