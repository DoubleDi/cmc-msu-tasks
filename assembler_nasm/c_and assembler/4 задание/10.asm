%include "io.inc"
section .rodata
sca1 db "%ld %ld", 0
sca2 db "%ld", 0
prin db "%ld %ld", 10, 0

section .bss
mas resd 31
a resd 1
b resd 1
c resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp
    and esp, -16
    sub esp, 128
.L:
    
    xor eax, eax
    ret