CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wno-comment
HEADRS = $(wildcard *.hpp)	

demo = Demo
EXE = tree

all: $(EXE)

$(EXE): $(demo).cpp $(HEADRS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o $(EXE)

.PHONY: all clean


