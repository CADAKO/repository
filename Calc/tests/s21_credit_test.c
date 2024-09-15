#include "s21_test.h"

START_TEST(credit_annuity_01) {
  double totalLoanAmount = 100;
  int termMonths = 60;
  double interestRate = 123.456;
  int creditType = 0;
  double monthlyPayments[termMonths];
  double overpayment = 0;
  double totalPayment = 0;
  calculateCredit(totalLoanAmount, termMonths, interestRate, creditType,
                  monthlyPayments, &overpayment, &totalPayment);
  ck_assert_double_eq(monthlyPayments[0], 10.32);
  ck_assert(fabs(overpayment - 519.2) < 0.001);
  ck_assert(fabs(totalPayment - 619.2) < 0.001);
}
END_TEST

START_TEST(credit_differentiated_01) {
  double totalLoanAmount = 100;
  int termMonths = 6;
  double interestRate = 123.456;
  int creditType = 1;
  double monthlyPayments[termMonths];
  double overpayment = 0;
  double totalPayment = 0;
  double res[] = {26.95, 25.24, 23.53, 21.81, 20.10, 18.38};
  calculateCredit(totalLoanAmount, termMonths, interestRate, creditType,
                  monthlyPayments, &overpayment, &totalPayment);
  for (int i = 0; i < termMonths; i++) {
    ck_assert_double_eq(res[i], monthlyPayments[i]);
  }
  ck_assert(fabs(overpayment - 36.01) < 0.001);
  ck_assert(fabs(totalPayment - 136.01) < 0.001);
}
END_TEST

Suite *test_credit() {
  Suite *suite = suite_create("credit_suite");

  TCase *tc_credit = tcase_create("test_credit");
  tcase_add_test(tc_credit, credit_annuity_01);
  tcase_add_test(tc_credit, credit_differentiated_01);

  suite_add_tcase(suite, tc_credit);

  return suite;
}
