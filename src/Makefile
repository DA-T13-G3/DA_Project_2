# Variables
CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
TARGET   = Tool

# List of all source files
SRCS     = main.cpp \
           allocationTool.cpp \
           parser.cpp \
           createGraph.cpp \
           dataStructs.cpp \
           buildResult.cpp \
           spilling.cpp \
           splitting.cpp \
           writeAssignments.cpp \
           menu.cpp

# Convert source file names (.cpp) into object file names (.o)
OBJS     = $(SRCS:.cpp=.o)

# Default rule (runs when you just type 'make')
all: $(TARGET)

# Rule to link the object files and create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile each .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove compiled files and start fresh
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to prevent conflicts with files named 'all' or 'clean'
.PHONY: all clean