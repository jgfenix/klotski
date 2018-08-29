#makefile simples apenas para compilar e executar as entradas

CC ?=gcc
CFLAGS += -lX11 -lm -Wall

all: clean labirinto nivel_1 nivel_2 nivel_3 nivel_4 nivel_5

clean:
	@rm -f a.out *.exe saida.txt

build:
	$(CC) klotski_glauco_JG.c gfx.c -o klotski.exe $(CFLAGS) 

labirinto: clean build
	@./klotski.exe < labirinto-ok 2>/dev/null; true 

nivel_1: clean build
	@./klotski.exe < nv1-ok 2>/dev/null; true

nivel_2: clean build
	@./klotski.exe < nv2-ok 2>/dev/null; true

nivel_3: clean build
	@./klotski.exe < nv3-ok 2>/dev/null; true

nivel_4: clean build
	@./klotski.exe < nv4-ok 2>/dev/null; true

nivel_5: clean build
	@./klotski.exe < nv5-ok 2>/dev/null; true

.PHONY: clean build labirinto nivel_1 nivel_2 nivel_3 nivel_4 nivel_5