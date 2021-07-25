Build: 
'gcc crashing_main.cpp -lstdc++ -o main.o'

Generate coredump and backtrace: 
'gdb -return-child-result -batch -ex "run" -ex "bt" -ex "generate-core-file core.dump" -ex "quit" main.o'

Analyse coredump: 
'gdb main.o -c core.dump -ex "bt"'

Show local variables: info locals

Call a function: print foo.DoFoo() or call foo.DoFoo()

watch for changes on variables: watch <variable> (also foo.i for members)

Query infos about object: whatis, ptype
Query more details about child objects: set print object on

Call template function: print 'add<int>(int,int)'(a,3)
Explicit instanciation of the template "forces" creating of the function. Otherwise it is optimized out with -O3. Details can be analysed with disassemble.

disassemble:

```
Dump of assembler code for function main(int, char**):
   0x0000555555555080 <+0>:     endbr64
   0x0000555555555084 <+4>:     push   %rax
   0x0000555555555085 <+5>:     pop    %rax
   0x0000555555555086 <+6>:     mov    $0x3,%esi
   0x000055555555508b <+11>:    mov    $0x3,%edi
   0x0000555555555090 <+16>:    sub    $0x8,%rsp
   0x0000555555555094 <+20>:    callq  0x5555555551b0 <add<int>(int, int)>
   0x0000555555555099 <+25>:    movsd  0xf77(%rip),%xmm0        # 0x555555556018
   0x00005555555550a1 <+33>:    mov    $0x1,%edi
   0x00005555555550a6 <+38>:    lea    0xf57(%rip),%rsi        # 0x555555556004
   0x00005555555550ad <+45>:    mov    %eax,%edx
   0x00005555555550af <+47>:    mov    $0x1,%eax
   0x00005555555550b4 <+52>:    callq  0x555555555070 <__printf_chk@plt>
   0x00005555555550b9 <+57>:    callq  0x555555555060 <abort@plt>
```

```
(gdb) disassemble 'add<int>(int,int)'
Dump of assembler code for function add<int>(int, int):
=> 0x00005555555551df <+0>:     endbr64
   0x00005555555551e3 <+4>:     push   %rbp
   0x00005555555551e4 <+5>:     mov    %rsp,%rbp
   0x00005555555551e7 <+8>:     mov    %edi,-0x4(%rbp)
   0x00005555555551ea <+11>:    mov    %esi,-0x8(%rbp)
   0x00005555555551ed <+14>:    mov    -0x4(%rbp),%edx
   0x00005555555551f0 <+17>:    mov    -0x8(%rbp),%eax
   0x00005555555551f3 <+20>:    add    %edx,%eax
   0x00005555555551f5 <+22>:    pop    %rbp
   0x00005555555551f6 <+23>:    retq
End of assembler dump.
```

With bazel:

```
# Run target
bazel run //gdb:run --copt -g --run_under='gdbserver :1234'

gdb
target remote :1234
set follow-fork-mode child # Follows first fork --> if second fork needs to be debugged we need to adapt the script

```

Generate coredump by `ulimit -c unlimited`

