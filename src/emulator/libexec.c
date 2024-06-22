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
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "emulator.h"

static uint8_t *ProgramCounter;
FILE* rom;

void init_pc(uint8_t *pc, FILE* ROM)
{
    ProgramCounter=pc;
    rom=ROM;
}

void read_header(char *path, uint8_t *erindc, header_t *header)//read header of file
{
    char header_byte;
    FILE *file=fopen(path, "rb");
    if(file==NULL)
    {
        *erindc=true;
        return;
    }
    fread(header_byte, sizeof(char), 1, file);
    header->eir=(header_byte>>0)&0b01;// set eir flag
    header->rk=(header_byte>>1)&0b01;// set rk flag
    header->rni=(header_byte>>2)&0b01;// set rni flag
    header->ti=(header_byte>>3)&0b01;// set ti flag
    fclose(file);
}

void extract_code(char *path, uint8_t *erindc)//extarcts machine code from .rom file and saves it to a temporary .hex file
{
    uint8_t code[256];
    FILE* rom_file=fopen(path, "rb");
    FILE* hex_file=fopen("code.hex", "wb");
    if(rom_file==NULL || hex_file==NULL) //THIS IS BUG FIX THISSSSS!!!
    {
        *erindc=true;
        return;
    }
    fseek(rom_file, 1, SEEK_CUR);// skip header
    fread(code, sizeof(uint8_t), 256, rom_file);
    fwrite(code, sizeof(uint8_t), 256, hex_file);
    fclose(rom_file);
    fclose(hex_file);

}

uint8_t readInstruction()// read instructions from a .hex file
{
    uint8_t instruction;
    if(fseek(rom, ProgramCounter, SEEK_CUR)!=0)// keep file pointer same as program counter
    {
        perror("Program Counter Failed.\n");
        fclose(rom);
        exit(0);
    }
    fread(instruction, sizeof(uint8_t), 1, rom);// read instruction
    return instruction;// return instruction
}
