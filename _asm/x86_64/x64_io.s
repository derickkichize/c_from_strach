%include "_asm/x86_64/inc/asciiz.inc.s"

global __x64_itoa
global __x64_atoi
global __x64_atof
global __x64_atoh

;;
; __x64_atoh: converts ascii string in to a base 16 decimal.    
;
; Parameters: 
;	rdi: (char*) - ascii_number
; Returns:
;	rax: (int)   -  int
;;
__x64_atoh:
	push rbp
	mov rbp, rsp

	push rsi
	push rbx
	push rax

	xor rsi, rsi
	mov rbx, 10h

	cmp byte [rdi], '0'
	je .check_hex_prefix

.loop:
	movzx rax, byte[rdi]
	inc rdi

	cmp al, 'a'
	jge .hex_digits

	cmp al, '0'
	jge .dec_digits

	cmp al, 0
	je .done

	jmp .loop

.dec_digits:
	sub al, '0'
	jmp .continue

.hex_digits:
	sub al, 87
	jmp .continue

.continue:
	imul rsi, rbx
	add rsi, rax
	jmp .loop

.check_hex_prefix:
	inc rdi	

	cmp byte [rdi], 'x'
	je  .ignore_hex_prefix

	dec rdi
	jmp .loop

.ignore_hex_prefix:
	inc rdi
	jmp .loop

.done:
	pop rax
	pop rbx

	mov rax, rsi
	pop rsi

	mov rsp, rbp
	pop rbp
	ret


	

;;
; atof converts ascii string in to a float.    
;
; Parameters: 
;
;	rdi: (char*)   - buffer
;
; Returns:
;	xmm0: (double) -  float
;;
__x64_atof:
	push rbp
	mov rbp, rsp

	push rax
	push rcx
	push rdi
	push rsi
	push r8
	
	xor rax, rax
	xor r8, r8
	mov rcx, 10

	cmp byte[rdi], '-'
	je .signed

.loop_integer:
	movzx rbx, byte[rdi]
	sub rbx, 48
	imul rcx
	add rax, rbx

	inc rdi
	cmp byte [rdi], 46
	jne .loop_integer

	cvtsi2sd xmm1, rax
	inc rdi
	xor rax, rax
	mov rsi, 1

.loop_faction:
	movzx rbx, byte[rdi]
	sub rbx, 48
	imul rcx
	imul rsi, rcx
	add rax, rbx

	inc rdi
	cmp byte[rdi], 57
	jg .done_fraction
	cmp byte [rdi], 48
	jl .done_fraction
	jmp .loop_faction

.done_fraction:
	cvtsi2sd xmm0, rax
	cvtsi2sd xmm2, rsi
	divsd xmm0, xmm2
	addsd xmm0, xmm1
	test r8, r8
	jz .done

	mov rcx, -1
	cvtsi2sd xmm1, rcx
	mulsd xmm0, xmm1
	jmp .done

.done:
	pop r8
	pop rsi
	pop rdi
	pop rcx
	pop rax

	mov rsp, rbp
	pop rbp
	ret
.signed:
	inc rdi
	inc r8
	jmp .loop_integer

;;
; itoa converts an integer to a string. 
;
; Parameters: 
;	rdi: (void*)	    - integer.
;	rsi: (char*)	    - buffer.	
;	rdx: (unsignet int) - convertion_base.
;
; Returns:
;	void
;;
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
;;
; atoi converts an ascii value to an integer
;
; Parameters: 
;	rdi: (char*) - ascii_string.
; Returns:
;	rax: (int)
;;
__x64_atoi:
	push rbp
	mov rbp, rsp

	call ascizz_to_dec

	mov rsp, rbp
	pop rbp
	ret
