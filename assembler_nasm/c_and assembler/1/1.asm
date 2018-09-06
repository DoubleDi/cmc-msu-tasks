%include "io.inc"
section .bss
    a_x resd 1
a_y resd 1
v_x resd 1
v_y resd 1
t resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, v_x
    GET_DEC 4, v_y
    GET_DEC 4, a_x
    GET_DEC 4, a_y
    GET_DEC 4, t
    mov eax, dword[t]
    mul dword[t]; eax = t^2
    mov ebx, eax
    mul dword[a_x]
    mov ecx, eax
    mov eax, dword[v_x]
    mul dword[t]
    add ecx, eax
    PRINT_DEC 4, ecx
    PRINT_CHAR " "
    mov eax, dword[a_y]
    mul ebx
    mov ecx, eax
    mov eax, dword[v_y]
    mul dword[t]
    add ecx, eax
    PRINT_DEC 4, ecx
    xor eax, eax
    ret