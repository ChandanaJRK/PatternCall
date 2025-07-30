# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++17 -pthread

# Output binary name
TARGET = main
TEST_TARGET = patternCallManager_test

# Source files
SRCS = patternMain.cpp patternCallManager.cpp
TEST_SRCS = patternCallManager_test.cpp patternCallManager.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Link object files into test executable with gtest libraries
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgtest -lgtest_main -pthread

# Compile each .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile .cpp to .o for test (same rule will apply)
# No change needed

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)