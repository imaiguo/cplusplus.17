; P118 可以导致dos卡死的代码 向0:26h内存单元中写入0
assume cs:code
code segment
	mov ax,0
	mov ds,ax	
	mov ds:[26h],ax

	mov ax,4c00h
	int 21h

code ends
end 