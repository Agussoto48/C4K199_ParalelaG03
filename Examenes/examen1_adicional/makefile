CXX = g++
CXXFLAGS = -Wall -std=c++17 -I../../EntregasSemanales/shared -lpthread
default: buildA buildB

BIN_DIR = bin

SRC_SHARED_PTHREADS = ../../EntregasSemanales/shared_pthreads/*.cpp
SRC_A = serial.cpp
SRC_B = paralela.cpp

#Ejecutables
EXE_A = $(BIN_DIR)/A
EXE_B = $(BIN_DIR)/B

buildA: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_A) $(SRC_SHARED_PTHREADS) -o $(EXE_A)

runA:
	@./$(EXE_A)

buildB: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_B) $(SRC_SHARED_PTHREADS) -o $(EXE_B)

runB:
	@./$(EXE_B)

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR)