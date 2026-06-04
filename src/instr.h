#ifndef INSTR_H
#define INSTR_H
#include "instr_types.h"
struct instr_t decode_command(unsigned char cmd);
void print_instr(struct instr_t instr);
#endif
