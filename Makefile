SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
EXE := game.exe
CXX := clang++
CXXFLAGS := -Iinclude -g
LDFLAGS :=
LDLIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

build:
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC) $(LDLIBS)

	




