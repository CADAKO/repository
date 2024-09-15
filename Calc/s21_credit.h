#ifndef SRC_S21_CREDIT_H_
#define SRC_S21_CREDIT_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void calculateCredit(double totalLoanAmount, int termMonths,
                     double interestRate, int creditType,
                     double *monthlyPayments, double *overpayment,
                     double *totalPayment);

#endif
