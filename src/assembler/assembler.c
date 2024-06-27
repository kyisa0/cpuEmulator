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
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "asm.h"
#include <Windows.h>

settings pc_set;

uint8_t instr_opcode[256][3][1];

void print_help()
{
    puts("Usage: [file.s] [options]\n"
         "\t-h, --help\t print this and exit.\n"
         "\t--reset-non-instr= true\\false\t if true and instruction is unknown reset the cpu.\n"
         "\t--text-interface= true\\false\t enable text interface, disable gui or disable text and enable gui\n"
         "\t--receive-key= true\\false\t if enabled receives the keyboard presses\n"
         "\t--end-in-reset= true\\false\t if enabled when pc counts to last instruction it will reset\n");
}


int main(int argc, char *argv[])
{
    char temp[1024];
    char file_name[64];
    if(!(argc>1))
    {
        printf("Usage: [file.s] [options]");
        return 1;
    }
    for(int i=2;i<=argc;i++)
    {
        if(argp(argv[i], "-h", "--help"))
        {
            print_help();
        }
        if(stwth(argv[i], "--reset-non-instr=") && sizeof(argv[i])>18)
        {
            
            strncpy(temp, argv[i]+18, (sizeof(argv[i]-18)));
            if(strcmp(temp, "true"))
            {
                pc_set.rni=true;
            }
            else{
                pc_set.rni=false;
            }
        }
    }

    if(!_access(argv[1], 0))
    {
        printf("Error: File doesn't exists\n");
    }

    FILE* file_code=fopen(argv[1], "r");

    char *f_buffer; 
    // read and parse the source code assembly file


}
