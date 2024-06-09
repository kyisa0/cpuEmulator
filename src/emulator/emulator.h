#ifndef EMULATOR_H
#define EMULATOR_H

void init_pc(uint8_t *pc, FILE *rom);
uint8_t readInstruction();

#endif