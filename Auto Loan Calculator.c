#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

#define MAX 100

//struct for loan information, including value of old car, price of new car, length of loan, interest rate, and monthly payment
struct loan{
    float oldCarValue;
    float newCarValue;
    float totalLoan;
    int loanLength;
    float monthInterestRate;
    float monthlyPayment;
};
float monthlyPayment(float totalLoan, float monthInterestRate, int loanLength);

//Function to calculate monthly payment for the loan
float monthlyPayment(float totalLoan, float monthInterestRate, int loanLength){
    float monthlyPayment;
    //divide interest rate by 100 to make it a %
    monthInterestRate = monthInterestRate/100;
    monthlyPayment = totalLoan * (monthInterestRate * pow((1 + monthInterestRate), loanLength)) / (pow((1 + monthInterestRate), loanLength) - 1);
    return monthlyPayment;
}

int main(void){
    //initialize variables and structs
    struct loan loans[MAX];
    struct loan readLoans[MAX];
    int i;
    int operationInt;
    int arraySize = 0;
    int totalLines = 1;
    int lineNumber;
    char fileName[MAX];
    char operation[MAX];
    //ask user to enter NEW to enter new loan information or FILE to read from file
    while (strcmp(operation, "NEW") != 0 && strcmp(operation, "FILE") != 0){
        printf("Enter NEW to enter new loan information or FILE to read and edit from file: ");
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
            printf("Enter monthly interest rate (without %%): ");
            scanf("%f", &loans[arraySize].monthInterestRate);

            //calculate total loan, monthly interest rate, and monthly payment from user inputs

            loans[arraySize].totalLoan = loans[arraySize].newCarValue - loans[arraySize].oldCarValue;
            loans[arraySize].monthlyPayment = monthlyPayment(loans[arraySize].totalLoan, loans[arraySize].monthInterestRate, loans[arraySize].loanLength);
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
            fprintf(fp, "Old car value: $%.2f New car value: $%.2f Total loan: $%.2f Loan length: %d Monthly interest rate: %.2f%% Monthly payment: $%.2f\n", loans[i].oldCarValue, loans[i].newCarValue, loans[i].totalLoan, loans[i].loanLength, loans[i].monthInterestRate, loans[i].monthlyPayment); 
        }
        fclose(fp);
        printf("File %s saved successfully!", fileName);
    }

    //If user enters FILE ask which file to open and read for loan information
    else if (strcmp(operation, "FILE") == 0){
        //ask user to enter file name
        printf("Enter file name: ");
        scanf("%s", fileName);
        FILE *fp;
        fp = fopen(fileName, "r");

        //scan each line of file and store in struct readLoans
        for (i = 0; i < totalLines; i++){
            fscanf(fp, "Old car value: $%f New car value: $%f Total loan: $%f Loan length: %d Monthly interest rate: %f%% Monthly payment: $%f\n", &readLoans[i].oldCarValue, &readLoans[i].newCarValue, &readLoans[i].totalLoan, &readLoans[i].loanLength, &readLoans[i].monthInterestRate, &readLoans[i].monthlyPayment);
            //If interest payment is not 0 increment lineNumber
            if (readLoans[i].monthlyPayment != 0){
                totalLines++;
            }
        }
        fclose(fp);

        //Ask user to enter EDIT to edit loan information or PRINT to print loans
        printf("Enter EDIT to edit loan information or PRINT to print all loans: ");
        scanf("%s", operation);

        //While operation != "EDIT" or "PRINT" repeat the question
        while (strcmp(operation, "EDIT") != 0 && strcmp(operation, "PRINT") != 0){
            printf("Enter EDIT to edit loan information or PRINT to print all loans: ");
            scanf("%s", operation);
        }

        //If user enters EDIT Ask user to enter line number to edit
        if (strcmp(operation, "EDIT") == 0){
        printf("Enter line number to edit: ");
        while (lineNumber > totalLines || lineNumber < 1){
            scanf("%d", &lineNumber);
            if (lineNumber > totalLines){
                printf("Line number larger than total lines. Enter line number to edit: ");
            }
        }

        //Decrement lineNumber by 1 to get index of struct
        lineNumber--;

        //Ask user to enter what to edit
        printf("Enter 1 to edit old car value, 2 to edit new car value, 3 to edit loan length, 4 to edit monthly interest rate: ");
        scanf("%d", &operationInt);

        //If user enters 1 edit old car value
        if (operationInt == 1){
            printf("Enter new old car value: ");
            scanf("%f", &readLoans[lineNumber].oldCarValue);
        }

        //If user enters 2 edit new car value
        else if (operationInt == 2){
            printf("Enter new new car value: ");
            scanf("%f", &readLoans[lineNumber].newCarValue);
        }

        //If user enters 3 edit loan length
        else if (operationInt == 3){
            printf("Enter new loan length: ");
            scanf("%d", &readLoans[lineNumber].loanLength);
        }

        //If user enters 4 edit monthly interest rate
        else if (operationInt == 4){
            printf("Enter new monthly interest rate: ");
            scanf("%f", &readLoans[lineNumber].monthInterestRate);
        }

        //Calculate new total loan, monthly interest rate, and monthly payment from the edited information
        readLoans[lineNumber].totalLoan = readLoans[lineNumber].newCarValue - readLoans[lineNumber].oldCarValue;
        readLoans[lineNumber].monthlyPayment = monthlyPayment(readLoans[lineNumber].totalLoan, readLoans[lineNumber].monthInterestRate, readLoans[lineNumber].loanLength);

        //Write new loan information to file
        fp = fopen(fileName, "w");
        for (i = 0; i < totalLines; i++){
            //Only write the information if monthly payment is not 0 to avoid writing empty lines
            if (readLoans[i].monthlyPayment != 0){
                fprintf(fp, "Old car value: $%.2f New car value: $%.2f Total loan: $%.2f Loan length: %d Monthly interest rate: %.2f%% Monthly payment: $%.2f\n", readLoans[i].oldCarValue, readLoans[i].newCarValue, readLoans[i].totalLoan, readLoans[i].loanLength, readLoans[i].monthInterestRate, readLoans[i].monthlyPayment); 
            }
        }
        printf("File %s Line %d edited successfully!", fileName, lineNumber + 1);
        fclose(fp);
        }

        //If user enters PRINT
        //Print all loans
        if (strcmp(operation, "PRINT") == 0){
            for (i = 0; i < totalLines; i++){
                //Print only if monthly payment is not 0 to avoid printing empty lines
                if (readLoans[i].monthlyPayment != 0){
                    printf("Old car value: $%.2f New car value: $%.2f Total loan: $%.2f Loan length: %d Monthly interest rate: %.2f%% Monthly payment: $%.2f\n", readLoans[i].oldCarValue, readLoans[i].newCarValue, readLoans[i].totalLoan, readLoans[i].loanLength, readLoans[i].monthInterestRate, readLoans[i].monthlyPayment); 
                }
            }
        }
    }
}