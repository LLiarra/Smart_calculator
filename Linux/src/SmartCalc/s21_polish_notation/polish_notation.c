#include "../s21_smart_calc.h"

#include <math.h>

static long double s21_sum(long double a, long double b) {
  return a + b;
}

static long double s21_sub(long double a, long double b) {
  return a - b;
}

static long double s21_mul(long double a, long double b) {
  return a * b;
}

static long double s21_del(long double a, long double b) {
  return a / b;
}

static long double s21_pow(long double a, long double b) {
  return powl(a, b);
}

static long double s21_mod(long double a, long double b) {
  return fmodl(a, b);
}

static long double s21_cos(long double a) {
  return cosl(a);
}

static long double s21_sin(long double a) {
  return sinl(a);
}

static long double s21_tan(long double a) {
  return tanl(a);
}

static long double s21_acos(long double a) {
  return acosl(a);
}

static long double s21_asin(long double a) {
  return asinl(a);
}

static long double s21_atan(long double a) {
  return atanl(a);
}

static long double s21_sqrt(long double a) {
  return sqrtl(a);
}

static long double s21_ln(long double a) {
  return logl(a);
}

static long double s21_log(long double a) {
  return log10l(a);
}

static void s21_change_sign(t_data* data) {
  switch (data->sign) {
    case '+':
      data->func = s21_sum;
      break;
    case '-':
      data->func = s21_sub;
      break;
    case '*':
      data->func = s21_mul;
      break;
    case '/':
      data->func = s21_del;
      break;
    case '^':
      data->func = s21_pow;
      break;
    default:
    break;
  }
}

static void s21_change_func(t_data* data) {
  switch (data->func_type) {
    case COS :
      data->func_uno = s21_cos;
      break;
    case SIN :
      data->func_uno = s21_sin;
      break;
    case TAN :
      data->func_uno = s21_tan;
      break;
    case ACOS :
      data->func_uno = s21_acos;
      break;
    case ASIN :
      data->func_uno = s21_asin;
      break;
    case ATAN :
      data->func_uno = s21_atan;
      break;
    case SQRT :
      data->func_uno = s21_sqrt;
      break;
    case LN :
      data->func_uno = s21_ln;
      break;
    case LOG :
      data->func_uno = s21_log;
      break;
    case MOD :
      data->func = s21_mod;
      break;
  }
}

static int s21_is_number(const char* str) {
  return str[0] >= '0' && str[0] <= '9';
}

static int s21_is_x(const char* str) {
  return str[0] == 'x' || str[0] == 'X';
}

static int s21_is_func(char* str, t_data* data) {
  char* arr_func[] = {"cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log", "mod"};
  int i = 0;
  int result = 0;
  while (i != 10) {
    int res = strcmp(str, arr_func[i]);
    if (!res) {
      result = 1;
      data->func_type = i;
      break;
    }
    i++;
  }
  return result;
}

static int s21_get_priority(t_data data) {
  int res = 0;
  if (data.sign == ')') {
    res = -1;
  } else if (data.sign == '(') {
    res = 1;
  } else if (data.sign == '-' || data.sign == '+') {
    res = 2;
  } else if (data.sign == '*' || data.sign == '/' || data.func_type == MOD) {
    res = 3;
  } else if (data.sign == '^') {
    res = 4;
  } else if (data.label == FUNCTION) {
    res = 5;
  }
  return res;
}

static int s21_is_left_associative(char sign) {
  return !(sign == '^');
}

static void s21_flush_stack(t_db_linked_list* list, t_stack* stack) {
  while (stack != NULL) {
    t_data elem = s21_pop(&stack);
    s21_push_list(list, elem);
  }
}

static void s21_flush_until_parentheses(t_db_linked_list* list, t_stack** stack) {
  t_data elem = s21_pop(stack);
  while (elem.sign != '(') {
    s21_push_list(list, elem);
    elem = s21_pop(stack);
  }
  if (*stack) {
    elem = s21_pop(stack);
    if (elem.label == FUNCTION) {
      s21_push_list(list, elem);
    } else {
      s21_push(stack, elem);
    }
  }
}

static void s21_check_priority(t_db_linked_list* list, t_stack** stack, t_data new_data) {
  t_data stack_data;
  if (*stack != NULL) {
    stack_data = s21_pop(stack);
  int res_stack = s21_get_priority(stack_data);
  int res_new = s21_get_priority(new_data);
  if (res_new == 1) {
    s21_push(stack, stack_data);
    s21_push(stack, new_data);
  } else if (res_new == -1) {
      if (stack_data.sign != '(') {
         s21_push_list(list, stack_data);
         s21_flush_until_parentheses(list, stack);
  }
  } else if (res_stack >= res_new && s21_is_left_associative(new_data.sign)) {
    s21_push_list(list, stack_data);
    int flag = 0;
    while (*stack) {
      stack_data = s21_pop(stack);
      res_stack = s21_get_priority(stack_data);
      if (res_stack >= res_new) {
        s21_push_list(list, stack_data);
      } else {
        s21_push(stack, stack_data);
        s21_push(stack, new_data);
        flag = 1;
        break;
      }
    }
    if (!flag) {
      s21_push(stack, new_data);
    }
  } else {
    s21_push(stack, stack_data);
    s21_push(stack, new_data);
  }
  }
}

static void s21_sorting_station(t_db_linked_list** list, t_stack** stack, t_data data) {
  if (data.label == NUMBER || data.label == X) {
    if (*list == NULL) {
      *list = s21_init_linked_list();
      s21_push_list(*list, data);
    } else {
      s21_push_list(*list, data);
    }
  } else {
    if (*stack == NULL) {
      *stack = s21_init_stack(data);
    } else {
      s21_check_priority(*list, stack, data);
    }
  }
}

t_db_linked_list* s21_string_processing(char* work_str) {
  char* rest = work_str;
  char* token;
  t_db_linked_list* list_head = NULL;
  t_stack* stack_head = NULL;
  t_data data;
  s21_init_data(&data);

  while ((token = __strtok_r(rest, " ", &rest))) {

    if (s21_is_number(token)) {
      char* save;
      data.label = NUMBER;
      long double value = atof(token);
      data.number = value;
    } else if (s21_is_func(token, &data)) {
      data.label = FUNCTION;
      s21_change_func(&data);
    } else if (s21_is_x(token)) {
      data.label = X;
    } else {
      data.label = SIGN;
      data.sign = token[0];
      s21_change_sign(&data);
    }
    s21_sorting_station(&list_head, &stack_head, data);
    memset(&data, 0, sizeof(data));
  }
  if (stack_head != NULL) {
    s21_flush_stack(list_head, stack_head);
    stack_head = NULL;
  }
  return list_head;
}
