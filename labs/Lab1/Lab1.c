/*
* 题目：（本题目是一个动手实践类题目，需要具备C语言和数据结构基础。）
* 在课程中，我们讨论一个小型的从表达式语言Sum到栈计算机Stack的编译器，
* 在附件中，你能找到对该编译器的一个C语言实现，但这个实现是不完整的，请你
* 把缺少的代码补充完整（不超过10行代码）。
* 加分题：实现常量折叠优化。
* */
#include <stdio.h>
#include <stdlib.h>


#define TODO()                                  \
  do{                                                           \
    printf ("\nAdd your code here: file \"%s\", line %d\n",     \
            __FILE__, __LINE__);                                \
  }while(0)


///////////////////////////////////////////////
// Data structures for the Sum language.
enum Exp_Kind_t {EXP_INT, EXP_SUM};

struct Exp_t
{
  enum Exp_Kind_t kind;
};


struct Exp_Int
{
  enum Exp_Kind_t kind;
  int i;
};


struct Exp_Sum
{
  enum Exp_Kind_t kind;
  struct Exp_t *left;
  struct Exp_t *right;
};


// "constructors"
struct Exp_t *Exp_Int_new (int i)
{
  struct Exp_Int *p = malloc (sizeof(*p));
  p->kind = EXP_INT;
  p->i = i;
  return (struct Exp_t *)p;  // 为什么这里可以转换为(struct Exp_t *)类型?
}


struct Exp_t *Exp_Sum_new (struct Exp_t *left, struct Exp_t *right)
{
  struct Exp_Sum *p = malloc (sizeof(*p));
  p->kind = EXP_SUM;
  p->left = left;
  p->right = right;
  return (struct Exp_t *)p;
}


// "printer"
void Exp_print (struct Exp_t *exp)
{
  switch (exp->kind){
  case EXP_INT:{
    struct Exp_Int *p = (struct Exp_Int *)exp;
    printf ("%d", p->i);
    break;
  }

  case EXP_SUM:{
    struct Exp_Sum *p = (struct Exp_Sum *)exp;
    Exp_print (p->left);
    printf ("+");
    Exp_print (p->right);
    break;
  }

  default:
    break;
  }
}


//////////////////////////////////////////////
// Data structures for the Stack language.
enum Stack_Kind_t {STACK_ADD, STACK_PUSH};
struct Stack_t
{
  enum Stack_Kind_t kind;
};


struct Stack_Add
{
  enum Stack_Kind_t kind;
};


struct Stack_Push
{
  enum Stack_Kind_t kind;
  int i;
};


// "constructors"
struct Stack_t *Stack_Add_new ()
{
  struct Stack_Add *p = malloc (sizeof(*p));
  p->kind = STACK_ADD;
  return (struct Stack_t *)p;
}


struct Stack_t *Stack_Push_new (int i)
{
  struct Stack_Push *p = malloc (sizeof(*p));
  p->kind = STACK_PUSH;
  p->i = i;
  return (struct Stack_t *)p;
}


/// instruction list
struct List_t
{
  struct Stack_t *instr;
  struct List_t *next;
};



struct List_t *List_new (struct Stack_t *instr, struct List_t *next)
{
  struct List_t *p = malloc (sizeof (*p));
  p->instr = instr;
  p->next = next;
  return p;
}



// "printer"
void List_reverse_print (struct List_t *list)
{
  //TODO();
  if (list->next != NULL)
    List_reverse_print(list->next);
  if (list->instr->kind == STACK_ADD)
    printf("\nadd");
  else {
    struct Stack_Push *p = (struct Stack_Push *)list->instr;
    printf("\npush %d", p->i);
  }
}


//////////////////////////////////////////////////
// a compiler from Sum to Stack
struct List_t *all = 0;



void emit (struct Stack_t *instr)
{
  all = List_new (instr, all);
}


void compile (struct Exp_t *exp)
{
  switch (exp->kind){
  case EXP_INT:{
    struct Exp_Int *p = (struct Exp_Int *)exp;
    emit (Stack_Push_new (p->i));
    break;
  }

  case EXP_SUM:{
    //TODO();
    struct Exp_Sum *p = (struct Exp_Sum *)exp;
    // 常量折叠优化
    if (p->left->kind == EXP_INT && p->right->kind == EXP_INT) {
      struct Exp_Int *pleft = (struct Exp_Int *)p->left, *pright = (struct Exp_Int *)p->right;
      emit (Stack_Push_new(pleft->i + pright->i));
    }
    else {
      compile(p->left);
      compile(p->right);
      emit (Stack_Add_new ());
    }
    break;
  }
  default:
    break;
  }
}



//////////////////////////////////////////////////
// program entry
int main()
{
  printf("Compile starting\n");
  // build an expression tree:
  //            +
  //           / \
  //          +   4
  //         / \
  //        2   3
  struct Exp_t *exp = Exp_Sum_new (Exp_Sum_new(Exp_Int_new (2)
                                               , Exp_Int_new (3))
                                   , Exp_Int_new (4));

  // print out this tree:
  printf ("the expression is:\n");

  Exp_print (exp);

  // compile this tree to Stack machine instructions
  compile (exp);

  // print out the generated Stack instructons:
  List_reverse_print (all);

  printf("\nCompile finished\n");
  return 0;
}
