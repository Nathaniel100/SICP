CC = g++
CFLAGS = -std=c++11 -c -g -Wall -O2
TARGET= fact sqrt pascal expt fib count_change gcd prime \
		sum accumulate half_interval_method fixed_point
SOURCES= fact.cpp sqrt.cpp pascal.cpp expt.cpp fib.cpp count_change.cpp gcd.cpp prime.cpp \
		 sum.cpp accumulate.cpp half_interval_method.cpp fixed_point.cpp
OBJECTS= $(SOURCES:.cpp=.o)

all: $(TARGET)
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

fact: fact.o
sqrt: sqrt.o
pascal: pascal.o
expt: expt.o
fib: fib.o
count_change: count_change.o
gcd: gcd.o
prime: prime.o
sum: sum.o
accumulate: accumulate.o
half_interval_method: half_interval_method.o
fixed_point: fixed_point.o

clean:
	$(RM) *.o *~ $(TARGET)

