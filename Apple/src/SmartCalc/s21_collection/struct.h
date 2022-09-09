#ifndef SRC_SMARTCALC_S21_COLLECTION_STRUCT_H_
#define SRC_SMARTCALC_S21_COLLECTION_STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum s_label {
  NUMBER = 1,
  X = 2,
  SIGN = 3,
  FUNCTION = 4
} t_label;

typedef enum s_func_type {
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG,
  MOD
} t_func_type;


typedef struct s_data {
  long double number;
  char sign;
  t_label label;
  t_func_type func_type;
  long double (*func)(long double a, long double b);
  long double (*func_uno)(long double a);
} t_data;

typedef struct s_node {
  t_data data;
  struct s_node *next;
  struct s_node *prev;
} t_node;

typedef struct s_db_linked_list {
  size_t size;
  t_node *head;
  t_node *tail;
} t_db_linked_list;

typedef struct s_stack {
  t_data data;
  struct s_stack* next;
} t_stack;


#endif  //  SRC_SMARTCALC_S21_COLLECTION_STRUCT_H_
