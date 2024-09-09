# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

# List of source files
SRCS := graph.cpp main.cpp

# List of object files (same as source files but with .o extension)
OBJS := $(SRCS:.cpp=.o)

# Output executable name
TARGET := test

# Default rule
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to avoid conflicts with files named 'all' or 'clean'
.PHONY: all clean

