CXX = g++
CXXFLAGS = -std=c++11 `pkg-config --cflags gtk+-3.0` -Iinclude
LDFLAGS = `pkg-config --libs gtk+-3.0`

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/commands.cpp $(SRC_DIR)/gui.cpp
TARGET = $(BUILD_DIR)/BroBash

all: build_dir $(TARGET)

build_dir:
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)
