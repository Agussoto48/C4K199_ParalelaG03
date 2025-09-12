CXX = g++
CXXFLAGS = -Wall -std=c++17 -I../shared
default: buildAguaSS buildAguaB buildFiloECCI

BIN_DIR = bin

#Shared
SRC_SHARED = ../shared/*.cpp

#Archivos fuentes del agua
SRC_AGUA_SEM_SHM = problemaAgua/aguaSemShm.cpp
SRC_AGUA_BUZON = problemaAgua/aguaBuzon.cpp

SRC_FILO_ECCI = FilosofosECCI/FilosofosSemShm.cpp

#Ejecutables del agua
EXE_AGUA_SEM_SHM = $(BIN_DIR)/aguaSemShm
EXE_AGUA_BUZON = $(BIN_DIR)/aguaBuzon

EXE_FILOCCI = $(BIN_DIR)/filo

#Compilacion y ejecucion del problema del agua
buildAguaSS: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_AGUA_SEM_SHM) $(SRC_SHARED) -o $(EXE_AGUA_SEM_SHM)

buildAguaB: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_AGUA_BUZON) $(SRC_SHARED) -o $(EXE_AGUA_BUZON)

buildFiloECCI:
	$(CXX) $(CXXFLAGS) $(SRC_FILO_ECCI) $(SRC_SHARED) -o $(EXE_FILOCCI)

runAguaSemShm:
	@./$(EXE_AGUA_SEM_SHM) $(ARGS)

runAguaBuzon:
	@./$(EXE_AGUA_BUZON) $(ARGS)

runFilo:
	@./$(EXE_FILOCCI)

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR)