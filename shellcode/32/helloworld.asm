section .data
msg db "hello world",0x0a

section .text
global _start

_start:
mov eax,4
mov ebx,1
mov ecx,msg
mov edx,14
int 0x80 ;write(1,msg,14)
mov eax,1
mov ebx,0
int 0x80 ;exit(0)
