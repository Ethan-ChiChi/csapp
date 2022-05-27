#include <stdint.h>
#include <stdio.h>

// fake memory
#define MM_LEN 1000

uint8_t mm[MM_LEN];

typedef enum OP
{
    MOV, 
    PUSH, 
    CAL
} op_t;

typedef enum OD_TYPE
{
    IMM, REG, 
    MM_IMM, MM_REG, MM_IMM_REG, MM_REG1, MM_REG1_REG2,
    MM_IMM_REG1_REG2, MM_REG2_S, MM_IMM_REG2_S,
    MM_REG1_REG2_S, MM_IMM_REG1_REG2_S
} od_type_t;

typedef struct OD
{
    od_type_t type;

    int64_t imm;
    int64_t scal;
    uint64_t *reg1;
    uint64_t *reg2;

    char code[100];
} od_t;

typedef struct INSTRUCT_STRUCT
{
    op_t op; // mov, push
    op_t src;
    op_t dst;
} inst_t;

//fake instruction
#define INST_LEN 100

inst_t program[INST_LEN];

uint64_t decode_od(od_t od);
