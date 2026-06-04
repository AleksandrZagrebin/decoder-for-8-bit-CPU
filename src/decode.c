#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "instr_types.h"

struct instr_t decode_command(unsigned char cmd) {
    struct instr_t instr;
    int rf1, rf2;
    
    if ((cmd >> 7) == 0) {
        instr.opcode = MOVI;
        instr.opnd.imm = cmd;
        return instr;
    }

    if (((cmd >> 6) & 1) == 1) {
        if ((cmd >> 2) == 0x30) {
            instr.opcode = IN;
        }
        else if (((cmd >> 2) == 0x31)) {
            instr.opcode = OUT;
        }
        else {
            fprintf(stderr, "Bad in/out: %x\n", (unsigned)cmd);
            abort();
        }
        rf1 = cmd & 0x3;
        instr.opnd.rop = rf1;
        return instr;
    }
    
    switch ((cmd >> 4) & 0xF) {
        case 8: instr.opcode = ADD; break;
        case 9: instr.opcode = SUB; break;
        case 10: instr.opcode = MUL; break;
        case 11: instr.opcode = DIV; break;
        default:
            fprintf(stderr, "Unrecognized instr: %x\n", cmd);
            abort();
    }
    
    rf1 = cmd & 0x3;
    rf2 = (cmd >> 2) & 0x3;
    
    instr.opnd.ops.rs = rf1;
    instr.opnd.ops.rd = rf2;
    return instr;
}

void print_instr(struct instr_t instr) {
    const char* regnames[] = { "A","B","C","D" };
    const char* arithnames[] = { "ADD","SUB","MUL","DIV" };
    
    switch (instr.opcode) {
        case MOVI:
            printf("MOVI D, %d\n", instr.opnd.imm);
            break;
        case IN:
            printf("IN %s\n", regnames[instr.opnd.rop]);
            break;
        case OUT:
            printf("OUT %s\n", regnames[instr.opnd.rop]);
            break;
        case ADD:
        case SUB:
        case MUL:
        case DIV:
            printf("%s %s, %s\n", arithnames[instr.opcode - 8], 
                   regnames[instr.opnd.ops.rd], regnames[instr.opnd.ops.rs]);
            break;
        default:
            fprintf(stderr, "Unsupported inst\n");
            abort();
    }
}
