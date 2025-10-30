CXX = g++
CXXFLAGS = -Wall -std=c++17 -I../../EntregasSemanales/shared -Iinclude/

default: build

BIN_DIR = bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


SRC_SHARED = ../../EntregasSemanales/shared_pthreads/*.cpp 

SRC = src/*.cpp
EXE = $(BIN_DIR)/contar

build: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) $(SRC_SHARED) -o $(EXE)


run:
	./$(EXE) $(ARGS)

clean:
	@rm -rf $(BIN_DIR)

