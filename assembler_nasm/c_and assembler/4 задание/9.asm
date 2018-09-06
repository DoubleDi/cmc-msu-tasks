%include "io.inc"
section .rodata
num db "%u ", 0
prin db "%d", 10, 0
prin1 db "%d ", 0

section .bss
n resd 1
x resd 1
n1 resd 1
n2 resd 1
nsave resd 1

section .data 
summ1 dd 0
summ2 dd 0
maxsumm1 dd -1
maxsumm2 dd 0

section .text
CEXTERN printf
CEXTERN scanf
CEXTERN malloc
CEXTERN free
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    and esp, -16
    sub esp, 32
    mov dword[esp], num
    mov dword[esp + 4], n
    call scanf
    xor esi, esi ; main counter
.L:
    cmp esi, [n]
    je .end
    inc esi    
    mov dword[esp + 4], n1
    mov dword[esp], num
    call scanf
    mov edx, 4
    mov eax, [n1]
    imul eax, eax
    mov [n2], eax
    imul eax, edx
    mov [esp], eax
    call malloc
    mov [esp + 8], eax
    xor edi, edi ; counter
    mov dword[summ1], 0
    mov dword[summ2], 0
    mov dword[esp], num
.L1:
    cmp edi, [n2]
    je .skip 
    mov dword[esp + 4], x
    call scanf
    mov eax, [x]
    mov edx, [esp + 8]
    mov [edx + 4 * edi], eax
    inc edi  
    mov ecx, [n1]
    inc ecx
    mov eax, edi
    xor edx, edx
    div ecx
    cmp edx, 1
    jne .pop
    mov eax, [x]
    add [summ1], eax 
    adc dword[summ2], 0
.pop:
    jmp .L1
.skip:
    mov eax, [summ1]
    mov edx, [summ2]
    cmp edx, [maxsumm2]
    jl .noswitch
    je .check
    jmp .cont
.check:
    cmp eax, [maxsumm1]
    jle .noswitch
.cont:
    mov [maxsumm1], eax
    mov [maxsumm2], edx
    mov edx, [esp + 8]
    mov eax, [esp + 12]
    mov [esp + 12], edx
    mov ecx, [n1]
    mov [nsave], ecx
    mov [esp], eax
    call free
.noswitch:
    jmp .L
.end: 
    mov ebx, [esp + 12]
    mov ecx, [nsave]
    mov [n1], ecx
    imul ecx, ecx
    mov [n2], ecx
    imul ecx, 4
    mov [nsave], ecx
    xor esi, esi
.almost:
    mov ecx, 4
    imul ecx, esi
    inc esi
    mov edi, [ebx + ecx]
    mov dword[esp], prin1
    mov [esp + 4], edi
    mov eax, esi
    xor edx, edx
    div dword[n1]
    cmp edx, 0
    jne .noenter
    mov dword[esp], prin
.noenter:
    call printf
    cmp esi,[n2]
    je .endend
    jmp .almost
.endend:    
    mov ebx, [esp + 12]
    mov [esp], ebx
    call free
    mov esp, ebp
    xor eax, eax
    ret