#include <stdio.h>
#include <stdint.h>
#include "disk/elf.h"
#include "cpu/mmu.h"
#include "cpu/register.h"
#include "memory/dram.h"
#include "memory/instruction.h"

int main()
{
    init_handler_table();

    // init
    reg.rax = 0x12340000;
    reg.rbx = 0x555555555190;
    reg.rcx = 0x555555555190;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7fffffffdef8;
    reg.rdi = 0x1;
    reg.rbp = 0x7fffffffde00;
    reg.rsp = 0x7fffffffdde0;

    reg.rip = (uint64_t)&program[11];

    write64bits_dram(va2pa(0x7fffffffde00), 0x0); // rbp
    write64bits_dram(va2pa(0x7fffffffddf8), 0x0);
    write64bits_dram(va2pa(0x7fffffffddf0), 0xabcd);
    write64bits_dram(va2pa(0x7fffffffdde8), 0x12340000);
    write64bits_dram(va2pa(0x7fffffffdde0), 0x0);  // rsp

    print_register();
    print_stack();

    // run inst
    for (int i = 0; i < 15; i++)
    {
        instruction_cycle();

        print_register();
        print_stack();
    }

    // verify

    int match = 1;
    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x555555555190);
    match = match && (reg.rcx == 0x555555555190);
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

    match = match && (read64bits_dram(va2pa(0x7fffffffde00)) == 0x0);        // rbp
    match = match && (read64bits_dram(va2pa(0x7fffffffddf8)) == 0x1234abcd);
    match = match && (read64bits_dram(va2pa(0x7fffffffddf0)) == 0xabcd);
    match = match && (read64bits_dram(va2pa(0x7fffffffdde8)) == 0x12340000);
    match = match && (read64bits_dram(va2pa(0x7fffffffdde0)) == 0x0);        // rsp

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