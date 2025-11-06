CXX = g++
CXXFLAGS = -Wall -std=c++17 -fopenmp -Iadaptaciones_MP
default: buildAll

BIN_DIR = bin

#Archivos fuentes
SRC_PAPA = Papa/papa.cpp
SRC_FILO = Filosofos/filo.cpp
SRC_MP = adaptaciones_MP/*.cpp

#Ejecutables
EXE_PAPA = $(BIN_DIR)/papa
EXE_FILO = $(BIN_DIR)/filo


buildPapa: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_PAPA) $(SRC_MP) -o $(EXE_PAPA)

buildFilo: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILO) $(SRC_MP) -o $(EXE_FILO)

buildAll: buildPapa buildFilo

runPapa:
	@./$(EXE_PAPA) $(ARGS)

runFilo:
	@./$(EXE_FILO)

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR)