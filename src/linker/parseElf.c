#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<headers/linker.h>
#include<headers/common.h>

int read_elf(const char *filename, uint64_t bufaddr)
{
    //open file and read
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        debug_printf(DEBUG_LINKER, "unable to open file %s\n", filename);
        exit(1);
    } 

    // read text line by line
    char line[MAX_ELF_FILE_WIDTH];
    int line_counter = 0;

    while (fgets(line, MAX_ELF_FILE_WIDTH, fp) != NULL)
    {
        line_counter++;
        printf("%s\n", line);
    }
    return line_counter;
}

