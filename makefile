all: main rcmatrix

main: main.cpp rcmatrix.cpp
	rm -f -- rcmatrix *.o
	g++ -Wall -pedantic -o main.o -c main.cpp
	g++ -Wall -pedantic -o rcmatrix.o -c rcmatrix.cpp
	g++ -o rcmatrix main.o rcmatrix.o

.PHONY: clean

clean:
	rm -f -- rcmatrix *.o

