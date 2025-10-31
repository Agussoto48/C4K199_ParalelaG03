CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude/

default: build

BIN_DIR = bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


SRC_SHARED = ../../EntregasSemanales/shared_pthreads/*.cpp 

SRC = src/*.cpp
EXE = $(BIN_DIR)/contar

build: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXE)


run:
	@./$(EXE) $(ARGS)

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE) $(ARGS)

clean:
	@rm -rf $(BIN_DIR)

