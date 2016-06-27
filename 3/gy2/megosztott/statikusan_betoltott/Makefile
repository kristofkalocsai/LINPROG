# 3. fejezet
# Megosztott programkönyvtárak

CFLAGS = -Wall
prgs = round

all: $(prgs)

round.o: round.c
	gcc -fPIC -c -Wall round.c
	# PositionIndepentCode (-fPIC) megosztott memoriateruletre kerul a lib

libround.so.1.0.1: round.o
	gcc -shared -Wl,-soname,libround.so.1 -o libround.so.1.0.1 round.o -lc
	# megosztott, -Wl: az ezutani parameterek a linkernek szolnak
	# 3 db verzioszam: main.sub.release
	# main: ha valtozik, valtozott az interface
	# sub: implementacio valtozott, interface marad
	# release: bugfixes
	# soname: a rsz igy keresi linkeleskor
	ldconfig -n .
	# megcsinalja magatol az soname-linkeket
	ln -s libround.so.1.0.1 libround.so
	# 

round: roundmain.o round.h libround.so.1.0.1
	gcc -o $@ $< -L. -lround

clean:
	rm -f $(prgs) *.o *.so*

.PHONY: all clean
