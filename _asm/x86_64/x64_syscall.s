global __x64_syswrite

segment .data
	SYS_WRITE equ 0x1
	STDOUT    equ 0x1

segment .text

__x64_syswrite:
	push rbp
	mov rbp, rsp

	push rax
	push rdi
	push rsi
	push rdx

	mov rax, SYS_WRITE

	syscall

	pop rdx
	pop rsi
	pop rdi
	pop rax

	mov rsp, rbp
	pop rbp
	ret
	


