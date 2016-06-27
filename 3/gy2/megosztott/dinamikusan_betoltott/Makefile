# 3. fejezet
# Dinamikusan betöltött programkönyvtárak

CFLAGS = -Wall
prgs = dynamic_roundmain_bad dynamic_roundmain
libs = libround.so.1.0.1

all: $(prgs) $(libs)

round.o: round.c
	gcc -fPIC -c -Wall round.c

libround.so.1.0.1: round.o
	gcc -shared -Wl,-soname,libround.so.1 -o libround.so.1.0.1 round.o -lc
	ldconfig -n .

dynamic_roundmain_bad: dynamic_roundmain.o round.h
	gcc -o $@ $< -ldl

dynamic_roundmain: dynamic_roundmain.o round.h
	gcc -o $@ $< -ldl -rdynamic

clean:
	rm -f $(prgs) *.o *.so*

.PHONY: all clean
