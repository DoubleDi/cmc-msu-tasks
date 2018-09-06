%include "io.inc"

section .bss
a11 resd 1
a12 resd 1
a21 resd 1
a22 resd 1
b1 resd 1
b2 resd 1

section .text
global CMAIN
CMAIN:
    GET_UDEC 4, a11
    GET_UDEC 4, a12
    GET_UDEC 4, a21
    GET_UDEC 4, a22
    GET_UDEC 4, b1
    GET_UDEC 4, b2
    mov eax, dword[a11]
    and eax, dword[a12]
    or eax, dword[a22]
    mov ebx, dword[a22]
    and ebx, dword[b1]
    mov ecx, dword[a12]
    and ecx, dword[b2]
    xor ebx, ecx
    and ebx, dword[a11]
    xor eax, ebx
    and eax, dword[a21]
    xor eax, dword[a22]
    
    mov edx, eax
    
    mov eax, dword[a21]
    and eax, dword[a22]
    or eax, dword[a12]
    mov ebx, dword[a12]
    and ebx, dword[b2]
    mov ecx, dword[a22]
    and ecx, dword[b1]
    xor ebx, ecx
    and ebx, dword[a21]
    xor eax, ebx
    and eax, dword[a11]
    xor eax, dword[a12]
    
    mov ecx, eax
    
    mov eax, dword[a11]
    and eax, dword[b1]
    or eax, dword[b2]
    and eax, dword[a21]
    xor eax, dword[b2]
    and edx, eax
    
    mov eax, dword[a21]
    and eax, dword[b2]
    or eax, dword[b1]
    and eax, dword[a11]
    xor eax, dword[b1]
    and ecx, eax
    
    or edx, ecx  
    
    
    mov eax, dword[a12]
    and eax, edx
    xor eax, dword[b1]
    and eax, dword[a11]
    
    mov ebx, dword[a22]
    and ebx, edx
    xor ebx, dword[b2]
    and ebx, dword[a21]
    or eax, ebx
    PRINT_UDEC 4, eax
    PRINT_CHAR " "
    PRINT_UDEC 4, edx
    xor eax, eax
    ret