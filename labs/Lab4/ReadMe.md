在这个题目中，要求你完成一个针对算术表达式的语法分析器。该算术表达式的上下文无关文法是：

E -> E + T
   | E - T
   | T

T -> T * F
   | T / F
   | F

F -> num
   | (E)

请下载我们提供的C代码框架，并把其中缺少的部分补充完整。
代码下载地址：
http://staff.ustc.edu.cn/~bjhua/mooc/exp.zip