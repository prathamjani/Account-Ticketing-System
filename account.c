// ===================================================================================
//  Assignment: 1 
//  Milestone : 4
// ===================================================================================

// ===================================================================================
//  Student Name  : Pratham Jayesh Jani
//  Student ID    : 134947209
//  Student Email : pjjani@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#define _CRT_SECURE_NO_WARNINGS
#include "commonHelpers.h"
#include "account.h"

/***************************************************/
void getAccount(Account* accPtr)
{
    printf("Account Data: New Record\n");                   // *** DO NOT MODIFY THIS LINE ***
    printf("----------------------------------------\n"); // *** DO NOT MODIFY THIS LINE ***
    // Add the necessary code to get user input for each Account member:

    printf("Enter the account number: ");
    accPtr->account_num = getPositiveInteger();
    printf("\nEnter the account type (A=Agent | C=Customer): ");
    accPtr->account_type = getCharOption("AC");
    printf("\n");
}

/************************************************/
void getUserLogin(UserLogin* usrPtr)
{
    printf("User Login Data Input\n");                 // *** DO NOT MODIFY THIS LINE ***
    printf("----------------------------------------\n"); // *** DO NOT MODIFY THIS LINE ***

    // Add the necessary code to get user input for each UserLogin member:
    printf("Enter user login (10 chars max): ");
    getCString(usrPtr->user_name, USER_NAME_MIN, USER_NAME_MAX);
    printf("Enter the display name (30 chars max): ");
    getCString(usrPtr->customer_account, USER_ACC_MIN, USER_ACC_MAX);
    printf("Enter the password (must be 8 chars in length): ");
    getCString(usrPtr->password, USER_PASWD, USER_PASWD);
    printf("\n");
}

/******************************************************/
void getDemographic(Demographic* demoPtr)
{
    // Demographic Data: get user input
    // ---------------------------------------------------------
    printf("Demographic Data Input\n");                // *** DO NOT MODIFY THIS LINE ***
    printf("----------------------------------------\n"); // *** DO NOT MODIFY THIS LINE ***

    // Add the necessary code to get user input for each Demographic member:
    // NOTE: You will need to get the CURRENT YEAR to devise the appropriate range
    //       when prompting for the birth year data.  There is a function in the 
    //       commonHelpers library that gives you this!
    printf("Enter birth year (current age must be between %d and %d): ", MIN_YRS, MAX_YRS);
    demoPtr->birth_year = getIntFromRange(currentYear() - MAX_YRS, currentYear() - MIN_YRS);

    printf("Enter the household Income: $");
    demoPtr->household_income = getPositiveDouble();
    
    printf("Enter the country (30 chars max.): ");
    getCString(demoPtr->country, COUNTRY_NAME_MIN, COUNTRY_NAME_MAX);
    printf("\n");
}


/*****************************************************/
void displayAccountSummaryHeader(void)
{
    printf("Acct# Acct.Type Birth\n");
    printf("----- --------- -----\n");
}


/*****************************************************/
void displayAccountSummaryRecord(const Account* inputAccount)
{
    printf("%5d %-9s %5d\n", inputAccount->account_num, inputAccount->account_type == 'C' ? "CUSTOMER" : "AGENT", inputAccount->usersDemo.birth_year);
}

/***************************************************/
void displayAccountDetailHeader(void)
{
    printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
    printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

/******************************************************/
void displayAccountDetailRecord(const Account* inputAccount)
{
    int i = 0;
    char temp[USER_PASWD + 1] = { 0 };
    for (i = 0; i < USER_PASWD; i++)
    {
        temp[i] = (i % 2) ? '*' : inputAccount->userInfo.password[i];
    }
    printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", inputAccount->account_num, inputAccount->account_type == 'C' ? "CUSTOMER" : "AGENT", inputAccount->usersDemo.birth_year, inputAccount->usersDemo.household_income, inputAccount->usersDemo.country, inputAccount->userInfo.customer_account, inputAccount->userInfo.user_name, temp);
}
