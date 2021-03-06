# C--语言的代码生成器
在这个作业中，要求你给C--语言实现代码生成器，生成栈式计算机的指令代码。
C--语言的语法
C--语言的语法和上一次作业中的相同，为了方便引用，这里重复给出如下：

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

栈式计算机
栈式计算机的指令见课程的讲义，需要特别指出的是，讲义中所给出的指令不足以编译C--，所以需要你自己设计并添加必须的指令。
任务
首先下载我们提供的代码框架：

http://staff.ustc.edu.cn/~bjhua/mooc/codegen.zip

首先编译该代码：

  $ make

然后运行给定的测试例：

  $ ./a.out < test.txt

对给定的测试例，在屏幕上打印了所生成的栈计算机的代码；并且生成了名为stack.exe的可执行程序，如果运行该程序的话：

  $ ./stack.exe

将输出：

  88
  true

代码当中已经给出的是模块和任务是包括：

    栈计算机的数据结构定义模块：stack-machine.h.c。你的任务是根据自己的研究和判断，增加必要的新的指令（结合下面的任务2）；
    从C--编译到栈计算机的代码生成模块：gen-stack.h.c；你的任务是将这部分代码补充完整（TODO的部分）；
    从栈计算机编译到x86汇编代码并生成可执行文件的模块：stack2x86.h.c。（这部分是选做，不做统一要求。


## 注释：该程序在x86-64架构下不能使用。只能在i386架构下使用。可以使用docker或者VM来创建i386并删除a.out和*.o文件然后用make重新编译。
