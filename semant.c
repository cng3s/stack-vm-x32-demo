#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"
#include "todo.h"

//////////////////////////////////////
// the symbol table
List_t table = 0;

// lookup an "id" in the symbol table.
// return "type" on success; and -1 for failure
Type_t Table_lookup (char *id)
{
  List_t p = table;
  while (p){
    Dec_t d = (Dec_t)p->data;
    if (strcmp(d->id, id)==0)
      return d->type;
    p = p->next;
  }
  return -1;
}

void Print_exp_type(enum Exp_Kind_t kind)
{
  switch (kind) {
  case EXP_INT:       printf("INT");          break;
  case EXP_TRUE:      printf("TRUE");         break;
  case EXP_FALSE:     printf("FALSE");        break;
  case EXP_ID:        printf("ID");           break;
  case EXP_ADD:       printf("ADD");          break;
  case EXP_SUB:       printf("SUB");          break;
  case EXP_TIMES:     printf("TIMES");        break;
  case EXP_DIVIDE:    printf("DIVIDE");       break;
  case EXP_AND:       printf("AND");          break;
  case EXP_OR:        printf("OR");           break;
  default:            printf("Unknown type"); break;
  }
}

Type_t Type_error(Type_t t1, Type_t t2)
{
  printf ("Exp_type_error: type ");
  Print_exp_type(t1);
  printf (" and ");
  Print_exp_type(t2);
  printf(" dismatch\n");
  return TYPE_UNKNOW;
}


void Table_insert (Dec_t dec)
{
  if (Table_lookup (dec->id) != -1){
    fprintf (stderr, "Error: the variable "
	     "\"%s\" has been declared!\n", dec->id);
    exit (0);
  }
  table = List_new (dec, table);
  return;
}

//////////////////////////////////////////
// dec
void check_dec(Dec_t d)
{
  Table_insert (d);
}

void check_decs(List_t decs)
{
  while (decs){
    Dec_t d = (Dec_t)decs->data;
    check_dec(d);
    decs = decs->next;
  }
  return;
}

////////////////////////////////////////
// exp

// Your job:
Type_t check_exp (Exp_t exp)
{
  //TODO();
  switch (exp->kind) {
  case EXP_INT:     return TYPE_INT;
  case EXP_TRUE:    return TYPE_BOOL;
  case EXP_FALSE:   return TYPE_BOOL;
  case EXP_DIVIDE:
  case EXP_TIMES:
  case EXP_SUB:
  case EXP_ADD:{
                 Exp_Add p = (Exp_Add) exp;
                 Type_t t1 = check_exp (p->left);
                 Type_t t2 = check_exp (p->right);
                if (t1 != TYPE_INT || t2 != TYPE_INT)
                  return Type_error(t1, t2);
                else
                  return TYPE_INT;
               }
  case EXP_OR:
  case EXP_AND:{
                 Exp_And p = (Exp_And) exp;
                 Type_t t1 = check_exp (p->left);
                 Type_t t2 = check_exp (p->right);
                if (t1 != TYPE_BOOL || t2 != TYPE_BOOL)
                  return Type_error(t1, t2);
                else
                  return TYPE_BOOL;
               }
  case EXP_ID:{
                Exp_Id p = (Exp_Id) exp;
                Type_t t = Table_lookup (p->id);
                if (t == -1)
                  printf ("id not found in table");
                return t;
              }
  }

  return 0;
}

////////////////////////////////////////
// stm

// Your job:
void check_stm (Stm_t stm)
{
  //TODO();
  switch (stm->kind) {
  case STM_ASSIGN:{
                    Stm_Assign s = (Stm_Assign) stm;
                    Type_t t1 = Table_lookup (s->id);
                    Type_t t2 = check_exp (s->exp);
                    if (t1 != t2)
                      Type_error (t1, t2);
                    break;
                  }
  case STM_PRINTI:{
                    Stm_Printi s = (Stm_Printi) stm;
                    Type_t t = check_exp (s->exp);
                    if (t != TYPE_INT)
                      Type_error(TYPE_INT, t);
                    break;
                  }
  case STM_PRINTB:{
                    Stm_Printb s = (Stm_Printb) stm;
                    Type_t t = check_exp (s->exp);
                    if (t != TYPE_BOOL)
                      Type_error(TYPE_BOOL, t);
                    break;
                  }
  }

}

void check_stms(List_t stms)
{
  while (stms){
    Stm_t s = (Stm_t)stms->data;
    check_stm(s);
    stms = stms->next;
  }
  return;
  //TODO();
}


void Semant_check(Prog_t prog)
{
  // create table
  check_decs(prog->decs);
  // check stm
  check_stms(prog->stms);
  return;
}
