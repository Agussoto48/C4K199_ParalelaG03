CXX_MPI     := mpicxx
CXX_OMP     := g++
CXXFLAGS_MPI := -Wall -std=c++17 -Iinclude
CXXFLAGS_OMP := -Wall -std=c++17 -fopenmp -Iinclude

default: build

BIN_DIR := bin

#Archivos fuentes
SRC_MPI := MPI/*.cpp
SRC_OMP := OpenMP/*.cpp

#Ejecutables
EXE_MPI := $(BIN_DIR)/ej_mpi
EXE_OMP := $(BIN_DIR)/ej_omp

#Parámetros MPI
NP ?= 1 
ARGS ?=

buildMPI: | $(BIN_DIR)
	$(CXX_MPI) $(CXXFLAGS_MPI) $(SRC_MPI) -o $(EXE_MPI)

buildOPM: | $(BIN_DIR)
	$(CXX_OMP) $(CXXFLAGS_OMP) $(SRC_OMP) -o $(EXE_OMP)

build: buildMPI buildOPM

runMPI:
	mpirun --oversubscribe -np $(NP) ./$(EXE_MPI) $(ARGS)

runOPM:
	@./$(EXE_OMP) $(ARGS)

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@rm -rf $(BIN_DIR)