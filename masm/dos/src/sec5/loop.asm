; P100 计算2^12的结果
;

assume cs:code
code segment
	mov ax,2
	mov cx,11
     s:	add ax,ax
	loop s

	mov ax,4c00h
	int 21h
code ends
end
