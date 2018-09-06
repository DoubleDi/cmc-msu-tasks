%include "io.inc"
section .bss
c resd 1
b resd 1
a resd 1

section .text
global CMAIN
CMAIN:
    GET_HEX 4, a
    GET_HEX 4, b
    GET_HEX 4, c
    mov eax, dword[c]
    and eax, dword[a]
    mov ecx, dword[c]
    not ecx
    and ecx, dword[b]
    or eax, ecx
    PRINT_HEX 4, eax
    xor eax, eax
    ret