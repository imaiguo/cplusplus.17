;p107 计算ffff:0006 单元中数乘以123
; 遇到'loop 0012'时,用P命令自动重复执行 2条重复命令直至 cx=0
; 遇到'loop 0012'时,用G命令可以在指定位置0012停下， '-g 0012'

assume cs:code
code segment
	mov ax,0ffffh
	mov ds,ax
	mov bx,6              ;以上，设置ds:bx指向ffff:6

	mov al,[bx]
	mov ah,0              ;以上，设置(al)=((ds*16)+(bx)),(ah)=0。

	mov dx,0              ;累加寄存器清0
	
	mov cx,123              ;循环123次
  s:add dx,ax
	loop s                ;以上累加计算(ax)*123

	mov ax,4c00h          ;程序返回
	int 21h

code ends
end