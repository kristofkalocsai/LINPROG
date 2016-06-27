# 3. fejezet
# Statikus programkönyvtárak

CFLAGS = -Wall
prgs = ceiling1 ceiling2 ceiling3 round

all: $(prgs)

ceiling2: ceiling2.o ceilfunc.o

libceilfunc.a: ceilfunc.o
	ar rcs $@ $<
# targykodu allobanybol libet csinal

ceiling3: ceiling2.o libceilfunc.a
	gcc -o $@ $< -L. -lceilfunc

libround.a: round.o
	ar rcs $@ $<

round: roundmain.o round.h libround.a
	gcc -o $@ $< -L. -lround

clean:
	rm -f $(prgs) *.o *.a

.PHONY: all clean
