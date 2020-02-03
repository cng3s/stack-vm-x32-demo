# C--语言的代码生成器
C--语言实现代码生成器，生成栈式计算机的指令代码。
C--语言的语法
prog   -> { decs stms }  
decs   -> dec decs  
        |  
dec    -> type id ;  
type   -> int  
        | bool  
stms   -> stm stms  
        |  
stm    -> id = exp ;  
        | printi(exp) ;  
        | printb(exp) ;  
exp    -> intnum  
        | true  
        | false  
        | id  
        | (exp)  
        | exp + exp  
        | exp - exp  
        | exp * exp  
        | exp / exp  
        | exp && exp  
        | exp || exp  

首先编译该代码：

  $ make

然后运行给定的测试例：

  $ ./a.out < test.txt

对给定的测试例，在屏幕上打印了所生成的栈计算机的代码；并且生成了名为stack.exe的可执行程序，如果运行该程序的话：

  $ ./stack.exe

将输出：

  88
  true

## 注释：该程序在x86-64架构下不能使用。只能在i386架构下使用。可以使用docker或者VM来创建i386并删除a.out和*.o文件然后用make重新编译。
