#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


//sign extends a bitfield with given size
/* You may find implementing this function helpful */
int bitExtender(unsigned int field, unsigned int size) {
  /* YOUR CODE HERE */
  int bitSigno = size - 1;

  uint32_t fieldExt = field;


  if((field >> bitSigno) & 1){
    unsigned int fieldMask = 0xFFFFFFFF << size;
    fieldExt = (fieldExt | fieldMask);
    return fieldExt;
  } else {
    unsigned int fieldMask0 = 0xFFFFFFFF << size;
    fieldExt = (fieldExt & ~fieldMask0);
    return fieldExt;
  }

}


/* Distances in BYTES */

int get_branch_distance(Instruction instruction) {
  /* YOUR CODE HERE */
  /*bit original 12 11 10 9 8 7 6 5 4 3 2 1 (0)*/
  /*bit desorden 12 10 9 8 7 6 5 4 3 2 1 11 (0)*/
  /*imm7 = 12 10 9 8 7 6 5*/
  /*imm5 = 4 3 2 1 11*/

  unsigned int im5 = instruction.btype.imm5; /*Tomamos los imme 5 y 7 de la instrucci'on*/
  unsigned int im7 = instruction.btype.imm7;
  
  /*Obtenemos los bits 12 y 11 respectivamente segun como estan ordenados en la greenCard*/
  unsigned int bit12 = (im7 >> 6) & 1;

  unsigned int bit11 = (im5) & 1;

  unsigned int parte1Bit = 0b11110;
  unsigned int parte2Bit = 0b00111111;

 /*Obtenemos los bits que van del 10 al 5 y del 4 al 1 utilizando mascaras de bits*/
  unsigned int bit4_to_1 = (im5 & parte1Bit);
  unsigned int bit10_to_5 = (im7 & parte2Bit); 


  /*Unimos los bit 12 y 11 con los bits del 10 al 5 y del 4 al 1, asi teniendo el bit en orden 12 11 10 9 8 7 6 5 4 3 2 1 0 */
  int bitOrdenado = (bit12 << 12) | (bit11 << 11) | (bit10_to_5 << 5) | (bit4_to_1);

  return bitExtender(bitOrdenado,13);
}


int get_jump_distance(Instruction instruction) {
  /* YOUR CODE HERE */
  /*20 10 9 8 7 6 5 4 3 2 1 11 19 18 17 16 15 14 13 12*/

  unsigned int imme = instruction.jtype.imm;

  unsigned int bit20 = (imme >> 19) & 1;

  unsigned int maskForBit10_to_1 = 0b01111111111000000000;
  unsigned int maskForBit19_to_12 = 0b00000000000011111111;
  unsigned int maskForBit11 = 0b00000000000100000000;

  unsigned int bit10_to_1 = (imme & maskForBit10_to_1);
  unsigned int bit19_to_12 = (imme & maskForBit19_to_12);
  unsigned int bit11 = (imme & maskForBit11);

  bit10_to_1 = (bit10_to_1 >> 8);

  int jump = (bit20 << 20) | (bit19_to_12 << 12) | (bit11 << 3) | (bit10_to_1);


  return bitExtender(jump,21);
}

/* Offset in BYTES */
/* Used both in load and store */

int get_memory_offset(Instruction instruction) {
  /* YOUR CODE HERE */

  unsigned int im5 = instruction.stype.imm5; 
  unsigned int im7 = instruction.stype.imm7;
  unsigned int imme = instruction.itype.imm;

  if(instruction.opcode == 0b0000011){
    /*tipo I*/
    int imm = imme;
    return bitExtender(imm,12);

  } else if(instruction.opcode == 0b0100011){
    /*tipo S*/
    int store = (im7 << 5) | (im5);
    return bitExtender(store,12); 
  } else {
    /*El opcode no era de tipo I o S*/
    return 0;
  }
}


void handle_invalid_instruction(Instruction instruction) {
  printf("Invalid Instruction: 0x%08x\n", instruction.bits);
}


void handle_invalid_read(Address address) {
  printf("Bad Read. Address: 0x%08x\n", address);
  exit(-1);
}


void handle_invalid_write(Address address) {
  printf("Bad Write. Address: 0x%08x\n", address);
  exit(-1);
}
