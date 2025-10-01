CXX = g++
CXXFLAGS = -Wall -std=c++17 -I../../EntregasSemanales/shared

default: buildMonos buildPapa

BIN_DIR = bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


SRC_SHARED = ../../EntregasSemanales/shared/*.cpp 

SRC_MONOS = monos/*.cpp
EXE_MONOS = $(BIN_DIR)/monos

SRC_PAPAS = PapaCaliente/*.cpp
EXE_PAPAS = $(BIN_DIR)/papa

buildMonos: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_MONOS) $(SRC_SHARED) -o $(EXE_MONOS)

buildPapa: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_PAPAS) $(SRC_SHARED) -o $(EXE_PAPAS)
	
runMonos:
	./$(EXE_MONOS)

runPapas:
	./$(EXE_PAPAS)

clean:
	@rm -rf $(BIN_DIR)

