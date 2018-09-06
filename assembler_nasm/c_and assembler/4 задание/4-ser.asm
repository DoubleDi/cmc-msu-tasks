%include "io.inc"
section .rodata
    template db `%u`, 0
    filename db "data.in", 0
    mode db "r", 0
section .bss
    trash resd 1
section .text
CEXTERN fscanf
CEXTERN printf
CEXTERN fopen
global CMAIN
CMAIN:
    mov ebp, esp
    and esp, -16
    sub esp, 16
   
    mov dword[esp], filename
    mov dword[esp+4], mode
    call fopen
    mov dword[esp], eax ; FILE*
   
    xor ebx, ebx ; answer
    mov dword[esp+8], trash
    mov dword[esp+4], template
.loop:
    call fscanf
    cmp eax, 0
    jle .end    
    inc ebx
    jmp .loop
.end:
    mov dword[esp], template
    mov dword[esp+4], ebx
    call printf
    xor eax, eax
    mov esp, ebp
    ret