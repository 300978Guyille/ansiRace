#include <stdio.h>

#include "types.h"

#include "utils.h"



int main () {



    /* bitExtender, 12 bits, as in type I and type S*/

    printf("Testing bitExtender, 12 bits...\n");

    printf("your answer: %08x\tcorrect answer: ffffffff\n", bitExtender(0x00000fff, 12));

    printf("your answer: %08x\tcorrect answer: fffff800\n", bitExtender(0x00000800, 12));

    printf("your answer: %08x\tcorrect answer: 000007ff\n", bitExtender(0xfffff7ff, 12));



    /* bitExtender, 13 bits, as in type B*/

    printf("Testing bitExtender, 13 bits...\n");

    printf("your answer: %08x\tcorrect answer: ffffffff\n", bitExtender(0x00001fff, 13));

    printf("your answer: %08x\tcorrect answer: fffff000\n", bitExtender(0x00001000, 13));

    printf("your answer: %08x\tcorrect answer: 00000fff\n", bitExtender(0xffffefff, 13));



    /* bitExtender, 21 bits, as in type J*/

    printf("Testing bitExtender, 21 bits...\n");

    printf("your answer: %08x  \tcorrect answer: ffffffff\n", bitExtender(0x001fffff, 21));

    printf("your answer: %08x  \tcorrect answer: fff00000\n", bitExtender(0x00100000, 21));

    printf("your answer: %08x  \tcorrect answer: 000fffff\n", bitExtender(0xffefffff, 21));



    /* get_memory_offset */

    printf("Testing get_memory_offset...\n");

    Instruction gmo;

    gmo.bits = 0xfe000e23;

    printf("your answer: %d  \tcorrect answer: -4\n", get_memory_offset(gmo));

    gmo.bits = 0x02000023;

    printf("your answer: %d  \tcorrect answer: 32\n", get_memory_offset(gmo));

    gmo.bits = 0x40000023;

    printf("your answer: %d  \tcorrect answer: 1024\n", get_memory_offset(gmo));

    gmo.bits = 0x7e000fa3;

    printf("your answer: %d  \tcorrect answer: 2047\n", get_memory_offset(gmo));



    /* get_branch_distance */

    printf("Testing get_branch_distance...\n");

    Instruction gbd;

    gbd.bits = 0xfe000e00;

    printf("your answer: %d  \tcorrect answer: -2052\n", get_branch_distance(gbd));

    gbd.bits = 0x02000000;

    printf("your answer: %d  \tcorrect answer: 32\n", get_branch_distance(gbd));

    gbd.bits = 0x40000000;

    printf("your answer: %d  \tcorrect answer: 1024\n", get_branch_distance(gbd));

    gbd.bits = 0x7e000f80;

    printf("your answer: %d  \tcorrect answer: 4094\n", get_branch_distance(gbd));\

    gbd.bits = 0x00000080;

    printf("your answer: %d  \tcorrect answer: 2048\n", get_branch_distance(gbd));



    /* get_jump_distance */

    printf("Testing get_jump_distance...\n");

    Instruction gjd;

    gjd.bits = 0xfe000000;

    printf("your answer: %d  \tcorrect answer: -1046560\n", get_jump_distance(gjd));

    gjd.bits = 0x02000000;

    printf("your answer: %d  \tcorrect answer: 32\n", get_jump_distance(gjd));

    gjd.bits = 0x40000000;

    printf("your answer: %d  \tcorrect answer: 1024\n", get_jump_distance(gjd));

    gjd.bits = 0xfffff000;

    printf("your answer: %d  \tcorrect answer: -2\n", get_jump_distance(gjd));

    gjd.bits = 0x7fe00000;

    printf("your answer: %d  \tcorrect answer: 2046\n", get_jump_distance(gjd));

    gjd.bits = 0x00100000;

    printf("your answer: %d  \tcorrect answer: 2048\n", get_jump_distance(gjd));

    gjd.bits = 0x000ff000;

    printf("your answer: %d  \tcorrect answer: 1044480\n", get_jump_distance(gjd));



}