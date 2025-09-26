CXX = g++
CXXFLAGS = -Wall -std=c++17 -I../shared
default: buildFilo

BIN_DIR = bin

#Archivos fuentes
SRC_ADAPTACIONES = adaptaciones_pthreads/*.cpp
SRC_FILO = Filosofos/filosofos.cpp

#Ejecutables
EXE_FILO = $(BIN_DIR)/filo

buildFilo: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILO) $(SRC_ADAPTACIONES) -o $(EXE_FILO)


runFilo:
	@./$(EXE_FILO)

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR)