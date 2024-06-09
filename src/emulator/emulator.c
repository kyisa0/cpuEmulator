/*
    cpuEmulator, simple emulator for my custom ISA
    
    Copyright (C) 2024  kyisa0

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "emulator.h"

// Registers
uint8_t GP[6]={0, 0, 0, 0, 0, 0};// general purpose registers
uint8_t RO=0; // flag registers
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
    RO=0; //flag register
    A=0; //accumulator register
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
                printf("And result of: %u\n", A);
                PC++;
                break;
            case 0x02: // LDA load Accumulator with value on the memory address
                PC++;
                instr=readInstruction();// read memory address
                A=RAM[instr];
                printf("Value %u loaded to A register.\n", A);
                PC++;
                break;
            case 0x03:// LDR load gp register with value on the memory address
                PC++;
                instr=readInstruction();// read register number
                reg_num=instr;
                PC++;
                instr=readInstruction();// read memory address
                GP[reg_num]=RAM[instr];
                printf("Value %u loaded to register %u\n", GP[reg_num], reg_num);
                PC++;
                break;
            case 0x04:// LDI load gp register with I value
                PC++;
                instr=readInstruction();// read Register number
                reg_num=instr;
                PC++;
                instr=readInstruction();// read I value
                GP[reg_num]=instr;
                printf("immediate value %u loaded to register %u\n", instr, reg_num);
                PC++;
                break;
            case 0x05: //STA store value on accumulator to memory
                PC++;
                instr=readInstruction(); // read memory address
                RAM[instr]=A;
                PC++;
                printf("value %u stored to ram address %u\n", A, instr);
                break;
            case 0x06:// STR store value on GP register to memory
                PC++;
                instr=readInstruction();// read register number
                reg_num=instr;
                PC++;
                instr=readInstruction();// read memory address
                RAM[instr]=GP[reg_num];
                printf("Value %u stored to ram address %u\n", GP[reg_num], instr);
                PC++;
                break;
            case 0x07:// or with Accumulator
                PC++;
                instr=readInstruction(); // read register number
                A=A|GP[instr];
                PC++;
                printf("Result of OR is %u\n", A);
                break;
            case 0x08:// XOR with accumulator
                PC++;
                instr=readInstruction();// read register number
                A=A^GP[instr];
                printf("result of xor is %u\n", A);
                PC++;
                break;
            case 0x09:// Subtract with accumulator
                PC++;
                instr=readInstruction();// read register number
                if((A-GP[instr])<0) setcarry();
                A=A-GP[instr];
                printf("Result of subtraction is %u\n", A);
                PC++;
                break;
            case 0x0A:// Add with accumulator 
                PC++;
                instr=readInstruction();// read register number
                if((A+GP[instr])>255) setcarry();
                A=A+GP[instr];
                printf("Result of add is %u\n", A);
                PC++;
                break;
            case 0x0B://Divide with accumulator
                PC++;
                instr=readInstruction();// read register number
                A=A/GP[instr];
                printf("Result of divide is %u\n", A);
                PC++;
                break;
            case 0x0C:// Multiply with accumulator
                PC++;
                instr=readInstruction();// read register number
                if((A+GP[instr])>255) setcarry();
                A=A*GP[instr];
                printf("Result of multiply is %u\n", A);
                PC++;
                break;
            case 0x00:// NOP instruction
                PC++;
                printf("NOP\n");
                break;
            case 0x0E:// reverse register (NOT)
                PC++;
                instr=readInstruction();
                GP[instr]=~GP[instr];
                printf("A register reversed\n");
                PC++;
                break;
            case 0x0F:// JMPR jump to memory address in a register
                PC++;
                instr=readInstruction();
                PC=(GP[instr]);
                printf("Jumped to: %u\n", GP[instr]);
                break;
            case 0X10:// JMP to a address using I value
                PC++;
                instr=readInstruction();
                PC=instr;
                printf("Jumped to: %u\n", instr);
                break;
            case 0x11:// RST instruction
                reset();
                printf("Reset.\n");
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
                else{
                    PC++;
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
                else{
                    PC++;
                }
                break;
            case 0x14:// branch if carry
                PC++;
                instr=readInstruction();
                if(((RO>>7)&1)==1)
                {
                    PC=instr;
                }
                else{
                    PC++;
                }
                break;
            case 0x15:// branch if not carry
                PC++;
                instr=readInstruction();
                if(((RO>>7)&1)==0)
                {
                    PC=instr;
                }
                else{
                    PC++;
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
                else{
                    PC++;
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
                else{
                    PC++;
                }
                break;
            case 0x18:// set carry
                if(((RO>>7)&1)==1)
                {
                    RO=RO^0x80;
                }
                PC++;
                printf("Carry is set.\n");
                break;
            case 0x19:// reset carry
                if(((RO>>7)&1)==0)
                {
                    RO=RO|0x80;
                }
                PC++;
                printf("Carry is reset.\n");
                break;
            case 0x1A: //envram unimplemented
                PC++;
                break;
            case 0x1B: //enterm unimplemented
                PC++;
                break;
            case 0x1C:
                printf("HALT\n");
                exit(0);
                break;

                
        }
    }
}
