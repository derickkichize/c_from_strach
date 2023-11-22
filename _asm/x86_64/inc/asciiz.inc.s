;Print unsigned integer
ito_asciiz:
	push rbp
	mov rbp, rsp

	push rdx

	cmp rbx, 16
	je .hex_format

	jmp .continue

.hex_format:
	mov byte [rdi], '0'
	inc rdi
	mov byte [rdi], 'x'
	inc rdi

.continue:
	or rax, rax
	jns .buf_assoc

	mov byte [rdi], '-'
	inc rdi
	neg rax

.buf_assoc:
	pop rdx
	call usig_ito_asciiz

	mov rsp, rbp
	pop rbp

	ret

;Print unsigned integer
usig_ito_asciiz:
	push rbp
	mov rbp, rsp

	push rax
	push rbx
	push rcx
	push rdx

	cmp rbx, 2
	jge .setup

	mov rbx, 10

.setup:
	xor rcx, rcx
	xor r8, r8
.start:
	xor rdx, rdx

	div rbx
	push rdx
	inc rcx
	inc r8

	cmp rax, 0
	jnz .start

.loop:
	pop rdx
	add rdx, 30h

	cmp rdx, '9'
	jng .buf_assoc

	add rdx, 39

.buf_assoc:
	mov byte [rdi], dl	
	inc rdi
	loop .loop
	
	pop rdx
	pop rcx
	pop rbx
	pop rax

	mov rsp, rbp
	pop rbp
	ret
