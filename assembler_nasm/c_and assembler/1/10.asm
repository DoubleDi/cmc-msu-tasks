%include "io.inc"

section .bss
month resd 1
day resd 1

section .data
c dd 2

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, month
    GET_DEC 4, day
    mov eax, dword[month]
    dec eax
    mov edx, 0
    div dword[c]
    mov ebx, eax
    add eax, edx
    mov edx, 0
    mov dword[c], 41
    mul dword[c]
    mov ecx, eax
    mov eax, ebx
    mov edx, 0
    mov dword[c], 42
    mul dword[c]
    add ecx, eax
    add ecx, dword[day]
    PRINT_DEC 4, ecx
    xor eax, eax
    ret