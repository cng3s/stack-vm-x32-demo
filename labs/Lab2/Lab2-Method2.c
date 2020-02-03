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
#include <stdlib.h>

/* Data Structure of token and token infomation */
enum kind {IF, ID};
struct token {
    enum kind   k;
    char        *lexeme;
    int         row, col;
};

/* Data Structure and Functions of Linked List Start */

struct list_header {
    struct list_item    *next;
};

struct list_item {
    struct token        *tok;
    struct list_item    *next;
};

int list_item_insert(struct list_header *ls, struct list_item *item);
struct list_item * list_item_structure(enum kind k);
void list_print(struct list_item *ls);

/* Data Structure and Functions of Linked List End */

/* Program Infomation and Functions Start */

char program[1000];
int  program_len = 0;
int  program_col = 1;
int  program_row = 1;
int  program_pos = 0;

// 创建一个词素时用来指向开始位置的指针和一个自由指针
char *lexeme;
int  lexeme_len = 0;

struct list_header *token_list;

int  read_program();
void compile();
int  handle_skip_character(char c);
int  is_skip_character(char c);
void s0(char c);
void s1(char c);
void s2(enum kind k);
void s3(char c);
void s4(char c);

/* Program Infomation and Functions End */

int main()
{
    
    FILE *fp = fopen("program.txt", "r+");
    if (NULL == fp) {
        printf("File Can't Open!\n");
        return -1;
    }

    for (; !feof(fp); ++ program_len)
        program[program_len] = fgetc(fp);
    
    fclose(fp);
    
    compile();
    list_print(token_list->next);

    return 0;
}

void compile()
{
    for (; program_pos < program_len - 1;) {
        if (!handle_skip_character(program[program_pos])) {
            lexeme = (char *)malloc(sizeof(char) * 10);
            lexeme_len = 0;
            s0(program[program_pos]);
        }
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
}

void s1(char c)
{
    if (is_skip_character(c)) {
        s2(ID);
        handle_skip_character(c);
        return;
    }
    char nextc = program[++ program_pos];
    ++ program_col;
    lexeme[lexeme_len ++] = c;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '_')
        s1(nextc);
    else
        s2(ID);
}

void s2(enum kind k)
{
    lexeme[lexeme_len] = '\0';
    list_item_insert(token_list, list_item_structure(k));
}

void s3(char c)
{
    lexeme[lexeme_len++] = c;
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

int handle_skip_character(char c)
{
    if (c == EOF)
        return 1;
    else if (c == '\n') {
        program_col = 1;
        program_pos ++;
        program_row ++;
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

int is_skip_character(char c)
{
    return (c == EOF || c == '\n' || c == '\t' || c == ' ') ? 1 : 0;
}

struct list_item * list_item_structure(enum kind k)
{
    struct list_item *item = (struct list_item *)malloc(sizeof(struct list_item));
    item->tok = (struct token *)malloc(sizeof(struct token));
    item->tok->lexeme = lexeme;
    item->tok->k = k;
    item->tok->row = program_row;
    item->tok->col = program_col - lexeme_len;
    item->next = NULL;
    return item;
}

int list_item_insert(struct list_header *ls, struct list_item *item)
{
    if (item == NULL)
        return 0;
    if (ls == NULL) {
        struct list_header *header = (struct list_header *)malloc(sizeof(header));
        header->next = item;
        token_list = header;
    }
    else {
        item->next = ls->next;
        ls->next = item;
    }
    return 1;
}

void list_print(struct list_item *ls) {
    if (ls->next != NULL)
        list_print(ls->next);
    if (ls->tok->k == IF)
        printf("IF\t\t\t(%d,%d)\n", ls->tok->row, ls->tok->col);
    else 
        printf("ID(%s)\t\t\t(%d,%d)\n", ls->tok->lexeme, ls->tok->row, ls->tok->col);

}