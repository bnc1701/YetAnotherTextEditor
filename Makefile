CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Iinclude
SRC = src/main.cpp src/editor.cpp src/buffer.cpp
TARGET = yetanothertexteditor

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
