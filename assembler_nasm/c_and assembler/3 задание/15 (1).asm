%include "io.inc"

global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
	push ebp
	mov ebp, esp
	GET_UDEC 4, esi; N
	GET_UDEC 4, edi; K
	xor eax, eax

	.while_start:
	cmp eax, 1
	je .while_end
		; PRINT_CHAR '@'
		push edi
		push esi
		call happiness
		pop esi
		pop edi
		inc esi
		jmp .while_start
	.while_end:

	dec esi
	PRINT_UDEC 4, esi
	NEWLINE
	mov esp, ebp
	pop ebp	
	xor eax, eax
	ret

happiness:
	push ebp
	mov ebp, esp
	push ebx
	push esi
	; [ebp + 8]; number
	; [ebp + 12]; base

	mov eax, [ebp + 8]
	xor ecx, ecx
	.while1_start:
	cmp eax, 0
	je .while1_end
		xor edx, edx
		div dword[ebp + 12]		
		push edx
		inc ecx
		jmp .while1_start
	.while1_end:

	mov eax, ecx
	mov esi, ecx
	xor edx, edx
	mov ebx, 2
	div ebx
	mov ebx, eax
;	add ebx, edx; частное + остаток =>частное с округлением вверх

	xor eax, eax
	xor ecx, ecx
	.while2_start:
	cmp ecx, ebx
	je .while2_end
		pop edx
		add eax, edx
		inc ecx
		jmp .while2_start
	.while2_end:

	.while3_start:
	cmp ecx, esi
	je .while3_end
		pop edx
		sub eax, edx
		inc ecx
		jmp .while3_start
	.while3_end:

	cmp eax, 0
	jne .no
		mov eax, 1
		jmp .happiness_end
	.no:
		mov eax, 0

	.happiness_end:
	pop esi
	pop ebx
	mov esp, ebp
	pop ebp
	ret