CC = gcc
LD = gcc
CFLAGS = -std=gnu99 -ggdb3 -Wall -fPIC
STATIC_DDS_LIB = libdds.a

all: dds.so

dds.so: dds.o util.o
	$(LD) -shared -o $@ $^ -ldds -lm

dds: dds.c util.c
	$(CC) $(CFLAGS) -c -o $@ $<

build_driver:
	$(CC) dds.c util.c -ldds -o dds_driver

clean:
	rm dds.o dds.so
