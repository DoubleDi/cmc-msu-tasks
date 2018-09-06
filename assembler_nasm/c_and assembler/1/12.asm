%include "io.inc"



section .data
card dd "23456789TJQKA"
suit dd "SCDH"
d dd 13

section .bss
num resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, num
    mov eax, dword[num]
    dec eax
    mov edx, 0
    div dword[d]
    movzx ebx, byte[card + edx]
    PRINT_CHAR ebx
    movzx eax, byte[suit + eax]
    PRINT_CHAR eax
    xor eax, eax
    ret