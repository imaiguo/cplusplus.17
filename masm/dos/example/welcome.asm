assume cs:codesg,ds:datasg,ss:stacksg
; ----------------------------------------------------------------
datasg segment

        db 'welcome to masm  '    ;ds:[si]

        db 00000010B           ;绿色
        db 00100100B           ;绿底红色
        db 01110001B           ;白底蓝色
datasg ends

stacksg segment
        db 128 dup(0)   ;128个内存栈
stacksg ends


codesg segment

start:  mov ax,datasg
        mov ds,ax       ;声明数据段地址

        mov ax,stacksg
        mov ss,ax
        mov sp,128      ;初始化栈

        mov ax,0B800H
        mov es,ax       ;显示缓冲区

        mov si,0
        mov di,160*10+30*2
        mov bx,16
        mov dx,0

        mov cx,3


showm:  push bx
        push cx
        push si
        push di

        mov cx,16
        mov dh,ds:[bx]

showr:   mov dl,ds:[si]
        mov es:[di],dx
        add di,2
        inc si
        loop showr
        pop di
        pop si
        pop cx
        pop bx
        add di,160
        inc bx
        loop showm

        mov ax,4c00H
        int 21H
 


codesg ends
end start
