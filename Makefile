CXX = g++
CXXFLAGS = -Wall -std=c++11
CXXDEBUGFLAGS = -ggdb -fsanitize=address

SRC     := src
INCLUDE := include
LIB     := lib
LIBRARIES :=
EXECUTABLE := encoder
OUTPUTDIR := output

.PHONY: all run debug clean fresh test

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)/*.cpp
	@echo "🔧 Building..."
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $^ -o $@

run: clean all
	@clear
	@echo "🚀 Executing..."
	@./$(EXECUTABLE)

test:

debug: CXXFLAGS += $(CXXDEBUGFLAGS)
debug: fresh all
	@echo "🔍 Debug build complete!"

clean:
	@echo "🧹 Clearing..."
	-rm -f $(EXECUTABLE)
	-rm -rf $(OUTPUTDIR)/*

