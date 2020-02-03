【抽象语法树】

在这个题目中，你将完整的实现抽象语法树（包括数据结构的定义、语法树的生成等）。首先，请下载我们提供的代码包：

http://staff.ustc.edu.cn/~bjhua/mooc/ast.zip 

代码的运行方式是：
首先生成语法分析器：

  $ bison exp.y

然后生成编译器：

  $ gcc main.c exp.tab.c ast.c

最后使用编译器编译某个源文件：

  $ a.exe <test.txt

在提供的代码里，我们已经提供了抽象语法树的定义、若干操作、及由bison生成语法树的代码框架。你的任务是：
    进一步完善该代码框架，使其能够分析减法、除法和括号表达式；（你需要修改语法树的定义，修改bison源文件及其它代码）
    重新研究第一次作业中的从Sum编译到Stack的小型编译器代码，把他移植到目前的代码框架中，这样你的编译器能够从文本文件中读入程序，然后输出编译的结果。（注意，你必须扩展你的编译器，让他能够支持减法和除法。）