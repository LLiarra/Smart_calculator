#include "../s21_smart_calc.h"

t_db_linked_list* s21_init_linked_list() {
  t_db_linked_list *tmp = (t_db_linked_list*)malloc(sizeof(t_db_linked_list));
  if (tmp == NULL) {
    exit(-1);
  }
  tmp->size = 0;
  tmp->head = NULL;
  tmp->tail = NULL;
  return tmp;
}

void s21_push_list(t_db_linked_list *list, t_data data) {
  t_node *tmp = (t_node*)malloc(sizeof(t_node));
  if (tmp == NULL) {
      exit(-1);
  }
  tmp->data = data;
  tmp->next = NULL;
  tmp->prev = list->tail;
  if (list->tail) {
      list->tail->next = tmp;
  }
  list->tail = tmp;
  if (list->head == NULL) {
      list->head = tmp;
  }
  list->size++;
}

t_node* s21_insert_node(t_db_linked_list** list, t_node* node, t_data data) {
  t_node* insert = NULL;
  if (node == NULL) {
    exit(-1);
  }
  insert = (t_node*)malloc(sizeof(t_node));
  insert->data = data;
  insert->prev = node->prev;
  insert->next = node;
  if (node->prev) {
    node->prev->next = insert;
    node->prev = insert;
  } else {
    node->prev = insert;
  }
  if (!node->prev) {
      (*list)->head = insert;
  }
  if (!node->next) {
      (*list)->tail = insert;
  }
  (*list)->size++;
  return insert;
}


t_stack* s21_init_stack(t_data data) {
  t_stack* new_stack = (t_stack*)malloc(sizeof(t_stack));
  if (new_stack == NULL) {
    exit(-1);
  }
  new_stack->data = data;
  new_stack->next = NULL;
  return new_stack;
}


void s21_push(t_stack** head, t_data data) {
  t_stack* temp = (t_stack*)malloc(sizeof(t_stack));
  if (temp == NULL) {
    exit(-1);
  }
  temp->next = *head;
  temp->data = data;
  *head = temp;
}

t_data s21_pop(t_stack** head) {
  t_stack* out;
  t_data res;
  if (head == NULL) {
    exit(-1);
  }
  out = *head;
  *head = (*head)->next;
  res = out->data;
  free(out);
  return res;
}

void s21_init_data(t_data* data) {
  data->sign = '\0';
  data->label = 0;
  data->func_uno = NULL;
  data->func = NULL;
}
