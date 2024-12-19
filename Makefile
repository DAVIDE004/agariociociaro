SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = gameciociaro

CXX = clang++
CPPFLAGS = -std=c++11 
LIBS = libraylib.a -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL


all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(LIBS) $(CPPFLAGS) $^ -o $@ 

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $^

clean:
	rm -rf $(OBJ) $(BIN)