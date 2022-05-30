#include <stdio.h>
#include <stdint.h>
#include "disk/elf.h"
#include "cpu/register.h"
#include "memory/dram.h"
#include "memory/instruction.h"

int main()
{
    init_handler_table();

    // init
    reg.rax = 0x1234;
    reg.rbx = 0x555555555190;
    reg.rcx = 0x555555555190;
    reg.rdx = 0xabcd0000;
    reg.rsi = 0x7fffffffdef8;
    reg.rdi = 0x1;
    reg.rbp = 0x7fffffffde00;
    reg.rsp = 0x7fffffffdde0;

    reg.rip = (uint64_t)&program[11];

    mm[va2pa(0x7fffffffde00)] = 0x0;        // rbp
    mm[va2pa(0x7fffffffddff)] = 0x0;        
    mm[va2pa(0x7fffffffddf0)] = 0xabcd;
    mm[va2pa(0x7fffffffddef)] = 0x12340000;
    mm[va2pa(0x7fffffffdde0)] = 0x0;        // rsp

    // run inst
    for (int i = 0; i < 15; i++)
    {
        instruction_cycle();
    }

    // verify

    int match = 1;
    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x555555555180);
    match = match && (reg.rcx == 0x555555555180);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7fffffffde00);
    match = match && (reg.rsp == 0x7fffffffdde0);

    if (match == 1)
    {
        printf("register match\n");
    }
    else
    {
        printf("register not match\n");
    }

    match = match && (mm[va2pa(0x7fffffffde00)] == 0x0);        // rbp
    match = match && (mm[va2pa(0x7fffffffddff)] == 0x1234abcd);
    match = match && (mm[va2pa(0x7fffffffddf0)] == 0xabcd);
    match = match && (mm[va2pa(0x7fffffffddef)] == 0x12340000);
    match = match && (mm[va2pa(0x7fffffffdde0)] == 0x0);        // rsp

    if (match == 1)
    {
        printf("memory match\n");
    }
    else
    {
        printf("memory not match\n");
    }

    return 0;
}