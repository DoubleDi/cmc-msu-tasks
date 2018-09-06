%include "io.inc"
section .bss
s_l resd 1
f_l resd 1
s_n resd 1
f_n resd 1


section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_CHAR  s_l
    GET_DEC 4, s_n
    GET_CHAR  f_l
    GET_CHAR  f_l
    GET_DEC 4, f_n
    
    mov eax, dword[s_l]
    sub eax, dword[f_l]
    mov ecx, eax
    sar ecx, 100
    mov ebx, dword[f_l]
    sub ebx, dword[s_l]  
    mov edx, ebx
    sar edx, 100
    imul edx
    mov esi, eax
    neg esi
    mov eax, ebx
    imul ecx
    neg eax
    add esi, eax
    
    mov eax, dword[s_n]
    sub eax, dword[f_n]
    mov ecx, eax
    sar ecx, 100
    mov ebx, dword[f_n]
    sub ebx, dword[s_n]  
    mov edx, ebx
    sar edx, 100
    imul edx
    neg eax
    add esi, eax
    mov eax, ebx
    imul ecx
    neg eax
    add esi, eax
    
    PRINT_DEC 4, esi    
    xor eax, eax
    ret