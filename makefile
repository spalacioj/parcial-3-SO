CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lsodium
TARGET = parcial3
OBJ = main.o LZ78Compressor.o chacha20Encryptor.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

main.o: main.cpp LZ78Compressor.h chacha20Encryptor.h
	$(CXX) $(CXXFLAGS) -c main.cpp

LZ78Compressor.o: LZ78Compressor.cpp LZ78Compressor.h
	$(CXX) $(CXXFLAGS) -c LZ78Compressor.cpp

chacha20Encryptor.o: chacha20Encryptor.cpp chacha20Encryptor.h
	$(CXX) $(CXXFLAGS) -c chacha20Encryptor.cpp

clean:
	rm -f $(TARGET) $(OBJ)

clean_files:
	rm -f *.enc *.lz78
