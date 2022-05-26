#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<headers/linker.h>
#include<headers/common.h>

int read_elf(const char *filename, uint64_t bufaddr);

int main()
{
    read_elf("./files/exe/sum.elf.txt", 0);
    return 0;
}