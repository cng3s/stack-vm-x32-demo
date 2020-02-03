/**
 * 在这部分中，你将使用图转移算法手工实现一个小型的词法分析器。
 * 分析器的输入：存储在文本文件中的字符序列，字符取自ASCII字符集。文件中可能包括四种记号：关键字if、符合C语言标准的标识符、空格符、回车符\n。
 * 分析器的输出：打印出所识别的标识符的种类、及行号、列号信息。
 【示例】对于下面的文本文件：
ifx if iif       if
iff    if
 你的输出应该是：
 ID(ifx) (1, 1)
 IF        (1, 4)
 ID(iif)  (1, 8)
 IF       (1, 13)
 ID(iff) (2, 1)
 IF       (2, 8)
*/

#include <stdio.h>

enum        kind {IF, ID};
static int  program_pos = 0;              // 当前词法分析器读取文件位置
static int  program_col = 1;              // 记录文件列数
static int  program_line = 1;             // 记录文件行数
int         program_len = 0;              // 记录文件总长度
char        program[1000];                // 存放文件内容的数组
char        lexeme[10];                   // 存放词素
int         lexeme_len = 0;               // 存放词素长度

void compile();
void s0(char c);
void s1(char c);
void s2(enum kind k);
void s3(char c);
void s4(char c);
int  is_skip_character(char c);            // 判断是否是'\n', '\t', ' '字符
int  handle_skip_character(char c);        // 处理'\n','\t', ' '字符
void rollback();
void print_lexeme(enum kind k);
void compile_error();

int main() {
    FILE *fp = fopen("program.txt", "r+");
    if (NULL == fp) {
        printf("file can't open\n");
        return -1;
    }
    
    for (; !feof(fp); ++program_len)
        program[program_len] = fgetc(fp);
    fclose(fp);

    compile();

    return 0;
}


void compile()
{
    for (; program_pos < program_len - 1;) {
        if (!handle_skip_character(program[program_pos]))
            s0(program[program_pos]);
    }
}

void s0(char c)
{
    lexeme[lexeme_len ++] = c;
    char nextc = program[++ program_pos];
    ++ program_col;
    if ( (c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z') || c == '_' ) {
        if (c == 'i')
            s3(nextc);
        else
            s1(nextc);
    }
    else
        compile_error();
}

void s1(char c)
{
    if (is_skip_character(c)) {
        s2(ID);
        handle_skip_character(c);
        return;
    }
    ++ program_pos;
    ++ program_col;
    lexeme[lexeme_len ++] = c;
    char nextc = program[program_pos];
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '_')
        s1(nextc);
    else
        s2(ID);
}

void s2(enum kind k)
{
    print_lexeme(k);
    lexeme_len = 0;  // 惰性删除词素
    // rollback();
}

void s3(char c)
{
    lexeme[lexeme_len ++] = c;
    char nextc = program[++ program_pos];
    ++ program_col;
    if (c == 'f')
        s4(nextc);
    else
        s1(nextc);
}

void s4(char c)
{
    if (is_skip_character(c)) {
        s2(IF);
        handle_skip_character(c);
        return;
    }
    lexeme[lexeme_len ++] = c;
    char nextc = program[++ program_pos];
    ++ program_col;
    s1(nextc);
}

void print_lexeme(enum kind k)
{
    if (k == ID) {
        printf("ID(");
        for (int i = 0; i < lexeme_len; i ++)
            printf("%c", lexeme[i]);
        printf(")\t\t\t(%d, %d)\n", program_line, program_col - lexeme_len);
    }
    else if (k == IF) {
        printf("IF\t\t\t(%d,%d)\n",
            program_line, program_col - 2);
    }
}

int is_skip_character(char c)
{
    return (c == EOF || c == '\n' || c == '\t' || c == ' ') ? 1 : 0;
}

int handle_skip_character(char c)
{
    if (c == EOF)         // -1 == EOF( end of file )    
        return 1;
    else if (c == '\n') {
        program_col = 1;
        program_pos ++;
        program_line ++;
        return 1;
    }
    else if (c == '\t') {
        program_col += 4;
        program_pos ++;
        return 1;
    }
    else if (c == ' ') {
        program_col ++;
        program_pos ++;
        return 1;
    }
    return 0;
}

void compile_error() 
{
    printf("Invalid lexeme");
}

// program_pos回退函数
void rollback()
{
    if (program_pos > 0) {
        -- program_pos;
        -- program_col;
    }
}