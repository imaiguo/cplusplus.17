

# 汇编编译调试

汇编代码为masm格式，在dos模式环境, win10环境通过使用DosBox模拟

## 准备环境
mount C: D:\workspace\clangapp\asm\masm\dos

## 编译调试
> masm src\sec4\first.asm
> link first
> debug first.exe

## debug常用命令

R 查看、改变寄存器的内容
D 查看内存中的内容
E 改写内存中的内容
U 将内存中的机器指令翻译成为汇编指令
T 执行一条机器指令
A 以汇编指令的格式在内存中写入一条机器指令

