# LAB #3

### static library
lsd. Makefile libceilfunc.a

`gcc -o ceiling3 ceiling2.o libceilfunc.a`

de hogyan kene szebben?


`make ceiling3`

csak spec esetben kell statikusan linkelni, kulonben minden esetben minden fuggveny a diszken is kulon helyet foglal

`nm libceilfunc.a`

bele tudunk nezni a libraryba

### statikusan betoltott

```
$ ldd round
  linux-vdso.so.1 =>  (0x00007ffdc987b000)
  libround.so.1 => not found
  libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ffb1a2ca000)
  /lib64/ld-linux-x86-64.so.2 (0x00007ffb1a68f000)
$ export LD_LIBRARY_PATH=.
$ ldd round
  linux-vdso.so.1 =>  (0x00007fff2a3c9000)
  libround.so.1 => ./libround.so.1 (0x00007f2823c59000)
  libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f2823894000)
  /lib64/ld-linux-x86-64.so.2 (0x00007f2823e5b000)
```
azert nem talalta, mert nincs rajta a library path-on

igazabol a `/etc/ld.so.conf` ban kene legyen

es utana `ldconfig`

### dinamikusan betoltott
