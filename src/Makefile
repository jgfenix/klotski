#makefile simples apenas para compilar e executar as entradas

CC ?=gcc
CFLAGS += -Wall

all: clean labirinto nivel_1 nivel_2 nivel_3 nivel_4 nivel_5 nivel_6

clean:
	rm -f a.out *.exe

build:
	$(CC) klotski_glauco_JG.c -o klotski.exe $(CFLAGS) 

labirinto: clean build
	./klotski.exe < labirinto-ok

nivel_1: clean build
	./klotski.exe < nv1-ok

nivel_2: clean build
	./klotski.exe < nv2-ok

nivel_3: clean build
	./klotski.exe < nv3-ok

nivel_4: clean build
	./klotski.exe < nv4-ok

nivel_5: clean build
	./klotski.exe < nv5-ok

nivel_6: clean build
	./klotski.exe < nv6-ok


.PHONY: clean build labirinto nivel_1 nivel_2 nivel_3 nivel_4 nivel_5 nivel_6