%include "io.inc"

section .bss
a resd 1
b resd 1
c resd 1

section .data
mas times 30 dd 0
mas1 times 30 dd 0
ten dd 10

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    inc dword[mas1]
    mov ebp, esp; for correct debugging
    GET_UDEC 4, a
    GET_UDEC 4, b
    GET_UDEC 4, c
    push dword[a]
    call multiply
    pop dword[a]
    push dword[b]
    call multiply
    pop dword[b]
    xor ecx, ecx
    push dword[c]
    call multiply
    pop dword[c]
    mov ecx, eax
.pr:
    cmp ecx, -1
    je .endend
    PRINT_UDEC 4, [mas1 + 4 * ecx]
    dec ecx
    jmp .pr
.endend:
    xor eax, eax
    ret
    
multiply:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    push ebx
    push esi
    push edi
    xor ecx, ecx ; сдвиг
.L:
    test eax, eax
    jz .end
    xor ebx, ebx ; счетчик 
    xor edx, edx
    div dword[ten]
.L1:
    cmp ebx, 29
    je .skip
    mov esi, ebx
    imul esi, 4
    mov edi, dword[mas1 + esi]
    imul edi, edx
    push eax
    push edx
    mov eax, edi
    xor edx, edx
    add esi, ecx
    div dword[ten]
    add dword[mas + esi], edx
    add dword[mas + esi + 4], eax
    mov eax, dword[mas + esi]
    xor edx, edx
    div dword[ten]
    mov dword[mas + esi], edx
    add dword[mas + esi + 4], eax
    pop edx
    pop eax
    inc ebx
    jmp .L1
.skip:
    add ecx, 4
    jmp .L
.end:
    xor ecx, ecx
.go1:
    cmp ecx, 29
    je .go1end
    mov edx, [mas + 4 * ecx]
    test edx, edx
    jz .p
    mov eax, ecx
.p:
    mov dword[mas + 4 * ecx], 0
    mov [mas1 + 4 * ecx], edx
    inc ecx
    jmp .go1
.go1end:
    pop edi
    pop esi
    pop ebx
    leave
    ret