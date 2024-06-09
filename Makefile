all:emulator.exe:asm.exe



emulator.exe:libexec.dll
	gcc src/emulator/emulator.c -o emulator.exe -Lsrc/emulator -lexec

asm.exe:
	gcc src/assembler/assembler.c -o asm.exe


libexec.dll:
	gcc src/emulator/libexec.c -o libexec.dll -shared

