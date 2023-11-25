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

; Converts an ascii value to an integer.
ascizz_to_dec:
	push rbp,
	mov rbp, rsp

	push rbx
	push rsi
	push r8
	push rax

	xor rsi, rsi
	xor r8, r8
	mov rbx, 10

	cmp byte[rdi] , '-'
	je .signed

	jmp .loop

.loop:
	movzx rax, byte[rdi]
	inc rdi 
	sub al, '0'

	cmp al, 0
	jle .end

	imul rsi, rbx
	add rsi, rax
	jmp .loop

.signed:
	inc rdi
	mov r8, 1
	jmp .loop

.signum:
	neg rax
	jmp .return

.end:
	pop rax
	mov rax, rsi

	cmp r8, 1
	je .signum
.return
	pop r8
	pop rsi
	pop rbx

	mov rsp, rbp
	pop rbp
	ret
