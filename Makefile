output: computeBrick.o
	g++ -std=c++11 computeBrick.o  -o output
	./output -h 10 -w 32

computeBrick.o: computeBrick.cpp
	g++ -std=c++11 -c computeBrick.cpp

clean:
	rm -f 	computeBrick.o \
		output
