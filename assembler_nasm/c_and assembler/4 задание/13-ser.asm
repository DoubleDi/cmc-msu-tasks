%include "io.inc"
section .rodata
    input_t db `%d`, 0
    output_t db `%d\n`, 0
 
section .text
 
CEXTERN scanf
CEXTERN fprintf
CEXTERN get_stdout
CEXTERN malloc
CEXTERN free
 
global CMAIN
CMAIN:
    mov ebp, esp
    and esp, -16
    sub esp, 128
   
    mov dword[esp], input_t
    mov dword[esp+4], ebp
    sub dword[esp+4], 4
    call scanf
   
    mov ecx, dword[ebp-4]
    mov dword[esp], ecx
    shl dword[esp], 2
    call malloc
    mov esi, eax
    mov ecx, dword[ebp-4]
   
    mov dword[esp], input_t
    mov dword[esp+4], esi
.loop:
    mov edi, ecx
    call scanf
    mov ecx, edi
    add dword[esp+4], 4
    loop .loop
   
    call get_stdout
   
    mov dword[esp], esi
    mov ecx, dword[ebp-4]
    mov dword[esp+4], ecx
    mov dword[esp+8], fprintf
    mov dword[esp+12], 2
    mov dword[esp+16], eax ; stdout
    mov dword[esp+20], output_t
    call apply
   
    mov esp, ebp
    xor eax, eax
    ret
 
; void apply(int *arr, size_t len, void (*fn)(), int n, ...)
stupid_apply:
apply:
    push ebp
    mov ebp, esp
    push esi
    push edi
    sub esp, 4
   
    mov ecx, dword[ebp+20] ; n
    shr ecx, 2
    inc ecx
    shl ecx, 4
    sub esp, ecx ; allocate enough space
   
    mov ecx, dword[ebp+20] ; n
.load_args:
    dec ecx
    mov eax, dword[ebp+24 + 4*ecx]
    mov dword[esp + 4*ecx], eax
    test ecx, ecx
    jnz .load_args
   
    xor ecx, ecx
    mov esi, dword[ebp+8] ; &cur
    mov edi, esp ; &last_arg
    mov eax, dword[ebp+20] ; n
    shl eax, 2
    add edi, eax
.loop:
    cmp ecx, dword[ebp+12] ; len
    jge .end_loop
    mov eax, dword[esi]
    mov dword[edi], eax
    mov dword[ebp-4], ecx
    call dword[ebp+16]
    mov ecx, dword[ebp-4]
    inc ecx
    add esi, 4
    jmp .loop
.end_loop:
    mov esp, ebp
    sub esp, 8
    pop edi
    pop esi
    leave
    ret