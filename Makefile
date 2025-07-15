CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = src/main.cpp src/compressor.cpp src/utils.cpp
OUT = bin/compressor

all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	./$(OUT)

clean:
	rm -rf bin data/compressed.bin restored/restored.csv
