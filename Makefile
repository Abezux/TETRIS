CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Ivendor/raylib/include
LDFLAGS = -Lvendor/raylib/lib -lraylib -L/usr/lib/x86_64-linux-gnu -l:libGL.so.1 -lm -lpthread -ldl -lrt -lX11

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
