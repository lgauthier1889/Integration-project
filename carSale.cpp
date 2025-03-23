// File: carSales.cpp
// Dev: Lousiane Gauthier
// Org: FGCU 3003 202308 80602
// Description: main application file for Car Sales Programming Assignment
//------------------------------------------------------------------------------

#include <iostream>
#include <cmath>  // std::pow(), std::log(), std::log1p()

// global types and definitions
const float TAX_RATE = 6.5 / 100.0;
const float TITLE_FEE = 75.25;
const float TRANSFER_FEE = 7.85;
const float REGISTRATION_FEE = 14.50;

struct BillOfSales {
    float price = 0.0;
    float discount = 0.0;
    float tax = 0.0;
    float fees = 0.0;
    float unpaidBalance = 0.0;
};

struct Loan {
    float principle = 0.0;
    float annualRate = 0.0;
    int months = 0;
    float monthlyPayment = 0.0;
    float interest = 0.0;
    float totalPayments = 0.0;
};

struct Contract {
    BillOfSales billOfSale;
    bool finance = false;
    Loan loan;
};

// Function prototypes
BillOfSales getBillOfSales();
Loan getLoan(float loanAmount);
void printContract(const Contract& contract);  // pass by reference
int calculateMonths(float principle, float annualRate, float monthlyPayment);
float calculatePayment(float principle, float rate, int months);

int main() {
    char ask;
    bool anotherContract;

    do {
        Contract contract;

        contract.billOfSale = getBillOfSales();
        std::cout << "\nThe customer wants a loan? ";
        std::cin >> ask;
        contract.finance = (ask == 'Y' || ask == 'y');

        if (contract.finance) {
            contract.loan = getLoan(contract.billOfSale.unpaidBalance);
        }

        printContract(contract);

        std::cout << "\nDo you want to continue entering sales contracts? ";
        std::cin >> ask;
        anotherContract = (ask == 'Y' || ask == 'y');
    } while (anotherContract);

    return 0;
}

void printContract(const Contract& contract) {
    std::cout << "\nSales price: " << contract.billOfSale.price
              << "\nDiscount: " << contract.billOfSale.discount
              << "\nTax: " << contract.billOfSale.tax
              << "\nFees: " << contract.billOfSale.fees
              << "\n\nUnpaid Balance: " << contract.billOfSale.unpaidBalance;

    if (contract.finance) {
        std::cout << "\nMonths: " << contract.loan.months
                  << "\nPayment: " << contract.loan.monthlyPayment
                  << "\nAPR: " << contract.loan.annualRate
                  << "\nTotal Of Payment: " << contract.loan.totalPayments
                  << "\nInterest Paid: " << contract.loan.interest
                  << "\n";
}

int calculateMonths(float principle, float annualRate, float monthlyPayment) {
    float monthlyRate, mathExpression;
    int numberOfMPeriods;

    monthlyRate = annualRate / 12;
    mathExpression = (monthlyPayment / (monthlyPayment - monthlyRate * principle));
    numberOfMPeriods = std::log(mathExpression) / std::log(1 + monthlyRate);

    // round up to the nearest whole number
    numberOfMPeriods += 1;

    return numberOfMPeriods;
}

float calculatePayment(float principle, float rate, int months) {
    float monthlyInterestRate, paymentAmount, exponentialExpression;
    int numberOfMPeriods;
    numberOfMPeriods = calculateMonths(principle, rate, months);

    monthlyInterestRate = rate / 12;
    exponentialExpression = std::powf((1 + monthlyInterestRate), (-numberOfMPeriods));
    paymentAmount = (monthlyInterestRate * principle) / (1 - exponentialExpression);

    return paymentAmount;
}

BillOfSales getBillOfSales() {
    float tax, fees, price, discount;

    BillOfSales billOfSales;

    std::cout << "Sales price: ";
    std::cin >> price;
    billOfSales.price = price;

    std::cout << "\nDiscount: ";
    std::cin >> discount;
    billOfSales.discount = discount;

    tax = (price - discount) * TAX_RATE;
    billOfSales.tax = tax;
    fees = TITLE_FEE + TRANSFER_FEE + REGISTRATION_FEE;
    billOfSales.fees = fees;

    billOfSales.unpaidBalance = price - discount + tax + fees;

    return billOfSales;
}

Loan getLoan(float loanAmount) {
    char ask;

    Loan loan;
    loan.principle = loanAmount; // Initialize principle with loanAmount
    std::cout << "\nEnter APR: ";
    std::cin >> loan.annualRate;

    std::cout << "\nEnter 1)Months, 2)Payment: ";
    std::cin >> ask;

    if (ask == '1') {
        std::cout << "\nNumber of months: ";
        std::cin >> loan.months;
        loan.totalPayments = loan.months * loan.monthlyPayment;
    } else {
        std::cout << "\nMonthly payment amount: ";
        std::cin >> loan.monthlyPayment;
        loan.totalPayments = calculatePayment(loan.principle, loan.annualRate, loan.monthlyPayment);
    }

    loan.totalPayments = loan.months * loan.monthlyPayment;
    loan.interest = loan.totalPayments - loan.principle;

    return loan;
}

