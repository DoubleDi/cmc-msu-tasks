%include "io.inc"
section .data
ten dd 10
section .bss
k resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_UDEC 4, ecx
    GET_UDEC 4, k
    mov eax, 0
go:
    push ecx
    call F
    pop ecx    
    cmp eax, 1
    je end
    inc ecx
    jmp go
end:    
    PRINT_UDEC 4, ecx
    xor eax, eax
    ret
F: 
    push ebp
    xor ecx, ecx
    mov ebp, esp
    mov eax, [ebp + 8]
    L:    
    xor edx, edx
    cmp eax, 0
    jne Lend
    mov esi, eax
    mov eax, ecx
    mul dword[ten]
    mov ecx, eax
    mov eax, esi
    div ebx
    add ecx, edx
    jmp L
Lend:

    xor ecx, ecx
numStart:
    xor edx, edx
    test eax, eax
    jz numEnd
    div dword[k]
    inc ecx
    jmp numStart
numEnd:
    add ecx, 1
    shr ecx, 1
    mov eax, [ebp + 8]
    mov ebx, 1  
    xor esi, esi
    xor edi, edi 
ls: 
    xor edx, edx
    test eax, eax
    jz aa
    div dword[k]
    cmp ebx, ecx
    ja go1
    add esi, edx
    inc ebx
    jmp ls
go1: 
    add edi, edx
    inc ebx
    jmp ls
aa:
    xor eax,eax
    cmp esi, edi 
    je oo 
    jmp endend
oo:
    add eax, 1
endend:
    leave
    ret