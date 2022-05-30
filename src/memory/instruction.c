#include "memory/instruction.h"
#include "cpu/mmu.h"
#include "cpu/register.h"

static uint64_t decode_od(od_t od)
{
    if (od.type == IMM)
    {
        return *((uint64_t *)&od.imm);
    }
    else if (od.type == REG)
    {
        return (uint64_t)od.reg1;
    }
    else
    {
        // mm
        uint64_t vaddr = 0;

        if (od.type == MM_IMM)
        {
            vaddr = od.imm;
        }
        else if (od.type == MM_REG)
        {
            // store reg
            vaddr = *(od.reg1);
        }
        else if (od.type == MM_IMM_REG)
        {
            // store reg
            vaddr = od.imm + *(od.reg1);
        }
        else if (od.type == MM_REG1_REG2)
        {
            // store reg
            vaddr = *(od.reg1) + *(od.reg2);
        }
        else if (od.type == MM_IMM_REG1_REG2)
        {
            // store reg
            vaddr = *(od.reg1) + *(od.reg2) + od.imm;
        }
        else if (od.type == MM_REG2_S)
        {
            // store reg
            vaddr = (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_IMM_REG2_S)
        {
            // store reg
            vaddr = (*(od.reg2)) * od.scal + od.imm;
        }
        else if (od.type == MM_REG1_REG2_S)
        {
            // store reg
            vaddr = *(od.reg1) + (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_IMM_REG1_REG2_S)
        {
            // store reg
            vaddr = od.imm + *(od.reg1) + (*(od.reg2)) * od.scal;
        }
        return va2pa(vaddr);
    }
}

void instruction_cycle()
{
    inst_t *instr = (inst_t *)reg.rip;
    
    // imm: imm
    // reg: value
    // mm: paddr
    uint64_t src = decode_od(instr->src);
    uint64_t dst = decode_od(instr->dst);

    // add rax rbx
    // op = add_reg_reg = 3
    // handler_table[add_reg_reg] == handler_table[3] == add_reg_reg_handler
    handler_t handler = handler_table[instr->op]; // add_reg_reg_handler

    // add_reg_reg_handler(src = &rax, dst = &rbx)
    handler(src, dst);
}

void init_handler_table()
{
    handler_table[mov_reg_reg] = &mov_reg_reg_handler;
    handler_table[add_reg_reg] = &add_reg_reg_handler;
}

void mov_reg_reg_handler(uint64_t src, uint64_t dst)
{
    *(uint64_t *)dst = *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t);
}

void add_reg_reg_handler(uint64_t src, uint64_t dst)
{
    // add_reg_reg_handler(src = &rax, dst = &rbx)
    // src/dst: register address
    // *(uint64_t *)dst: dst register value
    /*
    rax pmm[0x1234] = 0x12340000
    rbx pmm[0x1235] = 0xabcd

    src: 0x1234
    dst: 0x1235

    *(uint64_t *)src = 0x12340000
    *(uint64_t *)dst = 0xabcd
    *(uint64_t *)dst = 012340000 + 0xabcd = 0x1234abcd

    rbx pmm[0x1235] = 0x1234abcd
    */
    
    *(uint64_t *)dst = *(uint64_t *)dst + *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t);

}