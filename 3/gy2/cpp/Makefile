# 3. fejezet
# C++ 

CFLAGS = -Wall
prgs = rounder rounder2

all: $(prgs)

rounder.o: rounder.cpp
	g++ -fPIC -c rounder.cpp

librounder.so.1.0.1: rounder.o
	g++ -shared -Wl,-soname,librounder.so.1 -o librounder.so.1.0.1 rounder.o -lc
	ldconfig -n .
	ln -s librounder.so.1.0.1 librounder.so

rounder: roundermain.cpp rounder.h librounder.so.1.0.1
	g++ -o $@ $< -L. -lrounder -Wl,-rpath .

uprounder.o: uprounder.cpp
	g++ -fPIC -c uprounder.cpp

libuprounder.so.1.0.1: uprounder.o
	g++ -shared -Wl,-soname,libuprounder.so.1 -o libuprounder.so.1.0.1 uprounder.o -lc
	ldconfig -n .

rounder2: roundermain2.cpp rounder2.h libuprounder.so.1.0.1
	g++ -o $@ $< -L. -ldl

clean:
	rm -f $(prgs) *.o *.so*

.PHONY: clean
