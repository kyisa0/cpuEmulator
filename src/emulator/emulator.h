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


#ifndef EMULATOR_H
#define EMULATOR_H
#include <stdbool.h>
void init_pc(uint8_t *pc, FILE *rom);
uint8_t readInstruction();
typedef struct{
    bool rni; // reset if non-instruction
    bool ti; // text interface
    bool rk; // allocate memory for keybaord buffer
    bool eir; // reset if pc is 255
}header_t;
void read_header(char *path, uint8_t *erindc, header_t *header);
void extract_code(char *path, uint8_t *erindc);
#endif
