CC = gcc
LD = gcc
CPPFLAGS = -I/Users/scedarbaum/dev/dds.el/dds/include
CFLAGS = -std=gnu99 -ggdb3 -Wall -fPIC $(CPPFLAGS)
STATIC_DDS_LIB = libdds.a

all: dds.so

dds.so: dds.o util.o
	$(LD) -shared -o $@ $^ -L/usr/local/lib -ldds -lm

dds: dds.c util.c
	$(CC) $(CFLAGS) -c -o $@ $<

build_driver:
	$(CC) dds.c util.c -L/usr/local/lib -ldds -o dds_driver

clean:
	rm dds.o dds.so
