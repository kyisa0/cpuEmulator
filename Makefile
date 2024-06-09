all:emulator.exe:asm.exe

emulator.exe:libexec.dll
	gcc emulator.c -o emulator.exe -L. -lexec

libexec.dll:
	gcc libexec.c -c -o libexec.o
	gcc libexec.o -shared -o libexec.dll

clean:
	rm libexec.o libexec.dll emulator.exe
asm.exe:
	gcc assembler.c -o asm.exe