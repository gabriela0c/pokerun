CXX = g++
# -MMD -MP: gera dependencias de header (.d) para recompilar certo quando um .h muda
CXXFLAGS = -std=c++17 -Wall -I./include -I./sfml/include -MMD -MP
LDFLAGS = -L./sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -mconsole

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Fontes: raiz + 1 e 2 niveis de subpasta
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp)
# Objetos e dependencias achatados em obj/
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))
DEPS = $(OBJS:.o=.d)
# Onde o make procura os .cpp
VPATH = $(sort $(dir $(SRCS)))

TARGET = $(BIN_DIR)/jogo.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# inclui as dependencias geradas (ignora se ainda nao existirem)
-include $(DEPS)

# limpeza manual (opcional): mingw32-make clean
clean:
	-cmd /c "del /Q /F $(OBJ_DIR)\*.o $(OBJ_DIR)\*.d $(BIN_DIR)\*.exe"
