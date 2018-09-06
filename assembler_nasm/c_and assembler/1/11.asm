%include "io.inc"

section .bss
letter resd 1
number resd 1
section .data
y dd 'A'

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_CHAR letter
    mov eax, dword[letter]
    sub eax, dword[y] 
    inc eax
    mov ebx, 8
    sub ebx, eax
    GET_DEC 4, number
    mov ecx, dword[number]
    mov eax, 8
    sub eax, ecx
    mov edx, 0
    mul ebx
    mov edx, 0
    mov dword[y], 2
    div dword[y]
    PRINT_DEC 4, eax 
    xor eax, eax
    ret