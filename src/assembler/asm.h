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

#ifndef ASM_H
#define AMS_H

#include <stdio.h>
#include <stdbool.h>

#define _u8 uint8_t
#define _u64 uint64_t

_u8 argp(char *s, char *t1, char *t2);
_u8 stwth(char *source, char *delimeter);

typedef struct{
    bool rni;
    bool ti;
    bool eir;
}settings;

#endif