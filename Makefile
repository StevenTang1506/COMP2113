# Variable for the C++ compiler
CXX = g++

# Variable for the C++ compiler flags
CXXFLAGS = -std=c++11 -Wall

# Variable for the output executable
TARGET = game

# Variable for the source files
SOURCES = main.cpp Game.cpp

# Variable for the object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default rule
all: $(TARGET)

# Rule to link the object files and create the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to generate object files from source files
%.o: %.cpp Game.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony target to prevent problems with files of the same name as the rules
.PHONY: all clean