CC = g++
CXXFLAGS= -Wall -pedantic -g -ggdb

main : folder obj/main.o obj/bridge.o obj/BandMatrix.o
	$(CC) $(CXXFLAGS) -o bin/main obj/main.o obj/bridge.o obj/BandMatrix.o

folder:
	mkdir -p ./bin
	mkdir -p ./obj

obj/main.o : src/main.cpp
	$(CC) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/bridge.o : src/bridge.cpp
	$(CC) $(CXXFLAGS) -c src/bridge.cpp -o obj/bridge.o

obj/BandMatrix.o : src/BandMatrix.cpp
	$(CC) $(CXXFLAGS) -c src/BandMatrix.cpp -o obj/BandMatrix.o

clean:
	rm -f -r bin obj

debug:
	$(CC) -c -Wall src/main.cpp -o obj/main.o 
	$(CC) -c -Wall src/bridge.cpp -o obj/bridge.o
	$(CC) -c -Wall src/BandMatrix.cpp -o obj/BandMatrix.o
