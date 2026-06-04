#include<stdio.h>
#include<assert.h>

#include "instr.h"
#include "instr_types.h"
int main() {
    unsigned command;
    
    while (scanf("%x", &command) == 1) {
        struct instr_t instr;
        unsigned char cmd = command & 0xFF;
        assert(cmd == command);
        instr = decode_command(cmd);
        print_instr(instr);
    }
    
    return 0;
}
