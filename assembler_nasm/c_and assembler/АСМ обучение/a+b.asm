%include "io.inc"
section .bss
 x resd 1
 y resd 1
section .text
global CMAIN
CMAIN:
    GET_DEC 4, x
    GET_DEC 4, y
    mov eax, dword[x]
    cmp eax, dword[y]
    jg go 
    add eax, dword[y]
    jmp end
go:
    sub eax, dword[y]
end:
    PRINT_DEC 4, eax
    xor eax, eax
    ret