
# cdb使用笔记


编译helloworld​
使用cl编译代码 并生成pdb调试信息文件
```bash
> vcvars64
> cl /Zi main.cc
```

## 开始调试

程序会自动停在启动处

```bash
> cdb main.exe
```

启动运行目标程序
```bash
0:00> g
```

单步命令 stepinto stepover stopout
```bash
0:000>t
0:000>p
0:000>gu
```

查找函数的符号
```bash
0:000> x main!test
00007ff6`85d2f750 main!test (void)
0:000>
0:000> x main!*test
00007ff6`85df774c main!_ldtest (double *)
00007ff6`85d38808 main!`anonymous namespace'::_Whitespace_bitmap_t::_Test (char)
00007ff6`85df7480 main!_dtest (double *)
00007ff6`85df7608 main!_fdtest (float *)
00007ff6`85d2f750 main!test (void)
00007ff6`85d38815 main!`anonymous-namespace'::_Whitespace_bitmap_t::_Test =  (inline caller) main!__std_get_string_size_without_trailing_whitespace+5
00007ff6`85d388a6 main!`anonymous-namespace'::_Whitespace_bitmap_t::_Test =  (inline caller) main!__std_system_error_allocate_message+6a
```

查看变量的值
```bash
0:000> x i
0000001d`860ffc30 i = 0n10
```

查看寄存器的值
```bash
0:000> r rax 
rax=00007ff685e38a00
0:000> r eax 
eax=85e38a00
0:000> r ax
ax=8a00
0:000> r al
ah=00
```

## 断点命令

```bash
0:000> bu main:test
0:000> bp 0040108c
0:000> bp main+5c
0:000> bp `source.c:31`
0:000> bl
 0 e 00007ff6`85d2f750     0001 (0001)  0:**** main!test
```

在 test 模块中以字符串"mem"开头的所有符号上设置断点

```bash
0:000> bm test!mem*
```

超过 函数 test 的开头 12 个字节。 对于前六个通过代码的传递，将忽略此断点，但在第七次通过代码时停止执行
```bash
0:000> bp test+0xb 7
```

在 RtlRaiseException 处设置断点，显示 eax 寄存器，显示 符号 MyVar 的值，然后继续

```bash
0:000> bp ntdll!RtlRaiseException "r eax; dt MyVar; g"
```


清除断点 清除所有断点
```bash
0:000> bc 0
0:000> bc *
```

## 检查 _FILE_OBJECT 模块中的 nt 数据类型
```bash
0:000> dt nt!_FILE_OBJECT
ntdll!_FILE_OBJECT
   +0x000 Type             : Int2B
   +0x002 Size             : Int2B
   +0x008 DeviceObject     : Ptr64 _DEVICE_OBJECT
   ... ...
   +0x080 Lock             : _KEVENT
   +0x098 Event            : _KEVENT
   +0x0b0 CompletionContext : Ptr64 _IO_COMPLETION_CONTEXT
   +0x0b8 IrpListLock      : Uint8B
   +0x0c0 IrpList          : _LIST_ENTRY
   +0x0d0 FileObjectExtension : Ptr64 Void
```

## 进程线程信息
查看进程中的所有线程列表
```bash
0:000> ~
```

查看线程0的堆栈信息
```bash
0:000> ~0s
main!main+0x58:
00007ff6`85d2f7e8 8b442424        mov     eax,dword ptr [rsp+24h] ss:0000001d`860ffc34=0000000a
0:000> k
Child-SP          RetAddr               Call Site
0000001d`860ffc10 00007ff6`85d7b0a0     main!main+0x58
(Inline Function) --------`--------     main!invoke_main+0x22
0000001d`860ffc50 00007ff9`468626bd     main!__scrt_common_main_seh+0x10c
0000001d`860ffc90 00007ff9`4838a9f8     KERNEL32!BaseThreadInitThunk+0x1d
0000001d`860ffcc0 00000000`00000000     ntdll!RtlUserThreadStart+0x28
```

推出调试和程序  推出并分离
```bash
0:000> q
quit:
... ...
0:000> qd
begine
test
hello world!
end
quit:
... ...
```

## 符号信息
设置符号存储路径 设置符号路径
```bash
0:000> .symfix c:\myCache
0:000> .sympath
Symbol search path is: srv*
Expanded Symbol search path is: cache*;SRV*https://msdl.microsoft.com/download/symbols

************* Path validation summary **************
Response                         Time (ms)     Location
Deferred                                       srv*
```


## 保存日志
 
 启动参数
[-logo LogFile]日志打开。 开始将信息记录到日志文件。 如果此文件已存在，则会将其覆盖。
```bash
> windbg main.exe -logo log.txt
```

## 参考资料
cdb官网信息 [ https://learn.microsoft.com/zh-cn/windows-hardware/drivers/debugger/debugging-using-cdb-and-ntsd ]

