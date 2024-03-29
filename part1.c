#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"


// forward declarations
void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction);
void write_load(Instruction);
void write_store(Instruction);
void write_branch(Instruction);
void write_auipc(Instruction);
void write_lui(Instruction);
void write_jalr(Instruction);
void write_jal(Instruction);
void write_ecall(Instruction);


void decode_instruction(Instruction instruction) {
  /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
  unsigned int code=instruction.opcode;
  
  switch(code) { // What do we switch on?
    /* YOUR CODE HERE */
    case 3:     //Tipo I load
      write_load(instruction);
      break;

    case (0x13):     //Tipo I
      write_itype_except_load(instruction);
      break;
    case 0x67:
      write_jalr(instruction);
      break;
    case 0x73:
      write_ecall(instruction);
      break;

    case 0x17:     //Tipo U 
      write_auipc(instruction);
      break;

    case 0x23:     //Tipo S
      write_store(instruction);
      break;

    case 0x33:     //Tipo R
      write_rtype(instruction);
      break;

    case 0x37:     //Tipo U
      write_lui(instruction);
      break;

    case 0x63:     //Tipo Sb
      write_branch(instruction);
      break;

    case 0x6F:     //Tipo Uj
      write_jal(instruction);
      break;

    default: // undefined opcode
      printf("error en decode");
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_rtype(Instruction instruction) {
  unsigned int funct3= instruction.rtype.funct3;
  unsigned int funct7= instruction.rtype.funct7;
  switch(funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
      switch (funct7)
      {
        case 0x00:
          print_rtype("add",instruction);
          break;
        case 0x01:
          print_rtype("mul",instruction);
          break;
        case 0x20:
          print_rtype("sub",instruction);
          break;
        default:
          handle_invalid_instruction(instruction);
          break;
      }
      break;
    case 0x1:
      switch (funct7)
      {
        case 0x00:
          print_rtype("sll",instruction);
          break;
        case 0x01:
          print_rtype("mulh",instruction);
          break;
        default:
          handle_invalid_instruction(instruction);
          break;
      }
      break;
    case 0x2:
      print_rtype("slt",instruction);
      break;
    case 0x4:
      switch (funct7)
      {
        case 0x00:
          print_rtype("xor",instruction);
          break;
        case 0x01:
          print_rtype("div",instruction);
          break;
        default:
          handle_invalid_instruction(instruction);
          break;
      }
      break;
    case 0x5:
      switch (funct7)
      {
        case 0x00:
          print_rtype("srl",instruction);
          break;
        case 0x20:
          print_rtype("sra",instruction);
          break;
        default:
          handle_invalid_instruction(instruction);
          break;
      }
      break;
    case 0x6:
      switch (funct7)
      {
        case 0x00:
          print_rtype("or",instruction);
          break;
        case 0x01:
          print_rtype("rem",instruction);
          break;
        default:
          handle_invalid_instruction(instruction);
          break;
      }
      break;
    case 0x7:
      print_rtype("and",instruction);
      break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_itype_except_load(Instruction instruction) {
  unsigned int funct3= instruction.itype.funct3;
  int imm=bitExtender(instruction.itype.imm, 12);
  unsigned int temp;
      switch (funct3)
      {
      case 0x0:
        print_itype_except_load("addi", instruction, imm);
        break;
      case 0x1:
        print_itype_except_load("slli", instruction, imm);
        break;
      case 0x2:
        print_itype_except_load("slti", instruction, imm);
        break;
      case 0x4:
        print_itype_except_load("xori", instruction, imm);
        break;
      case 0x5:
        temp=instruction.itype.imm;
        if ((temp>>10)&1){
          print_itype_except_load("srai", instruction, imm&31);
        }else{
          print_itype_except_load("srli", instruction, imm&31);
        }
        break;
      case 0x6:
        print_itype_except_load("ori", instruction, imm);
        break;
      case 0x7:
        print_itype_except_load("andi", instruction, imm);
        break;
      
      default:
        break;
      }
}


void write_load(Instruction instruction) {
  unsigned int funct3= instruction.itype.funct3;
  switch(funct3) { // What do we switch on?
    case 0:
      print_load("lb",instruction);
      break;

    case 1:
      print_load("lh",instruction);
      break;

    case 2:
      print_load("lw",instruction);
      break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_store(Instruction instruction) {
  unsigned int funct3= instruction.itype.funct3;
  switch(funct3) { // What do we switch on?
    case 0:
      print_store("sb",instruction);
      break;

    case 1:
      print_store("sh",instruction);
      break;

    case 2:
      print_store("sw",instruction);
      break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_branch(Instruction instruction) {
  int func3=instruction.btype.funct3;
  switch(func3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0:
      print_branch("beq", instruction);
      break;
    case 1:
      print_branch("bne", instruction);
      break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


/* For the writes, probably a good idea to take a look at utils.h */

void write_auipc(Instruction instruction) {
  /* YOUR CODE HERE */
  unsigned int rd=instruction.utype.rd;
  unsigned int offset=instruction.utype.imm;
  printf(AUIPC_FORMAT,rd,offset);
}


void write_lui(Instruction instruction) {
  /* YOUR CODE HERE */
  unsigned int rd=instruction.utype.rd;
  unsigned int offset=instruction.utype.imm;
  printf(LUI_FORMAT,rd,offset);
}


void write_jalr(Instruction instruction) {
  /* YOUR CODE HERE */
  printf("jalr\n");
}


void write_jal(Instruction instruction) {
  /* YOUR CODE HERE */
  unsigned int rd=instruction.jtype.rd;
  int imm=get_jump_distance(instruction);
  printf(JAL_FORMAT,rd,imm);
}


void write_ecall(Instruction instruction) {
  /* YOUR CODE HERE */
  printf("ecall\n");
}


void print_rtype(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
  unsigned int rd=instruction.rtype.rd;
  unsigned int rs1=instruction.rtype.rs1;
  unsigned int rs2=instruction.rtype.rs2;
  printf(RTYPE_FORMAT,name,rd,rs1,rs2);
}


void print_itype_except_load(char* name, Instruction instruction, int imm) {
  /* YOUR CODE HERE */
  printf(ITYPE_FORMAT, name, instruction.itype.rd, instruction.itype.rs1, imm);
  //printf("\n%d\n",bitExtender(instruction.itype.imm, 12));
}


void print_load(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
  unsigned int rd=instruction.itype.rd;
  unsigned int rs1=instruction.itype.rs1;
  int offset=get_memory_offset(instruction);
  printf(MEM_FORMAT,name,rd,offset,rs1);
}


void print_store(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
  unsigned int rs2=instruction.stype.rs2;
  unsigned int rs1=instruction.stype.rs1;
  int offset=get_memory_offset(instruction);
  printf(MEM_FORMAT,name,rs2,offset,rs1);

}


void print_branch(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
  int imm=get_branch_distance(instruction);
  printf(BRANCH_FORMAT,name,instruction.btype.rs1,instruction.btype.rs2,imm);
}
