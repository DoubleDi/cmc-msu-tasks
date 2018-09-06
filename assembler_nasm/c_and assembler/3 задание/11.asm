%include "io.inc"
section .data
flag dd 1
section .bss
num resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, num
    mov edx, 0
L1:
    cmp edx, dword[num]
    je finish
    inc edx
    GET_UDEC 4, eax
    push edx    
    push eax
    call F
    pop eax
    pop edx
    jmp L1
finish:
    xor eax, eax
    ret
F:
    push ebp
    mov ebp, esp
    mov ecx, [ebp + 8]
    xor eax, eax
    xor edx, edx
L:    
    test ecx, ecx
    jz end
    mov ebx, ecx
    shr ecx, 1
    and ebx, 1
    cmp dword[flag], 1
    je nch
    mov dword[flag], 1
    add eax, ebx
    jmp L
 nch:
    mov dword[flag], 0
    add edx, ebx
    jmp L
 end:
    sub eax, edx
    cmp eax, 0
    jge gogo
    dec eax
    not eax    
gogo:
    cmp eax, 10
    jb endend
    push eax
    call F
    leave
    ret
endend:
    cmp eax, 9
    jne go1
    PRINT_STRING "YES"
    NEWLINE
    jmp endendend 
 go1:
    cmp eax, 6
    jne go2
    PRINT_STRING "YES"
    NEWLINE
    jmp endendend 
 go2:
    cmp eax, 3
    jne go3
    PRINT_STRING "YES"
    NEWLINE
    jmp endendend 
 go3:
    cmp eax, 0
    jne go
    PRINT_STRING "YES"
    NEWLINE
    jmp endendend 
 go:
    PRINT_STRING "NO"
    NEWLINE
endendend:
    leave
    ret
    
    
    
     
    