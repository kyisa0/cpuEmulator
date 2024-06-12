all:emulator.exe:asm.exe



emulator.exe:libexec.dll
	gcc src/emulator/emulator.c -o emulator.exe -Lsrc/emulator -lexec

asm.exe:libasm.dll
	gcc src/assembler/assembler.c -o asm.exe -L. -lasm


libexec.dll:
	gcc src/emulator/libexec.c -o libexec.dll -shared

libasm.dll:
	gcc src/assembler/libasm.c -o libasm.dll -shared