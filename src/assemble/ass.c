#include <stdio.h>

#include "ass.h"

int main()
{
    cpu.rax = 0x1234abcd5678ffaa;

    printf("eax: %08x\n", cpu.eax);
    printf("ax: %04x\n", cpu.ax);
    printf("al: %02x\n", cpu.al);
    printf("ah: %02x\n", cpu.ah);
}

uint64_t decode_od(od_t od)
{
    if (od.type == IMM)
    {
        return od.imm;
    }
    else if (od.type == REG)
    {
        return *(uint64_t*)od.reg;
    }
    else
    {
        uint64_t addr = MM_LEN + 0xff;

        return mm[addr % MM_LEN]; // need optimize
    }
    
}