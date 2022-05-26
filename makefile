CC = /usr/bin/gcc-9
CFLAFS = -Wall -g -O2 -Werror -std=gnu99 -Wno-unused-function

BIN_HARDWARE = ./bin/test_hardware

SRC_DIR = ./src

# debug
COMMON = $(SRC_DIR)/common/print.c $(SRC_DIR)/common/convert.c

.PHONY: link
link:
	$(CC) $(CFLAFS) -I$(SRC_DIR) $(COMMON) $(SRC_DIR)/tests/test_elf.c $(SRC_DIR)/linker/parseElf.c -o ./bin/test_elf
	./bin/test_elf
