%include "io.inc"
section .rodata
num db "%d", 0
stroke db "%s", 0

section .bss
strarr resb 5500
x resd 1
st resb 11

section .data
len dd 11

section .text
CEXTERN printf
CEXTERN scanf
CEXTERN strcmp
CEXTERN strcpy
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    and esp, -16
    sub esp, 16
    mov dword[esp], num
    mov dword[esp + 4], x
    call scanf
    xor ebx, ebx
    xor esi, esi
.L: 
    inc ebx
    cmp ebx, [x]
    jg .end
    mov dword[esp], stroke
    ;mov eax, esi
   ; imul eax, [len]
   ; lea eax, [strarr + eax]
    mov dword[esp + 4], st
    call scanf
    xor edi, edi    
.L1:
    cmp edi, esi
    je .skip
    lea eax, [strarr + edi]
    mov dword[esp], eax
    mov dword[esp + 4], st
    call strcmp
    cmp eax, 0
    je .L
    add edi, 11
    jmp .L1
.skip:
    lea eax, [strarr + esi]
    mov [esp], eax
    mov dword[esp + 4], st
    call strcpy
    add esi, 11
    jmp .L  
.end:
    mov dword[esp], num
    xor edx, edx
    mov eax, esi
    mov esi, 11
    div esi
    mov [esp + 4],  eax
    call printf
    mov esp, ebp 
    xor eax, eax
    ret