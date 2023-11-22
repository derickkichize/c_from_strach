global __x64_memset


;memset - fill memory with a constant byte
__x64_memset:
	push rbp
	mov rbp, rsp

	push rdi
	push rsi
	push rdx
	push rcx

	xor rcx, rcx

.loop:
	mov byte[rdi], sil
	inc rdi
	inc rcx

	cmp rcx, rdx
	je .end

	jmp .loop

.end:
	pop rcx
	pop rdx
	pop rsi
	pop rdx

	mov rsp, rbp
	pop rbp
	ret

