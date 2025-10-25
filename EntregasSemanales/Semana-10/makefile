CXX = g++
CXXFLAGS = -Wall -std=c++17 -fopenmp
default: buildAll

BIN_DIR = bin

#Archivos fuentes
SRC_MATRICES = openMP/matricesMP.cpp
SRC_SUMA = openMP/sumaUnoMP.cpp
SRC_PI = openMP/piPorSeriesMP.cpp

#Ejecutables
EXE_MATRICES = $(BIN_DIR)/matrices
EXE_SUMA = $(BIN_DIR)/suma
EXE_PI = $(BIN_DIR)/pi

buildMatrices: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_MATRICES) -o $(EXE_MATRICES)

buildSuma: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_SUMA) -o $(EXE_SUMA)

buildPi: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_PI) -o $(EXE_PI)

buildAll: buildMatrices buildSuma buildPi 

runMatrices:
	@./$(EXE_MATRICES)

runSuma:
	@./$(EXE_SUMA)

runPi:
	@./$(EXE_PI)

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR)