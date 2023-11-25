asm=nasm
asmflags=-f elf64

cc=gcc
no_warnopts=-Wno-unused-variable -Wno-sizeof-pointer-memaccess

cflags=-Wall -Wextra -z execstack $(no_warnopts) -g

asm_dir=_asm
obj_dir=obj
src_dir=src
inc_dir=includes
lib_dir=libs

bin=main
cfile=$(src_dir)/main.c

thx_io=thx_io
thx_string=thx_string

__x64_io=x64_io
__x64_string=x64_string
__x64_syscall=x64_syscall


 
all: always clean $(bin)

$(bin): $(cfile) $(thx_io).o $(thx_string).o $(__x64_syscall).o
	$(cc) $(cflags)  $(cfile) $(lib_dir)/* $(obj_dir)/* -I $(inc_dir) -o $(bin)

$(thx_io).o: $(__x64_io).o $(thx_string).o
	$(cc) $(cflags) -c $(obj_dir)/*.o $(src_dir)/$(thx_io).c -I $(inc_dir) -o $(lib_dir)/$(thx_io).o

$(thx_string).o: $(__x64_string).o
	$(cc) $(cflags) -c $(obj_dir)/*.o $(src_dir)/$(thx_string).c -I $(inc_dir) -o $(lib_dir)/$(thx_string).o

$(__x64_io).o: 
	$(asm) $(asmflags) $(asm_dir)/x86_64/$(__x64_io).s -o $(obj_dir)/$(__x64_io).o

$(__x64_string).o: 
	$(asm) $(asmflags) $(asm_dir)/x86_64/$(__x64_string).s -o $(obj_dir)/$(__x64_string).o
	
$(__x64_syscall).o: 
	$(asm) $(asmflags) $(asm_dir)/x86_64/$(__x64_syscall).s -o $(obj_dir)/$(__x64_syscall).o

always:
	mkdir -p src
	mkdir -p obj


clean:
	rm -rf $(obj_dir)/*
	rm -rf $(bin)

