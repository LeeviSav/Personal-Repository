//Final Project: Auto Loan Calculator
//Author: Leevi Savikko
//Last edit on 14/10/2022

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

#define MAX 100
#define PRINTMAX 15

//struct for loan information, including value of old car, price of new car, length of loan, interest rate, and monthly payment
struct loan{
    float oldCarValue;
    float newCarValue;
    float totalLoan;
    int loanLength;
    float InterestRate;
    float monthlyPayment;
};
float monthlyPayment(float totalLoan, float InterestRate, int loanLength);

//Function to calculate monthly payment for the loan
float monthlyPayment(float totalLoan, float InterestRate, int loanLength){
    float monthlyPayment;
    //divide interest rate by 100 to make it a %
    InterestRate = InterestRate/100;
    //calculate monthly interest rate
    InterestRate = InterestRate/12;
    monthlyPayment = totalLoan * (InterestRate * pow((1 + InterestRate), loanLength)) / (pow((1 + InterestRate), loanLength) - 1);
    return monthlyPayment;
}

int main(void){
    //initialize variables and structs
    struct loan loans[MAX];
    struct loan readLoans[MAX];
    int editedLoansNumber[MAX];
    int i;
    int k;
    int operationInt;
    int arraySize = 0;
    int totalLines = 1;
    int oldCarValueMax = 0;
    int newCarValueMax = 0;
    int totalLoanMax = 0;
    int monthlyPaymentMax = 0;
    int lineNumber;
    char fileName[MAX];
    char operation[MAX];
    //ask user to enter NEW to enter new loan information or FILE to read from file
    while (strcmp(operation, "NEW") != 0 && strcmp(operation, "EDIT") != 0 && strcmp(operation, "PRINT") != 0){
        printf("Enter NEW to enter new loan information, EDIT to read and edit from file or PRINT to print all loans from file: ");
        scanf("%s", operation);
    }
    //if user enters NEW, ask for loan information and calculate monthly payment
    if (strcmp(operation, "NEW") == 0){
        printf("Enter old car value (enter -1 to stop): ");
        while (loans[arraySize].oldCarValue != -1){
            scanf("%f", &loans[arraySize].oldCarValue);
            if (loans[arraySize].oldCarValue == -1){
                break;
            }
            printf("Enter new car value: ");
            scanf("%f", &loans[arraySize].newCarValue);
            printf("Enter loan length (in months): ");
            scanf("%d", &loans[arraySize].loanLength);
            printf("Enter interest rate (without %%): ");
            scanf("%f", &loans[arraySize].InterestRate);

            //calculate total loan, Interest rate, and monthly payment from user inputs
            loans[arraySize].totalLoan = loans[arraySize].newCarValue - loans[arraySize].oldCarValue;
            loans[arraySize].monthlyPayment = monthlyPayment(loans[arraySize].totalLoan, loans[arraySize].InterestRate, loans[arraySize].loanLength);
            arraySize++;
            printf("Enter old car value (enter -1 to stop): ");
        }

        //Ask user to enter the file name where to save the loan information
        printf("Enter file name: ");
        scanf("%s", fileName);
        FILE *fp;
        fp = fopen(fileName, "w");

        //write loan information to file
        for (i = 0; i < arraySize; i++){
            fprintf(fp, "Old car value: $%.2f New car value: $%.2f Total loan: $%.2f Loan length: %d Interest rate: %.2f%% Monthly payment: $%.2f\n", loans[i].oldCarValue, loans[i].newCarValue, loans[i].totalLoan, loans[i].loanLength, loans[i].InterestRate, loans[i].monthlyPayment); 
        }
        fclose(fp);
        printf("File %s saved successfully!", fileName);
    }

    else if(strcmp(operation, "EDIT") == 0){
        while(strcmp(operation, "EDIT") == 0){
            //ask user to enter file name
            printf("Enter file name: ");
            scanf("%s", fileName);
            FILE *fp;
            fp = fopen(fileName, "r");

            //scan each line of file and store in struct readLoans
            for (i = 0; i < totalLines; i++){
                fscanf(fp, "Old car value: $%f New car value: $%f Total loan: $%f Loan length: %d Interest rate: %f%% Monthly payment: $%f\n", &readLoans[i].oldCarValue, &readLoans[i].newCarValue, &readLoans[i].totalLoan, &readLoans[i].loanLength, &readLoans[i].InterestRate, &readLoans[i].monthlyPayment);
                //If interest payment is not 0 increment lineNumber
                if (readLoans[i].monthlyPayment != 0){
                    totalLines++;
                }
            }
            fclose(fp);
            printf("Enter line number to edit: ");
            scanf("%d", &lineNumber);
            //while loop to check that user enters a valid line number
            while (lineNumber > totalLines-1 || lineNumber < 1){
                if(lineNumber > totalLines-1){
                    printf("Line number too large, enter a smaller line number: ");
                    scanf("%d", &lineNumber);
                }
                else if(lineNumber < 1){
                    printf("Line number too small, enter a larger line number: ");
                    scanf("%d", &lineNumber);
                }
            }
            //Decrement lineNumber by 1 to get index of struct
            lineNumber--;

            //Ask user to enter what to edit
            printf("Enter 1 to edit old car value, 2 to edit new car value, 3 to edit loan length, 4 to edit Interest rate: ");
            scanf("%d", &operationInt);
            //while loop to check that user enters valid input
            while (operationInt < 1 || operationInt > 4){
                printf("Invalid input. Enter 1 to edit old car value, 2 to edit new car value, 3 to edit loan length, 4 to edit Interest rate: ");
                scanf("%d", &operationInt);
            }
            //If user enters 1 edit old car value
            if (operationInt == 1){
               printf("Enter a new old car value: ");
                scanf("%f", &readLoans[lineNumber].oldCarValue);
            }

            //If user enters 2 edit new car value
            else if (operationInt == 2){
                printf("Enter a new new car value: ");
                scanf("%f", &readLoans[lineNumber].newCarValue);
            }

            //If user enters 3 edit loan length
            else if (operationInt == 3){
                printf("Enter a new loan length: ");
                scanf("%d", &readLoans[lineNumber].loanLength);
            }

            //If user enters 4 edit Interest rate
            else if (operationInt == 4){
                printf("Enter a new interest rate: ");
                scanf("%f", &readLoans[lineNumber].InterestRate);
            }

            //Calculate new total loan, monthly interest rate, and monthly payment from the edited information
            readLoans[lineNumber].totalLoan = readLoans[lineNumber].newCarValue - readLoans[lineNumber].oldCarValue;
            readLoans[lineNumber].monthlyPayment = monthlyPayment(readLoans[lineNumber].totalLoan, readLoans[lineNumber].InterestRate, readLoans[lineNumber].loanLength);

            //Write new loan information to file
            fp = fopen(fileName, "w");
            for (i = 0; i < totalLines; i++){
                //Only write the information if monthly payment is not 0 to avoid writing empty lines
                if (readLoans[i].monthlyPayment != 0){
                    fprintf(fp, "Old car value: $%.2f New car value: $%.2f Total loan: $%.2f Loan length: %d Interest rate: %.2f%% Monthly payment: $%.2f\n", readLoans[i].oldCarValue, readLoans[i].newCarValue, readLoans[i].totalLoan, readLoans[i].loanLength, readLoans[i].InterestRate, readLoans[i].monthlyPayment); 
                }
            }   
            fclose(fp);
            //ask user if they want to edit another line
            printf("Enter EDIT to edit another line or STOP to stop: ");
            scanf("%s", operation);
            //while input is not STOP or EDIT ask user to enter STOP or EDIT
            while (strcmp(operation, "STOP") != 0 && strcmp(operation, "EDIT") != 0){
                printf("Enter EDIT to edit another line or STOP to stop: ");
                scanf("%s", operation);
            }
            if (strcmp(operation, "STOP") == 0){
                break;
            }
        }
        printf("File %s saved successfully!\n", fileName);
    }
    else if(strcmp(operation, "PRINT") == 0){
        printf("Enter file name: ");
        scanf("%s", fileName);
        FILE *fp;
        fp = fopen(fileName, "r");
        //scan each line of file and store in struct readLoans
        for (i = 0; i < totalLines; i++){
            fscanf(fp, "Old car value: $%f New car value: $%f Total loan: $%f Loan length: %d Interest rate: %f%% Monthly payment: $%f\n", &readLoans[i].oldCarValue, &readLoans[i].newCarValue, &readLoans[i].totalLoan, &readLoans[i].loanLength, &readLoans[i].InterestRate, &readLoans[i].monthlyPayment);
            //If interest payment is not 0 increment lineNumber
            if (readLoans[i].monthlyPayment != 0){
                totalLines++;
            }
        }
        for (i = 0; i < totalLines; i++){
            //Print only if monthly payment is not 0 to avoid printing empty lines
            if (readLoans[i].monthlyPayment != 0){
                //Print everything with same number of characters to make it look nice
                if (i == 0){
                    printf("|| %-*s || %-*s || %-*s || %-*s || %-*s || %-*s || %-*s ||\n", 7, "Loan ID", PRINTMAX, "Old Car Value", PRINTMAX, "New Car Value", PRINTMAX, "Total Loan", PRINTMAX, "Loan Length", PRINTMAX, "Interest Rate", PRINTMAX, "Monthly Payment");
                }
                //Printing some with -1 to account for the extra character ($/%) added
                printf("|| %*d || $%*.2f || $%*.2f || $%*.2f || %*d || %*.2f%% || $%*.2f ||\n",7,i+1, PRINTMAX-1, readLoans[i].oldCarValue, PRINTMAX-1, readLoans[i].newCarValue, PRINTMAX-1, readLoans[i].totalLoan, PRINTMAX, readLoans[i].loanLength, PRINTMAX-1, readLoans[i].InterestRate, PRINTMAX-1, readLoans[i].monthlyPayment);
            }
        }
        fclose(fp);
    }
}
