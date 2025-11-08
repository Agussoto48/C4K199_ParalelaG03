CXX = g++
CXXFLAGS = -Wall -std=c++17 -fopenmp -Iinclude/
default: build

BIN_DIR = bin

#Archivos fuentes
SRC_MEDIOS = src/*.cpp

#Ejecutables
EXE = $(BIN_DIR)/medios


build: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_MEDIOS) -o $(EXE)

buildFilo: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_MEDIOS) -o $(EXE)

run:
	@./$(EXE) $(ARGS)


#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@rm -rf $(BIN_DIR)