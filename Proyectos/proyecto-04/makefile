CXX = mpicxx
CXXFLAGS = -Wall -std=c++17 -Iinclude/
default: build

BIN_DIR = bin

#Archivos fuentes
SRC = src/*.cpp

#Ejecutables
EXE = $(BIN_DIR)/medios

#Parámetros MPI
NP ?= $(shell nproc)   
ARGS ?=

build: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXE)

run:
	mpirun --oversubscribe -np $(NP) ./$(EXE) $(ARGS)

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@rm -rf $(BIN_DIR)