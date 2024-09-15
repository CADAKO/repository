#include "s21_credit.h"

void calculateCredit(double totalLoanAmount, int termMonths,
                     double interestRate, int creditType,
                     double *monthlyPayments, double *overpayment,
                     double *totalPayment) {
  *overpayment = 0;
  *totalPayment = 0;
  double tempTotalLoanAmount = totalLoanAmount;

  double monthlyInterestRate = interestRate / 1200;

  if (creditType == 0 && interestRate != 0) {
    // Расчет аннуитетного кредита
    double annuityCoefficient = monthlyInterestRate *
                                pow(1 + monthlyInterestRate, termMonths) /
                                (pow(1 + monthlyInterestRate, termMonths) - 1);
    double monthlyPayment = totalLoanAmount * annuityCoefficient;

    // Рассчитываем общую выплату
    for (int i = 0; i < termMonths; ++i) {
      monthlyPayments[i] = round(monthlyPayment * 100) / 100;
      double interestPayment = totalLoanAmount * monthlyInterestRate;
      double principalPayment = monthlyPayment - interestPayment;
      totalLoanAmount -= principalPayment;
      *totalPayment = *totalPayment + monthlyPayments[i];
    }
  } else {
    // Расчет дифференцированного кредита
    double principalPayment = totalLoanAmount / termMonths;

    for (int i = 0; i < termMonths; ++i) {
      double interestPayment = totalLoanAmount * monthlyInterestRate;
      double monthlyPayment = principalPayment + interestPayment;
      monthlyPayments[i] = round(monthlyPayment * 100) / 100;
      totalLoanAmount -= principalPayment;
      *totalPayment = *totalPayment + monthlyPayments[i];
    }
  }
  *overpayment = *totalPayment - tempTotalLoanAmount;
}
