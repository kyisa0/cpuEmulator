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

#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>
#include "asm.h"
#include <stdbool.h>


_u8 argp(char *source, char *target1, char *target2)
{
    return ((strcmp(source, target1)==0)||(strcmp(source, target2)==0));
}

_u8 stwth(char *source, char *delimeter)
{
    _u64 size_s=sizeof(source);
    _u64 size_d=sizeof(delimeter);

    if(size_d>size_s)
    {
        return 0;
    }
    int i=0;
    while (1)
    {
        if(!(i<size_s))
        {
            return 0;
        }
        if(source[i]==delimeter[i])
        {
            if(size_d==i)
            {
                return 1;
            }
            i++;
        }
        else{
            return 0;
        }
    }
}