.PHONY: all buildMult buildPi buildSuma runMult runPi runSuma clean default

# Si se pone solo make, compila todos los ejecutables
default: buildMult buildPi buildSuma

CXX = g++
CXXFLAGS = -Wall -std=c++17

BIN_DIR = bin

SRC_MULT = matrices/multMatrices.cpp
SRC_PI   = pi/PiPorSeries.cpp
SRC_SUMA = suma/sumaUno.cpp

EXE_MULT = $(BIN_DIR)/multMatrices
EXE_PI   = $(BIN_DIR)/PiPorSeries
EXE_SUMA = $(BIN_DIR)/sumaUno

# Crear carpeta bin si no existe
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Compilar cada programa
buildMult: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_MULT) -o $(EXE_MULT)

buildPi: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_PI) -o $(EXE_PI)

buildSuma: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_SUMA) -o $(EXE_SUMA)

# Ejecutar cada programa
runMult:
	@./$(EXE_MULT)

runPi:
	@./$(EXE_PI) $(ARGS)

runSuma:
	@./$(EXE_SUMA) $(ARGS)

# Limpiar ejecutables
clean:
	@rm -f $(EXE_MULT) $(EXE_PI) $(EXE_SUMA)

