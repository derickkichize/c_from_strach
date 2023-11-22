%include "_asm/x86_64/inc/asciiz.inc.s"

global __x64_itoa
global __x64_putsbuf
global __x64_putcbuf
global __x64_putstr

;itoa convert an integer to a string.
__x64_itoa:
	push rbp
	mov rbp, rsp

	mov rax, rdi
	mov rdi, rsi
	mov rbx, rdx

	call ito_asciiz
	mov rdi, rax

	mov rsp, rbp
	pop rbp
	ret

;putsbuf join strings into a buffer
__x64_putsbuf:
	push rbp
	mov rbp, rsp

	push rax
.loop:
	cmp byte [rdi], 0
	jz .join

	inc rdi
	jmp .loop

.join:
	mov al, byte [rsi]
	mov byte [rdi], al
	inc rdi
	inc rsi

	cmp al, 0
	jz .end
	inc rcx

	jmp .join

.end:
	mov byte [rdi], 0

	pop rax
	pop rdi

	mov rax, rcx

	mov rsp, rbp

	pop rbp
	ret

;putcbuf join characters into a buffer
__x64_putcbuf:
	push rbp
	mov rbp, rsp

	push rdi
	
	cmp byte [rdi], 0
	je .empty_str
.loop:
	inc rdi
	cmp byte [rdi], 0
	jnz .loop

.empty_str:
	mov byte [rdi], sil

	mov rsp, rbp
	pop rbp
	ret

;putstr put string into a buffer.
__x64_putstr:
	push rbp
	mov rbp, rsp

	mov rbx, rdi
	xor rcx, rcx
.loop:
	cmp byte[rbx], 0
	jz .print
	inc rbx
	inc rcx
	jmp .loop

.print:
	mov rsi, rdi
	mov rdx, rcx
	mov rdi, 0x1
	mov rax, 0x1
	syscall

	mov rsp, rbp
	pop rbp
	ret
