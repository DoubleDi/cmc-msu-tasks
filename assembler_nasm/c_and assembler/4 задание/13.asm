%include "io.inc"
section .rodata
prin db "%d", 10, 0
sca db "%d", 0
section .text
CEXTERN fprintf
CEXTERN malloc
CEXTERN get_stdout
CEXTERN scanf
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    and esp, -16
    sub esp, 128
    mov dword[esp], sca
    mov [esp + 4], ebp
    sub dword[esp + 4], 4
    call scanf
    mov edx, [ebp - 4]
    imul edx, 2
    mov dword[esp], edx
    call malloc
    mov edx, dword[ebp - 4]
    mov dword[esp], sca
    mov edi, eax
    mov dword[esp + 4], edi
.L:
    mov [esp + 20], edx
    call scanf
    mov edx, [esp + 20]
    add dword[esp + 4], 4
    dec edx
    cmp edx, 0
    jne .L
    call get_stdout
    mov edx, dword[ebp - 4]
    mov dword[esp + 20], prin
    mov [esp + 16], eax
    mov dword[esp + 12], 2
    mov dword[esp + 8], fprintf
    mov [esp + 4], edx
    mov [esp], edi
    call apply
    mov esp, ebp
    xor eax, eax
    ret
    
apply:
    xor edx, edx
    push ebp
    mov ebp, esp
    sub esp, 12
    mov eax, [ebp + 20]
    mov ecx, 2
    div ecx
    mov ecx, eax
    inc ecx
    imul ecx, 4
    sub esp, ecx
    mov ecx, [ebp + 20]
.L1:
    dec ecx
    mov eax, [ebp + 4 * ecx  +  24]
    mov [esp + 4 * ecx], eax
    cmp ecx, 0
    jne .L1
    mov eax, [ebp + 20]
    mov edi, [ebp + 8]
    mov esi, esp
    shl eax, 2
    add esi, eax
    xor edx, edx
.switch:
    cmp edx, [ebp + 12]
    jge .end
    mov ecx, [edi]
    mov [esi], ecx
    mov [ebp - 4], edx
    call dword[ebp +16]
    mov edx, dword[ebp - 4]
    inc edx
    add edi, 4
    jmp .switch
.end:
    leave
    ret