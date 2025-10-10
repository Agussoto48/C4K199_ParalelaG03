CXX = g++
CXXFLAGS = -Wall -std=c++17 -I../shared -lpthread
default: buildMatrices

BIN_DIR = bin

#Archivos fuentes
SRC_SHARED_PTHREADS = ../shared_pthreads/*.cpp
SRC_MATRICES = matrices/*.cpp
SRC_PROCESS = process/*.cpp

#Ejecutables
EXE_MATRICES = $(BIN_DIR)/matrices
EXE_PROCESS = $(BIND_DIR)/process

buildMatrices: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_MATRICES) $(SRC_SHARED_PTHREADS) -o $(EXE_MATRICES)

runMatrices:
	@./$(EXE_MATRICES)

buildProcess:
	$(CXX) $(CXXFLAGS) $(SRC_PROCESS) -o $(EXE_PROCESS)

runProcess:
	./$(EXE_PROCESS)

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR)