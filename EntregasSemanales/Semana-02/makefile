.PHONY: default all buildPi buildSuma buildSem runPi runSuma runSem clean

CXX = g++
CXXFLAGS = -Wall -std=c++17

BIN_DIR = bin

# Archivos fuente
SRC_PI = Pi/PiPorSeries.cpp
SRC_SUMA = SumaUno/sumaUno.cpp
SRC_SEM = PruebaSemaforos/pruebaSem.cpp PruebaSemaforos/Semaforo.cpp

# Ejecutables
EXE_PI = $(BIN_DIR)/pi
EXE_SUMA = $(BIN_DIR)/suma
EXE_SEM = $(BIN_DIR)/sem

# Regla por defecto
default: buildPi buildSuma buildSem

# Crear bin si no existe
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Builds
buildPi: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_PI) -o $(EXE_PI)

buildSuma: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_SUMA) -o $(EXE_SUMA)

buildSem: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_SEM) -o $(EXE_SEM)

# Runs
runPi:
	@./$(EXE_PI) $(ARGS)

runSuma:
	@./$(EXE_SUMA) $(ARGS)

runSem:
	@./$(EXE_SEM)

# Clean
clean:
	@rm -rf $(BIN_DIR)

