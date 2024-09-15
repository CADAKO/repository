#include "s21_test.h"

START_TEST(calc_test_simple_addition) {
  char* infixExpression = "2 + 2";
  double expected = 4;
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_simple_subtraction) {
  char* infixExpression = "10 - 5";
  double expected = 5;
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_simple_multiplication) {
  char* infixExpression = "3 * 4";
  double expected = 12;
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_simple_division) {
  char* infixExpression = "15 / 3";
  double expected = 5;
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_complex_expression) {
  char* infixExpression = "(2 + 3) * 4 - 6 / 2";
  double expected = 17;
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_power) {
  char* infixExpression = "2 ^ 3";
  double expected = 8;
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_sin) {
  char* infixExpression = "s(1)";
  double expected = sin(1);
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_cos) {
  char* infixExpression = "c(1)";
  double expected = cos(1);
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_acos) {
  char* infixExpression = "C(1)";
  double expected = acos(1);
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_atan) {
  char* infixExpression = "T(1)";
  double expected = atan(1);
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_asin) {
  char* infixExpression = "S(1)";
  double expected = asin(1);
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_log10) {
  char* infixExpression = "L(1)";
  double expected = log10(1);
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_mod) {
  char* infixExpression = "3%2";
  double expected = fmod(3, 2);
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_tan) {
  char* infixExpression = "t(1)";
  double expected = tan(1);
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_log) {
  char* infixExpression = "l(10)";
  double expected = log(10);
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_minus) {
  char* infixExpression = "~1+3";
  double expected = 2;
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_sqrt) {
  char* infixExpression = "Q(16)";
  double expected = sqrt(16);
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_negative_number) {
  char* infixExpression = "~3 + 2";
  double expected = -1;
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_positive_number) {
  char* infixExpression = "#3 - 2";
  double expected = 1;
  double result = calc(infixExpression);
  ck_assert_double_eq(result, expected);
}
END_TEST

START_TEST(calc_test_inf_expression) {
  char* infixExpression = "10 / 0";
  double result = calc(infixExpression);
  ck_assert(isinf(result));
}
END_TEST

START_TEST(calc_test_brackets_positive_1) {
  char* infixExpression = "(10 / 0)";
  int result = calcbracketinfix(infixExpression);
  int expected = 0;
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(calc_test_brackets_positive_2) {
  char* infixExpression = "(3)";
  int result = calcbracketinfix(infixExpression);
  int expected = 0;
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(calc_test_brackets_positive_3) {
  char* infixExpression = "(10 / 0)+s(1)";
  int result = calcbracketinfix(infixExpression);
  int expected = 0;
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(calc_test_brackets_negative_1) {
  char* infixExpression = ")";
  int result = calcbracketinfix(infixExpression);
  int expected = 1;
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(calc_test_brackets_negative_2) {
  char* infixExpression = "(10 / 0))";
  int result = calcbracketinfix(infixExpression);
  int expected = 1;
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(calc_test_brackets_negative_3) {
  char* infixExpression = "(10 / 0)+(";
  int result = calcbracketinfix(infixExpression);
  int expected = 1;
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(calc_test_brackets_negative_4) {
  char* infixExpression = "()";
  int result = calcbracketinfix(infixExpression);
  int expected = 1;
  ck_assert_int_eq(result, expected);
}
END_TEST

Suite* test_calc(void) {
  Suite* suite = suite_create("Calculator");
  TCase* tc_calc = tcase_create("Core");

  tcase_add_test(tc_calc, calc_test_simple_addition);
  tcase_add_test(tc_calc, calc_test_simple_subtraction);
  tcase_add_test(tc_calc, calc_test_simple_multiplication);
  tcase_add_test(tc_calc, calc_test_simple_division);
  tcase_add_test(tc_calc, calc_test_complex_expression);
  tcase_add_test(tc_calc, calc_test_power);
  tcase_add_test(tc_calc, calc_test_sin);
  tcase_add_test(tc_calc, calc_test_cos);
  tcase_add_test(tc_calc, calc_test_acos);
  tcase_add_test(tc_calc, calc_test_atan);
  tcase_add_test(tc_calc, calc_test_asin);
  tcase_add_test(tc_calc, calc_test_log10);
  tcase_add_test(tc_calc, calc_test_mod);
  tcase_add_test(tc_calc, calc_test_tan);
  tcase_add_test(tc_calc, calc_test_log);
  tcase_add_test(tc_calc, calc_test_minus);
  tcase_add_test(tc_calc, calc_test_tan);
  tcase_add_test(tc_calc, calc_test_log);
  tcase_add_test(tc_calc, calc_test_sqrt);
  tcase_add_test(tc_calc, calc_test_negative_number);
  tcase_add_test(tc_calc, calc_test_positive_number);
  tcase_add_test(tc_calc, calc_test_inf_expression);
  tcase_add_test(tc_calc, calc_test_brackets_positive_1);
  tcase_add_test(tc_calc, calc_test_brackets_positive_2);
  tcase_add_test(tc_calc, calc_test_brackets_positive_3);
  tcase_add_test(tc_calc, calc_test_brackets_negative_1);
  tcase_add_test(tc_calc, calc_test_brackets_negative_2);
  tcase_add_test(tc_calc, calc_test_brackets_negative_3);
  tcase_add_test(tc_calc, calc_test_brackets_negative_4);
  suite_add_tcase(suite, tc_calc);

  return suite;
}
