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

// string manipulating part
_u8 argp(char *source, char *target1, char *target2) // Check if argument one of two
{
    return ((strcmp(source, target1)==0)||(strcmp(source, target2)==0));
}

_u8 stwth(char *source, char *delimeter) // check if source starts with a spesific delimeter
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


char *fread_d(char *delimeter, size_t size_del, FILE* file_stream) // file read until delimeter or end of file is met
{
    bool found=false;// found indicator
    char *ptr;// pointer
    long cur_pos=ftell(file_stream);// start cursor position
    char ch;// character buffer to hold fgetc return value
    size_t i_del=0;// index_delimeter holds index of delimeter
    while((ch=fgetc(file_stream))!=EOF)
    {
        if(ch==delimeter[i_del])// compare 
        {
            i_del++;
            if(i_del==size_del)// if index of delimeter equal to size of delimeter 
            {
                found=true;// found is true
                break;
            }
        }
        else if(ch!=delimeter[i_del])// if compare is false
        {
            i_del=0;//set del to 0 to start again
        }
    }
    if(found==true)// if found
    {
        long end_pos=ftell(file_stream);// get end position
        ptr=(char *)malloc(sizeof(char)*(end_pos-cur_pos-size_del)+1);// allocate memory with size of calculated number, +1 for null terminator

        if(ptr==NULL)
        {
            return NULL;//return error
        }

        if(fseek(file_stream, cur_pos, SEEK_SET)!=0)
        {
            return NULL;//return error
        }

        fread(ptr, sizeof(char), end_pos-cur_pos-size_del, file_stream);// +1 for null terminator
        ptr[end_pos-cur_pos-1]='\0';
        return ptr;// return allocated and formatted output
    }
}


// end of string manipulating part