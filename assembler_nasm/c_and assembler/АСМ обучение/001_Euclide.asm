%include "io.inc"

section .bss
first resw 1
second resw 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_UDEC 2, first
    GET_UDEC 2, second
START_LOOP:
    MOV DX, 0
    MOV AX, word[first]
    MOV BX, word[second]
    DIV BX
    CMP DX, 0
    JZ END_LOOP
    MOV word[second], DX
    MOV word[first], BX
    JMP START_LOOP
END_LOOP:
    PRINT_UDEC 2, BX
    XOR AX, AX
    ret