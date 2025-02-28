CXX = g++
CXXFLAGS = -Wall -std=c++11
CXXDEBUGFLAGS = -ggdb -fsanitize=address 

SRC     := src
INCLUDE := include
LIB     := lib
LIBRARIES :=
EXECUTABLE := main

.PHONY: all run debug clean fresh test

all: $(SRC)/$(EXECUTABLE)

$(SRC)/$(EXECUTABLE): $(SRC)/*.cpp
	@echo "🔧 Building..."
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $^ -o $@

run: clean all
	@clear
	@echo "🚀 Executing..."
	@./$(SRC)/$(EXECUTABLE)

test:

debug: CXXFLAGS += $(CXXDEBUGFLAGS)
debug: fresh all
	@echo "🔍 Debug build complete!"

clean:
	@echo "🧹 Clearing..."
	-rm -f $(SRC)/$(EXECUTABLE)
