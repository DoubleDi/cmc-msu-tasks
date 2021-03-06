section .text
extern comparecounter
extern swapcounter

global compare ; cравнение 2х элементов    
compare:
    push ebp
    mov ebp, esp
    xor eax, eax
    finit
    fld qword[ebp + 16]; b
    fld qword[ebp + 8]; a
    fucomi st1
    setb al
    fstp st0
    fstp st0
    inc dword[comparecounter]
    leave
    ret

global swap ; перемещение 2х элементов
swap:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]; &a
    mov ecx, [ebp + 12]; &b
    finit
    fld qword[eax]; a
    fld qword[edx]; b
    fstp qword[eax]; a = b
    fstp qword[edx]; b = a
    inc dword[swapcounter]    
    leave
    ret
    
global timestamp ; таймер
timestamp:
    rdtsc
    ret
