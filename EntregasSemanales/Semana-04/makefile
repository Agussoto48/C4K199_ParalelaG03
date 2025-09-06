CXX = g++
CXXFLAGS = -Wall -std=c++17 -I../shared
default: buildAgua

BIN_DIR = bin

#Shared
SRC_SHARED = ../shared/*.cpp

#Archivos fuentes del agua
SRC_AGUA_SEM_SHM = problemaAgua/aguaSemShm.cpp


#Ejecutables del agua
EXE_AGUA_SEM_SHM = $(BIN_DIR)/aguaSemShm

#Compilacion y ejecucion del problema del agua
buildAgua: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_AGUA_SEM_SHM) $(SRC_SHARED) -o $(EXE_AGUA_SEM_SHM)

runAguaSemShm:
	@./$(EXE_AGUA_SEM_SHM) $(ARGS)


#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR)