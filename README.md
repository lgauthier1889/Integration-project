// File: carSales.cpp
// Dev: Lousiane Gauthier
// Org: FGCU 3003 202308 80602
// Description: main application file for Car Sales Programming Assignment
//-------------------------------------------------------------------------------
#include <iostream>
#include <cmath> //std::pow() for calculatePayment(), std::log() for calculateMonths().
//-------------------------------------------------------------------------------

//OpenSSF Scorecard
[![OpenSSF Scorecard](htt‌ps://api.securityscorecards.dev/projects/github.com/{lgauthier1889}/{integration-project}/badge)](htt‌ps://securityscorecards.dev/viewer/?uri=github.com/{owner}/{repo})

// global types and definitions
//---------------------------------------------------------------------------------
const float TAX_RATE = 6.5 / 100.0;  //*this math is done by the compiler*
const float TITLE_FEE = 75.25;
const float TRANSFER_FEE = 7.85;
const float REGISTRATION_FEE = 14.50;

struct BillOfSales { //*20 bites of memory (float=4)*
    float price;                                 //Entered sales price of the car.
    float discount; //Entered sum of any down payment, trade-in, dealer discounts.
    float tax;                                      //Calculated sales tax amount.
    float fees;                   //Sum of Title, Transfer, and Registration fees.
    float unpaidBalance;                            //Calculated cost of the car.
};

struct Loan {
    float principle;      //Amount to finance.
    float annualRate;     //Annual percentage rate of interest.
    int months;           //Number of monthly payments.
    float monthlyPayment; //Monthly payment amount.
    float interest;       //Total amount of interest paid on the loan.
    float totalPayments;  //including interest
};

struct Contract { //*45bites*
    BillOfSales billOfSale; //A Bill of Sale structure property.
    bool finance;       //(true: calculate loan, false: paying cash).
    Loan loan;        //A Loan structure property.
};

// Function declaration (proto-types)
// ---------------------------------------------------------------------------------
BillOfSales getBillOfSales();
Loan getLoan(float loanAmount);

//Function definitions
//-----------------------------------------------------------------------------------

int main() {
    char ask;
    bool anotherContract;

    do {

    Contract contract {0};

    contract.billOfSale = getBillOfSales();

    std::cout << "\nThe customer wants a loan? ";
    std::cin >> ask;
    contract.finance = (ask == 'Y' || ask == 'y');
    if (contract.finance){
        contract.loan = getLoan(contract.billOfSale.unpaidBalance);
    }

    printContract(contract);

        std::cout << "\nDo you want to continue entering sales contracts. ";
        std::cin >> ask;
        anotherContract = (ask == 'Y' || ask == 'y');
    } while (anotherContract);

    return 0;

} //end main


int calculateMonths(float principle, float annualRate, float monthlyPayment){

    float monthlyRate, mathExpression;
    int numberOfMPeriods;

    monthlyRate = annualRate / 12;
    mathExpression = (monthlyPayment /
                      (monthlyPayment - monthlyRate * principle));
    numberOfMPeriods = (std::log(mathExpression)) / (std::log(1+monthlyRate));

    //round up to the nearest hole number
    numberOfMPeriods += 1;

    return(numberOfMPeriods);
}

float calculatePayment(float principle, float rate, int months) {

    float monthlyInterestRate, paymentAmount, exponentialExpression;
    int numberOfMPeriods;
    numberOfMPeriods = calculateMonths (principle, rate, months);

    monthlyInterestRate = rate / 12;
    exponentialExpression = std::powf((1+monthlyInterestRate),(-numberOfMPeriods));
    paymentAmount = (monthlyInterestRate * principle)/(1-exponentialExpression);

    return(paymentAmount);
}

BillOfSales getBillOfSales() {
    float tax, fees, price, discount;

    BillOfSales billOfSales {0};

    std::cout << "Sales price : ";
    std::cin >> price;
    billOfSales.price = price;

    std::cout << "\nDiscount    :";
    std::cin >> discount;
    billOfSales.discount = discount;

    tax = (price - discount) * TAX_RATE;
    billOfSales.tax = tax;
    fees = TITLE_FEE + TRANSFER_FEE + REGISTRATION_FEE;
    billOfSales.fees = fees;

    billOfSales.unpaidBalance = price - discount + tax + fees;

    return(billOfSales);
}



/**
 * performs I/O to get required....
 * @param loanAmount
 * @return
 */
Loan getLoan(float loanAmount) {

    char ask;

    Loan loan {0};
    std::cout << "\nEnter APR: ";
    std::cin >> loan.annualRate;

    std::cout<< "\nEnter 1)Months, 2)Payment: ";
    std::cin >> ask;

    if (ask == 1 ){

        std::cout << "\nNumber of months: ";
        std::cin >> loan.months;

    }else {

        std::cout << "\nMonthly payment amount: ";
        std::cin >> loan.monthlyPayment;
        loan.totalPayments = calculatePayment(loan.principle, loan.annualRate, loan.monthlyPayment);
    }

    loan.totalPayments = loan.months * loan.monthlyPayment;
    loan.interest = loan.totalPayments - unpaidBalance.unpaidBalance;

    return (loan);
}

void printContract(Contract contract) {

    std::cout << "\nSales price: " << contract.billOfSale.price
              << "\nDiscount: " << contract.billOfSale.discount
              <<"\nTax: " << contract.billOfSale.tax
              <<"\nFess: " << contract.billOfSale.fees
              <<"\n"
              <<"\n Unpaid Balance: " <<contract.billOfSale.unpaidBalance;

    if(contract.finance){

        std::cout << "\nMonths: " << contract.loan.months
                  << "\nPayment: " << contract.loan.monthlyPayment
                  << "\nAPR: " << contract.loan.annualRate
                  << "\nTotal Of Payment: " << contract.loan.totalPayments
                  << "\nInterest Paid: " << contract.loan.interest
                  <<"\n";

    }
}
