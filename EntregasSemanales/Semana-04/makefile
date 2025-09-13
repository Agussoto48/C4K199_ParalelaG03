CXX = g++
CXXFLAGS = -Wall -std=c++17 -I../shared
default: buildAguaSS buildAguaB buildFilo

BIN_DIR = bin

#Shared
SRC_SHARED = ../shared/*.cpp

#Archivos fuentes del agua
SRC_AGUA_SEM_SHM = problemaAgua/aguaSemShm.cpp
SRC_AGUA_BUZON = problemaAgua/aguaBuzon.cpp

SRC_FILO_NGC = FilosofosECCI/Filosofos.cpp

#Ejecutables del agua
EXE_AGUA_SEM_SHM = $(BIN_DIR)/aguaSemShm
EXE_AGUA_BUZON = $(BIN_DIR)/aguaBuzon

EXE_FILO = $(BIN_DIR)/Filo

#Compilacion y ejecucion del problema del agua
buildAguaSS: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_AGUA_SEM_SHM) $(SRC_SHARED) -o $(EXE_AGUA_SEM_SHM)

buildAguaB: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_AGUA_BUZON) $(SRC_SHARED) -o $(EXE_AGUA_BUZON)

buildFilo: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILO_NGC) $(SRC_SHARED) -lncurses -o $(EXE_FILO)

runAguaSemShm:
	@./$(EXE_AGUA_SEM_SHM) $(ARGS)

runAguaBuzon:
	@./$(EXE_AGUA_BUZON) $(ARGS)

runFilo:
	@./$(EXE_FILO)

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR)