all: program_easy program_hard

program_easy: AsmFile.asm CFile.c
	nasm -f elf32 AsmFile.asm -o AsmFile.o
	gcc -std=c11 CFile.c -c -o CFile.o -m32
	gcc CFile.o AsmFile.o -o program_easy -m32

program_hard: AsmFile.asm CFile.c
	nasm -f elf32 AsmFile.asm -o AsmFile.o
	gcc -std=c11 CFile.c -c -o CFile.o -m32 -DHARD
	gcc CFile.o AsmFile.o -o program_hard -m32

clean:
	rm -f CFile.o AsmFile.o program
