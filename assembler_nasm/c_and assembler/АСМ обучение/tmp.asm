%include "io.inc"

section .bss
x resd 1
section .data
c dd 10

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, x
    mov eax, dword[x]
    mov ebx, 0
    mov edx, 0
start:    
    add ebx, edx
    mov ecx, eax
    sub ecx, 10
    mov edx, 0
    js second
    div dword[c]
    add eax , 0
    jnz start
second:
    add ebx, eax
    PRINT_DEC 4, ebx
    xor eax, eax
    ret