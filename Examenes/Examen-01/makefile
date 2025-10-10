CXX = g++
CXXFLAGS = -Wall -std=c++17 -I../../EntregasSemanales/shared -lpthread
default: buildA

BIN_DIR = bin

#Archivos fuentes
SRC_SHARED = ../../EntregasSemanales/shared/*.cpp
#SRC_SHARED_PTHREADS = ../../EntregasSemanales/shared_pthreads/*.cpp
SRC_A = EjercicioA/*.cpp
SRC_B = EjercicioB/*.cpp

#Ejecutables
EXE_A = $(BIN_DIR)/A
EXE_B = $(BIND_DIR)/ejerB

buildA: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_A) $(SRC_SHARED_PTHREADS) -o $(EXE_A)

runA:
	@./$(EXE_A)

buildB: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_B) $(SRC_SHARED) -o bin/B $(ARGS)

runB:
	@./bin/B

#Crea la carpeta bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR)