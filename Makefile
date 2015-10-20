all: fact fib sqrt count_change
CPP_FLAGS= -std=c++11 -O2
fact: fact.cpp
	g++ fact.cpp -o fact $(CPP_FLAGS)
fib: fib.cpp
	g++ fib.cpp -o fib $(CPP_FLAGS)
sqrt: sqrt.cpp
	g++ sqrt.cpp -o sqrt $(CPP_FLAGS)
count_change: count_change.cpp
	g++ count_change.cpp -o count_change $(CPP_FLAGS)
clean:
	rm fact fib sqrt count_change *.o

