CXX = g++
CXXFLAGS = -std=c++17 `pkg-config --cflags gtk+-3.0` -Iinclude
LDFLAGS = `pkg-config --libs gtk+-3.0` -lstdc++fs  # Link filesystem library

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/commands.cpp $(SRC_DIR)/gui.cpp $(SRC_DIR)/linkedlist.cpp $(SRC_DIR)/hashtable.cpp $(SRC_DIR)/datastructure.cpp
TARGET = $(BUILD_DIR)/BroBash

all: build_dir $(TARGET)

build_dir:
	# Ensure this line starts with a tab
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SRCS)
	# Ensure this line starts with a tab
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	# Ensure this line starts with a tab
	rm -rf $(BUILD_DIR)
