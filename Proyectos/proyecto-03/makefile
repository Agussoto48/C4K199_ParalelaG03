CXX = g++
CXXFLAGS = -Wall -std=c++17 -fopenmp -I../../EntregasSemanales/shared_openMP -Iinclude/
default: build

BIN_DIR = bin

#Archivos fuentes
SRC_MEDIOS = src/*.cpp
SRC_MP = ../../EntregasSemanales/shared_openMP/*.cpp

#Ejecutables
EXE = $(BIN_DIR)/medios


build: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_MEDIOS) $(SRC_MP) -o $(EXE)

buildFilo: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_MEDIOS) $(SRC_MP) -o $(EXE)

run:
	@./$(EXE) $(ARGS)


#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@rm -rf $(BIN_DIR)