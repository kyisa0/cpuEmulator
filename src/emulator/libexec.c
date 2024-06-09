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

uint8_t readInstruction()
{
    if(fseek(rom, ProgramCounter, SEEK_CUR)!=0)
    {
        perror("Program Counter Failed.\n");
        fclose(rom);
        exit(0);
    }
}
