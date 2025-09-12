CXX = g++
CXXFLAGS = -Wall -std=c++17 -I../shared
default: buildFilo

BIN_DIR = bin

#Shared
SRC_SHARED = ../shared/*.cpp

#Archivos fuentes
SRC_CONDITION = Condition/condition.cpp
SRC_MESA = Mesa/Mesa.cpp
SRC_FILO = Filosofos/Filosofos.cpp

#Ejecutables
EXE_MESA = $(BIN_DIR)/mesa
EXE_FILO = $(BIN_DIR)/filo

buildFilo: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILO) $(SRC_MESA) $(SRC_CONDITION) $(SRC_SHARED) -o $(EXE_FILO)


runFilo:
	@./$(EXE_FILO)

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR)