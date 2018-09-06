%include "io.inc"

section .rodata
sca db "%s",'\10', 0
pri db "%s", 0
zero db "0", 0
twoone db "2 1", 0
onetwo db "1 2", 0

section .bss
s1 resb 1001
s2 resb 1001


section .text
CEXTERN gets
CEXTERN scanf
CEXTERN strstr
CEXTERN printf
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    xor eax, eax
    mov ecx, esp
    and esp, -16
    push ecx
    sub esp, 12
    mov dword[esp], sca
    mov dword[esp + 4], s1
    call scanf
    mov dword[esp + 4], s2
    call scanf
    mov dword[esp + 4], s1
    mov dword[esp], s2    
    call strstr
    test eax, eax
    jnz .end12
    mov dword[esp + 4], s2
    mov dword[esp], s1
    call strstr
    test eax, eax
    jnz .end21
    jmp .end0
.end12:
    mov dword[esp], pri
    mov dword[esp + 4], onetwo
    call printf
    jmp .end
.end21:
    mov dword[esp], pri
    mov dword[esp + 4], twoone
    call printf
    jmp .end
.end0:
    mov dword[esp], pri
    mov dword[esp + 4], zero
    call printf
    jmp .end
.end:
    add esp, 12
    pop ecx
    mov esp, ecx
    xor eax, eax
    ret