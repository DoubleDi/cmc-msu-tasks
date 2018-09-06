%include "io.inc"

section .rodata
sca db "%u", 0
f db "data.in", 0
fw db "r", 0

section .bss
x1 resd 1
file resd 1

section .text
CEXTERN fscanf
CEXTERN fopen
CEXTERN printf
CEXTERN fclose
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    and esp, -16
    sub esp, 16 
    xor ebx, ebx
    mov dword[esp], f
    mov dword[esp + 4], fw
    call fopen
    mov esi, eax
    mov dword[esp], eax
    mov dword[esp + 4], sca
    mov dword[esp + 8], x1
    call fscanf
    cmp eax, 0
    jle .end
.L:
    inc ebx
    call fscanf
    cmp eax, 0
    jle .end
    jmp .L
.end:
    mov dword[esp], sca
    mov dword[esp + 4], ebx
    call printf
    mov [esp], esi
    call fclose
    mov esp, ebp
    xor eax, eax
    ret