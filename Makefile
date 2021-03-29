SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
EXE := a.exe
CXX := clang++
CXXFLAGS := -Iinclude -Wall -g
LDFLAGS := 
LDLIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(EXE)
	/c/"Program Files"/PowerShell/7-preview/pwsh -c "wt -d . cmd /k $(EXE)"




