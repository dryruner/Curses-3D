# 
# 
# c3d (C) lf94/ircsurfer33 (ircsurfer33(AT)gmail(dot)com)
# 
# 
VERSION=0.1.0

CC=gcc
CFLAGS=-Wall -O3

LINKER=-lcurses -lm

libc3d.so.$(VERSION) : c3d.o
	$(CC) -shared -Wl c3d.o -o libc3d.so.$(VERSION) $(LINKER)
	
c3d.o : c3d.c c3d.h
	$(CC) $(CFLAGS) c3d.c -c
	
	
clean:
	rm -f c3d.o libc3d.so.$(VERSION)