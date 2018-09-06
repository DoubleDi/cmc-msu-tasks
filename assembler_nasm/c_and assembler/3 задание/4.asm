%include "io.inc"

section .data
flag dd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    call F
    xor eax, eax
    ret
F:
    push ebp
    mov ebp, esp
    GET_DEC 4, eax
    test eax, eax
    jz end
    cmp dword[flag], 1
    jne jump
    mov dword[flag], 0 
    PRINT_DEC 4, eax
    PRINT_CHAR ' '
    call F
    jmp end
jump:
    mov dword[flag], 1 
    push eax
    call F
    pop eax
    PRINT_DEC 4, eax
    PRINT_CHAR ' '
end:
    leave
    ret
  
    
    