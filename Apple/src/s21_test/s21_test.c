#include "../SmartCalc/s21_smart_calc.h"
#include "../SmartCalc/s21_collection/struct.h"
#include <check.h>

START_TEST(s21_calc_one) {
  char str[] = "5.0 + 345.1";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 350.1;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_one_val) {
  char str[] = "5.345";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 5.345;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_one_val_negate) {
  char str[] = " 0 - 5.345";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = -5.345;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_one_val_unary) {
  char str[] = " 0 + 5.345";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 5.345;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_one_val_sum) {
  char str[] = " 0 + 5.345 + ( 245 + 12 ) + 134 + 234 + ( 235 + ( 123.4 + ( 1234.0 + 1 ) ) )";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 2223.745;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_one_val_sub) {
  char str[] = " 12234567.1 - 232455353.2 ";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = -220220786.1;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_one_val_mul) {
  char str[] = " ( 0 - 1 ) * 2 ";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = -2;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_one_val_del) {
  char str[] = "( ( 5 / 1 ) / 2 ) / 5";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 0.5;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_one_val_pow_two) {
  char str[] = "( 0 - 1 ) ^ 2";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 1;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_one_val_pow_two_neg) {
  char str[] = "0 - ( 1  ^ 2 )";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = -1;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_one_val_pow_three) {
  char str[] = "( 0 - 1 ) ^ 3";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = -1;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_sin) {
  char str[] = "sin ( 5 * 4 - 2 )";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = -0.750987;
  ck_assert_ldouble_eq_tol(res, test, 1e-06);
  free(list);
} END_TEST

START_TEST(s21_calc_cos) {
  char str[] = "cos ( 5.42 / 4.12 - 2.123 )";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 0.691331;
  ck_assert_ldouble_eq_tol(res, test, 1e-06);
  free(list);
} END_TEST

START_TEST(s21_calc_acos) {
  char str[] = "acos ( 5.42 / 9.12 ) / 15";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 0.062293;
  ck_assert_ldouble_eq_tol(res, test, 1e-06);
  free(list);
} END_TEST

START_TEST(s21_calc_asin) {
  char str[] = "asin ( 1.42 / 9.12 ) * 5 - 2";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = -1.218311;
  ck_assert_ldouble_eq_tol(res, test, 1e-06);
  free(list);
} END_TEST

START_TEST(s21_calc_tan) {
  char str[] = " 5 * ( 5 - tan ( 5 * 0.2 ) )";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 17.212961;
  ck_assert_ldouble_eq_tol(res, test, 1e-06);
  free(list);
} END_TEST

START_TEST(s21_calc_atan) {
  char str[] = " 0 - ( 5 - atan ( 5 / 11.2 ) )";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = -4.580120;
  ck_assert_ldouble_eq_tol(res, test, 1e-06);
  free(list);
} END_TEST

START_TEST(s21_calc_sqrt) {
  char str[] = " 0 - ( 5 + sqrt ( 9.123 ) )";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = -8.020430;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_ln) {
  char str[] = "10 * ln ( 345 / 2 ) ";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 51.503972;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_log) {
  char str[] = "log ( 1 / 2.234 ) ^ 2 ";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 0.121859;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_mod) {
  char str[] = "5 mod 9 * ( 1 / 2.234 ) ^ 2 ";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 1.001852;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_calc_oper) {
  char str[] = "7 - 6 + 5 / 9 - 1";
  t_db_linked_list* list = s21_string_processing(str);
  long double res = s21_calculate(list);
  long double test = 0.555556;
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
  free(list);
} END_TEST

START_TEST(s21_graph_one_x) {
  char str[] = "X";
  long double value = 0.01;
  for (long double i = 0.01; i <= 15.05; i++) {
    long double result = s21_set_graph(str, value);
    ck_assert_double_eq_tol(result, value, 1e-06);
  }
} END_TEST

START_TEST(s21_graph_x) {
  char str[] = "X";
  for (long value = 0.01; value <= 15.05; value++) {
    long double result = s21_set_graph(str, value);
    ck_assert_double_eq_tol(result, value, 1e-06);
  }
} END_TEST

START_TEST(s21_calc_smart) {
  char str[] = "7 - 6 + 5 / 9 - 1";
  long double test = 0.555556;
  long double res = s21_smart_calc(str);
  ck_assert_ldouble_eq_tol(res, test, 1e-6);
} END_TEST

START_TEST(s21_valid_bracket) {
  char str[] = " ( ( 7 - 6 + 5 ) / 9 - 1";
  int res = s21_is_not_valid(str);
  int test = 1;
  ck_assert_int_eq(res, test);
} END_TEST


START_TEST(s21_valid_operation) {
  char str[] = " ( ( -  +  ) ) /";
  int res = s21_is_not_valid(str);
  int test = 1;
  ck_assert_int_eq(res, test);
} END_TEST

START_TEST(s21_valid_operation_x) {
  char str[] = " ( ( X -  +  ) ) /";
  int res = s21_is_not_valid(str);
  int test = 1;
  ck_assert_int_eq(res, test);
} END_TEST


Suite* s21_smart_suite() {
  Suite* s;

  TCase *tc_calc, *tc_graph, *tc_valid;
  s = suite_create("s21_smart_calc");

  tc_calc = tcase_create("calc");
  tcase_add_test(tc_calc, s21_calc_one);
  tcase_add_test(tc_calc, s21_calc_one_val);
  tcase_add_test(tc_calc, s21_calc_one_val_negate);
  tcase_add_test(tc_calc, s21_calc_one_val_unary);
  tcase_add_test(tc_calc, s21_calc_one_val_sum);
  tcase_add_test(tc_calc, s21_calc_one_val_sub);
  tcase_add_test(tc_calc, s21_calc_one_val_mul);
  tcase_add_test(tc_calc, s21_calc_one_val_del);
  tcase_add_test(tc_calc, s21_calc_one_val_pow_two);
  tcase_add_test(tc_calc, s21_calc_one_val_pow_two_neg);
  tcase_add_test(tc_calc, s21_calc_one_val_pow_three);
  tcase_add_test(tc_calc, s21_calc_sin);
  tcase_add_test(tc_calc, s21_calc_cos);
  tcase_add_test(tc_calc, s21_calc_asin);
  tcase_add_test(tc_calc, s21_calc_acos);
  tcase_add_test(tc_calc, s21_calc_tan);
  tcase_add_test(tc_calc, s21_calc_atan);
  tcase_add_test(tc_calc, s21_calc_sqrt);
  tcase_add_test(tc_calc, s21_calc_ln);
  tcase_add_test(tc_calc, s21_calc_log);
  tcase_add_test(tc_calc, s21_calc_mod);
  tcase_add_test(tc_calc, s21_calc_oper);
  tcase_add_test(tc_calc, s21_calc_smart);
  suite_add_tcase(s, tc_calc);

  tc_graph = tcase_create("graph");
  tcase_add_test(tc_graph, s21_graph_one_x);
  tcase_add_test(tc_graph, s21_graph_x);
  suite_add_tcase(s, tc_graph);

  tc_valid = tcase_create("valid");
  tcase_add_test(tc_valid, s21_valid_bracket);
  tcase_add_test(tc_valid, s21_valid_operation);
  tcase_add_test(tc_valid, s21_valid_operation_x);
  suite_add_tcase(s, tc_valid);

  return s;
}

int main() {
  int no_failed = 0;
  Suite* s;
  SRunner* runner;

  s = s21_smart_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

