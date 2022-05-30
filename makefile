CC = /usr/bin/gcc-9
CFLAFS = -Wall -g -O2 -Werror -std=gnu99 -Wno-unused-function

EXE = program

SRC = ./src

CODE = ./src/memory/instruction.c ./src/disk/code.c ./src/memory/dram.c ./src/cpu/mmu.c ./src/main.c

 .PHONY: program
 main:
	$(CC) $(CFLAGS) -I$(SRC) $(CODE) -o $(EXE)

run:
	./$(EXE)