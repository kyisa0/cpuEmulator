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