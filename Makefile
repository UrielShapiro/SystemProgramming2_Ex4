 # Name: Uriel Shapiro
 # ID: 9745

CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wno-comment
GUIFLAGS = -lsfml-graphics -lsfml-window -lsfml-system 		# Flags for the GUI
HEADRS = $(wildcard *.hpp)	# all .hpp files in the current directory

Test = Test
demo = Demo
EXE = tree

all: $(EXE) $(Test)

$(EXE): $(demo).cpp $(HEADRS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GUIFLAGS)

$(Test): $(Test).cpp $(HEADRS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

clean:
	rm -f *.o $(EXE) $(Test)

.PHONY: all clean


