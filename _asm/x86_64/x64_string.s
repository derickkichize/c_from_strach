global __x64_memset
global __x64_memcats
global __x64_memcatc

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

;;
; memcats - Concat a string into a buffer.
;
; Parameters: 
;	rdi: (void*) - dst_buffer.
;	rsi: (void*) - src_buffer.
; Returns:
;	void
;;
__x64_memcats:
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

;;
; memcatc - Contact a character into a buffer.
;
; Parameters: 
;	rdi: (void*) - dst_buffer.
;	rsi: (char)  - char.
; Returns:
;	void
;;
__x64_memcatc:
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
