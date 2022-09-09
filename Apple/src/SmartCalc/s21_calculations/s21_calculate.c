#include "../s21_smart_calc.h"

static t_node* s21_delete_after_calculate(t_node* first_num, t_node* sign) {
  t_node* after = sign->next;
  t_node* before;
  if (after) {
    if (!first_num->prev) {
      after->prev = NULL;
    } else {
      before = first_num->prev;
      before->next = after;
      after->prev = before;
    }
  }
  if (sign->data.label == SIGN || (sign->data.label == FUNCTION && sign->data.func_type == 9)) {
    free(first_num->next);
  }
    free(first_num);
    free(sign);
  return after;
}

static t_node* s21_operator_process(t_db_linked_list* list, t_node* current) {
  long double result = 0.0;
  int res_modif = 0;
  t_data sign_data = current->data;
    if (sign_data.label == SIGN || (sign_data.label == FUNCTION && sign_data.func_type == 9)) {
      if ((current->prev != NULL && current->prev->prev != NULL) &&
      (current->prev->data.label == NUMBER && current->prev->prev->data.label == NUMBER)) {
       result = sign_data.func(current->prev->prev->data.number, current->prev->data.number);
       current = s21_delete_after_calculate(current->prev->prev, current);
       res_modif = 1;
      }
    } else if (sign_data.label == FUNCTION) {
      if (current->prev && current->prev->data.label == NUMBER) {
      result = sign_data.func_uno(current->prev->data.number);
      current = s21_delete_after_calculate(current->prev, current);
      res_modif = 1;
      }
    }
  t_data new_data;
  s21_init_data(&new_data);
  new_data.number = result;
  new_data.label = NUMBER;
  if (current && res_modif) {
    current = s21_insert_node(&list, current, new_data);
  } else {
    current = (t_node*)calloc(1, sizeof(t_node));
    current->data = new_data;
  }
  return current;
}

long double s21_calculate(t_db_linked_list* list) {
  t_node* current = list->head;
  long double res = 0;

  while (current) {
    if (current->data.label == SIGN || current->data.label == FUNCTION) {
      current = s21_operator_process(list, current);
    }
    if (!current->next) {
        break;
      }
    current = current->next;
  }
  if (current) {
    res = current->data.number;
    free(current);
  }
  return res;
}
