%include "io.inc"

section .bss
m resd 1
n resd 1

section .data
x dd 10

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_UDEC 4, eax
    GET_UDEC 4, n
    xor ebx, ebx
.L:    
    cmp ebx, dword[n]
    je .end
    inc ebx
    push eax
    call reverse
    pop ecx
    add eax, ecx
    jmp .L
.end:
    push eax
    call reverse
    pop ecx
    cmp eax, ecx
    jne .no
    PRINT_STRING "Yes"
    NEWLINE
    PRINT_UDEC 4, eax
    xor eax, eax
    ret
.no:
    PRINT_STRING "No"
    xor eax, eax
    ret

    
reverse:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    xor ecx, ecx
.rev:
    xor edx, edx
    div dword[x]
    imul ecx, [x]
    add ecx, edx
    test eax, eax
    jnz .rev
    mov eax, ecx
    leave
    ret
    
    