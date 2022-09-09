#ifndef SRC_SMARTCALC_S21_COLLECTION_S21_LINKED_LIST_H_
#define SRC_SMARTCALC_S21_COLLECTION_S21_LINKED_LIST_H_

#include "struct.h"

//  stack
t_stack* s21_init_stack(t_data data);
void s21_push(t_stack** head, t_data data);
t_data s21_pop(t_stack** head);
int s21_is_empty(t_stack* head);

//  list
t_db_linked_list* s21_init_linked_list();
void s21_push_list(t_db_linked_list *list, t_data data);
t_node* s21_insert_node(t_db_linked_list** list, t_node* node, t_data data);
void s21_print_elem(t_db_linked_list* list);
void s21_init_data(t_data* data);

#endif  // SRC_SMARTCALC_S21_COLLECTION_S21_LINKED_LIST_H_
