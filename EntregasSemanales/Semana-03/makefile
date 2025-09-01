CXX = g++
CXXFLAGS = -Wall -std=c++17

BIN_DIR = bin

#Archivos fuentes de enviarConclases/recibir
SRC_SND_CC = conClases/enviarConClases.cpp
SRC_RCV_CC = conClases/recibirConClases.cpp

#Archivos Fuentes de enviar/recibir sin clases
SRC_SND_SC = sinClases/enviarSinClases.cpp
SRC_RCV_SC = sinClases/recibirSinClases.cpp

#Archivos fuentes de los demas ejercios
SRC_PI = otrosEjercicios/PiPorSeries.cpp
SRC_SHM = otrosEjercicios/pruebaShM.cpp

#Achivo fuente de la biblioteca de semaforos (cpp)
SRC_SEM = shared/Semaforo.cpp

# Ejecutables
EXE_SND_CC = $(BIN_DIR)/enviarClase
EXE_RCV_CC = $(BIN_DIR)/recibirClase

EXE_SND_SC = $(BIN_DIR)/enviar
EXE_RCV_SC = $(BIN_DIR)/recibir

EXE_PI = $(BIN_DIR)/PiPorSeries $(ARGS)
EXE_SHM = $(BIN_DIR)/pruebaShM


# Regla por defecto
default: buildClase buildSinClase buildPi buildSHM

# Crear bin si no existe
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Builds y runs del ejercicio principal de los buzones
buildClase: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_SND_CC) -o $(EXE_SND_CC)
	$(CXX) $(CXXFLAGS) $(SRC_RCV_CC) -o $(EXE_RCV_CC)

buildSinClase: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_SND_SC) -o $(EXE_SND_SC)
	$(CXX) $(CXXFLAGS) $(SRC_RCV_SC) -o $(EXE_RCV_SC)

# Runs
runEC:
	@./$(EXE_SND_CC)

runRC:
	@./$(EXE_RCV_CC)

runE:
	@./$(EXE_SND_SC)

runR:
	@./$(EXE_RCV_SC)

#Builds y runs de los demas ejercicios
buildPi:
	$(CXX) $(CXXFLAGS) $(SRC_PI) -o $(EXE_PI)

buildSHM:
	$(CXX) $(CXXFLAGS) $(SRC_SHM) $(SRC_SEM) -o $(EXE_SHM)

runPi:
	@./$(EXE_PI)

runShm:
	@./$(EXE_SHM)

# Clean
clean:
	@rm -rf $(BIN_DIR)
