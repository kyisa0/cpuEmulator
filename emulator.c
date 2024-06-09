#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "emulator.h"

// Registers
uint8_t GP[6]={0, 0, 0, 0, 0, 0};// general purpose registers
uint8_t RO=0; // read only registers
uint8_t A=0; // accumulator register


//CPU
uint8_t RAM[256];// ram 256 bytes
uint8_t PC; // program counter max count 256 
uint8_t instr; // instruction register to hold instruction opcode



uint8_t reg_num;


void setcarry()
{
    RO=(RO|0x80);
}

void reset()
{
    PC=0;
    memset(RAM, 0, 256);
    memset(GP, 0, 6);
    RO=0;
    A=0;
}

int main(int argc, char *argv[])
{
    FILE *rom;
    if(!(argc>1))
    {
        printf("Usage: [hex file]");
        return 1;
    }
    rom=fopen(argv[1], "r");
    if(rom==NULL)
    {
        return 1;
    }
    init_pc(&PC, rom);

    while(PC<256)
    {
        instr=readInstruction();// read instruction
        switch(instr){
            case 0x01: //AND with A and GP1 value
                PC++;
                instr=readInstruction();// read register number
                A=A&GP[instr];
                PC++;
                break;
            case 0x02: // LDA load Accumulator with value on the memory address
                PC++;
                instr=readInstruction();// read memory address
                A=RAM[instr];
                PC++;
                break;
            case 0x03:// LDR load gp register with value on the memory address
                PC++;
                instr=readInstruction();// read register number
                reg_num=instr;
                PC++;
                instr=readInstruction();// read memory address
                GP[reg_num]=RAM[instr];
                PC++;
                break;
            case 0x04:// LDI load gp register with I value
                PC++;
                instr=readInstruction();// read Register number
                reg_num=instr;
                PC++;
                instr=readInstruction();// read I value
                GP[reg_num]=instr;
                PC++;
                break;
            case 0x05: //STA store value on accumulator to memory
                PC++;
                instr=readInstruction(); // read memory address
                RAM[instr]=A;
                PC++;
                break;
            case 0x06:// STR store value on GP register to memory
                PC++;
                instr=readInstruction();// read register number
                reg_num=instr;
                PC++;
                instr=readInstruction();// read memory address
                RAM[instr]=GP[reg_num];
                PC++;
                break;
            case 0x07:// or with Accumulator
                PC++;
                instr=readInstruction(); // read register number
                A=A|GP[instr];
                PC++;
                break;
            case 0x08:// XOR with accumulator
                PC++;
                instr=readInstruction();// read register number
                A=A^GP[instr];
                PC++;
                break;
            case 0x09:// Subtract with accumulator
                PC++;
                instr=readInstruction();// read register number
                if((A-GP[instr])<0) setcarry();
                A=A-GP[instr];
                PC++;
                break;
            case 0x0A:// Add with accumulator 
                PC++;
                instr=readInstruction();// read register number
                if((A+GP[instr])>255) setcarry();
                A=A+GP[instr];
                PC++;
                break;
            case 0x0B://Divide with accumulator
                PC++;
                instr=readInstruction();// read register number
                A=A/GP[instr];
                PC++;
                break;
            case 0x0C:// Multiply with accumulator
                PC++;
                instr=readInstruction();// read register number
                if((A+GP[instr])>255) setcarry();
                A=A*GP[instr];
                PC++;
                break;
            case 0x0D:// NOP instruction
                PC++;
                break;
            case 0x0E:// reverse register (NOT)
                PC++;
                instr=readInstruction();
                GP[instr]=~GP[instr];
                PC++;
                break;
            case 0x0F:// JMPR jump to memory address in a register
                PC++;
                instr=readInstruction();
                PC=(GP[instr]);
                break;
            case 0X10:// JMP to a address using I value
                PC++;
                instr=readInstruction();
                PC=instr;
                printf("Jumped to: %d", instr);
                break;
            case 0x11:// RST instruction
                reset();
                break;
            case 0x12:// Branch if equal
                PC++;
                instr=readInstruction();
                reg_num=instr;
                PC++;
                instr=readInstruction();
                if(A==GP[reg_num])
                {
                    PC=instr;
                }
                break;
            case 0x13:// Branch if not equal
                PC++;
                instr=readInstruction();
                reg_num=instr;
                PC++;
                instr=readInstruction();
                if(A!=GP[reg_num])
                {
                    PC=instr;
                }
                break;
            case 0x14:// branch if carry
                PC++;
                instr=readInstruction();
                if(((RO>>7)&1)==1)
                {
                    PC=instr;
                }
                break;
            case 0x15:// branch if not carry
                PC++;
                instr=readInstruction();
                if(((RO>>7)&1)==0)
                {
                    PC=instr;
                }
                break;
            case 0x16:// branch if greater
                PC++;
                instr=readInstruction();
                reg_num=instr;
                PC++;
                instr=readInstruction();
                if(A>GP[reg_num])
                {
                    PC=instr;
                }
                break;
            case 0x17:// branch if less
                PC++;
                instr=readInstruction();
                reg_num=instr;
                PC++;
                instr=readInstruction();
                if(A<GP[reg_num])
                {
                    PC=instr;
                }
                break;
            case 0x18:// set carry
                if(((RO>>7)&1)==1)
                {
                    RO=RO^0x80;
                }
                PC++;
                printf("Carry is set.");
                break;
            case 0x19:// reset carry
                if(((RO>>7)&1)==0)
                {
                    RO=RO|0x80;
                }
                PC++;
                printf("Carry is reset.");
                break;
            
        }
    }
}