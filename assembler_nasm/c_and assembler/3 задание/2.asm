%include "io.inc"

section .data
x dd 3

section .text
global CMAIN
CMAIN:
  ;  push ebp
    mov ebp, esp; for correct debugging
    GET_UDEC 4, eax
    push eax
    call F
    PRINT_UDEC 4, eax
   ; add esp, 4
     pop eax
     ;mov esp, ebp
     ;pop ebp
    xor eax, eax
    ret
    
F:  
    push ebp
    mov ebp, esp 
    mov eax, [ebp + 8]
    mov ecx, 0
    test eax, eax
    jz end 
    xor edx, edx
    div dword[x]
    cmp edx, 1
    jne none
    mov ecx, edx    
none:
    push ecx
    push eax
    call F
    pop edx
    pop ecx
    add eax, ecx
end: 
    mov esp, ebp
    pop ebp
    ret