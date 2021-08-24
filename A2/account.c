// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Pratham Jayesh Jani
//  Student ID    : 134947209
//  Student Email : pjjani@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#include <stdio.h>
#include <ctype.h>
#include "account.h"
#include "commonHelpers.h"

void getAccount(Account* acc)
{
    printf("New Account Data (Account#:%d)\n", acc->accNumber);
    printf("----------------------------------------\n");
    printf("Enter the account type (A=Agent | C=Customer): ");
    acc->accType = getCharOption("AC");
    printf("\n");
}

void getUserLogin(UserLogin* login)
{
    int j = 0;
    printf("User Login Data Input\n");                 // *** DO NOT MODIFY THIS LINE ***
    printf("----------------------------------------\n"); // *** DO NOT MODIFY THIS LINE ***
    // Add the necessary code to get user input for each UserLogin member:
    do
    {
        j = 0;
        printf("Enter user login (10 chars max): ");
        getCString(login->login_name, 0, 10);
        int i = 0;
        for (i = 0; i <= 10; i++)
        {
            if (login->login_name[i] == ' ')
            {
                j = 1;
            }
        }
        if (j == 1) printf("ERROR:  The user login must NOT contain whitespace characters.\n");
    } while (j == 1);
    j = 0;
    printf("Enter the display name (30 chars max): ");
    getCString(login->userName, 0, 30);

    int l = 0;
    while (l != 1)
    {
        char expressions[9] = "!@#$%^&*";
        int i = 0, index = 0;
        printf("Enter the password (must be 8 chars in length): ");
        getCString(login->password, 8, 8);
        int d = 0, lc = 0, uc = 0, e = 0;

        for (i = 0; i < 9; i++)
        {
            if (isdigit(login->password[i]))
            {
                d = d + 1;
            }
            else if (isupper(login->password[i]))
            {
                uc = uc + 1;
            }
            else if (islower(login->password[i]))
            {
                lc = lc + 1;
            }
            else
            {
                for (index = 0; index < 9; index++)
                {
                    if (login->password[i] == expressions[index])
                    {
                        e = e + 1;
                    }

                }
            }
        }
        if (d == 2 && uc == 2 && lc == 2 && e == 3)
        {
            l = 1;
        }
        else
        {
            printf("SECURITY: Password must contain 2 of each:\n");
            printf("          Digit: 0-9\n          UPPERCASE character\n          lowercase character\n          symbol character: %8s\n", expressions);
        }
    }
    printf("\n");
}

void getDemographic(Demographic* demo)
{
    // Demographic Data: get user input
    // ---------------------------------------------------------
    printf("Demographic Data Input\n");                // *** DO NOT MODIFY THIS LINE ***
    printf("----------------------------------------\n"); // *** DO NOT MODIFY THIS LINE ***

    // Add the necessary code to get user input for each Demographic member:

    printf("Enter birth year (current age must be between %d and %d): ", 18, 110);
    demo->birthYear = getIntFromRange(currentYear() - 110, currentYear() - 18);
    printf("Enter the household Income: $");
    demo->income = getPositiveDouble();
    printf("Enter the country (30 chars max.): ");
    getCString(demo->country, 1, 30);
    printf("\n");
}


void displayAccountSummaryHeader(void)
{
    printf("Acct# Acct.Type Birth\n");
    printf("----- --------- -----\n");
}


void displayAccountSummaryRecord(const Account* Acc)
{
    if (Acc->accNumber > 0)
    {
        printf("%5d %-9s %5d\n", Acc->accNumber, Acc->accType == 'C' ? "CUSTOMER" : "AGENT", Acc->demo_info.birthYear);
    }
}

void displayAccountDetailHeader(void)
{
    printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
    printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountDetailRecord(const Account* Acc)
{
    if (Acc->accNumber > 0)
    {
        int i = 0;
        char star[9] = { 0 };
        for (i = 0; i < 8; i++)
        {
            if (star[i] != (i % 2)) star[i] = '*';
            else star[i] = Acc->login_info.password[i];
        }
        printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", Acc->accNumber, Acc->accType == 'C' ? "CUSTOMER" : "AGENT", Acc->demo_info.birthYear, Acc->demo_info.income, Acc->demo_info.country, Acc->login_info.userName, Acc->login_info.login_name, star);
    }
}

void updateDemographic(Demographic* demo)
{
    int selection = -5;
    while (selection != 0)
    {

        printf("Demographic Update Options\n----------------------------------------\n");
        printf("1) Household Income (current value: $%.2lf)\n", demo->income);
        printf("2) Country (current value: %s)\n", demo->country);
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 2);
        if (selection == 1)
        {
            printf("\nEnter the household Income: $");
            demo->income = getPositiveDouble();
            printf("\n");
        }
        else if (selection == 2)
        {
            printf("\nEnter the country (30 chars max.): ");
            getCString(demo->country, 1, 30);
            printf("\n");
        }
        else
        {
            selection = 0;
        }
    }
}
void updateUserLogin(UserLogin* login)
{
    int selection = -1;
    while (selection != 0)
    {
        printf("User Login: %s - Update Options\n", login->login_name);
        printf("----------------------------------------\n");
        printf("1) Display name (current value: %s)\n", login->userName);
        printf("2) Password\n0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 2);
        if (selection == 1)
        {
            printf("\nEnter the display name (30 chars max): ");
            getCString(login->userName, 0, 30);
            printf("\n");
        }
        else if (selection == 2)
        {

            int l = 0;
            while (l != 1)
            {
                char expressions[9] = "!@#$%^&*";
                int i = 0, index = 0;
                printf("\nEnter the password (must be 8 chars in length): ");
                getCString(login->password, 8, 8);
                int d = 0, lc = 0, uc = 0, e = 0;

                for (i = 0; i < 9; i++)
                {
                    if (isdigit(login->password[i]))
                    {
                        d = d + 1;
                    }
                    else if (isupper(login->password[i]))
                    {
                        uc = uc + 1;
                    }
                    else if (islower(login->password[i]))
                    {
                        lc = lc + 1;
                    }
                    else
                    {
                        for (index = 0; index < 9; index++)
                        {
                            if (login->password[i] == expressions[index])
                            {
                                e = e + 1;
                            }
                        }
                    }
                }
                if (d == 2 && uc == 2 && lc == 2 && e == 3)
                {
                    l = 1;
                }
                else
                {
                    printf("SECURITY: Password must contain 2 of each:\n");
                    printf("          Digit: 0-9\n          UPPERCASE character\n          lowercase character\n          symbol character: %8s\n", expressions);
                }
            }
            printf("\n");
        }
        else
        {
            selection = 0;
        }
    }
}

void updateAccount(Account* account)
{
    int selection = -3;
    while (selection != 0)
    {
        printf("Account: %5d - Update Options\n", account->accNumber);
        printf("----------------------------------------\n");
        printf("1) Update account type (current value: %c)\n", account->accType);
        printf("2) Login\n3) Demographics\n0) Done\nSelection: ");
        selection = getIntFromRange(0, 3);
        {
            if (selection == 1)
            {
                printf("\n");
                printf("Enter the account type (A=Agent | C=Customer): ");
                account->accType = getCharOption("AC");
            }
            else if (selection == 2)
            {
                printf("\n");
                updateUserLogin(&account->login_info);
                printf("\n");
            }
            else if (selection == 3)
            {
                printf("\n");
                updateDemographic(&account->demo_info);
                printf("\n");
            }
            else
            {
                selection = 0;
                printf("\n");
            }
        }
    }
}

int findAccountbyIndex(int account, const Account accounts[], int maxarray, int check)
{
    int i = 0, flag = 0, index = -3;
    if (check == 1)
    {
        printf("\nEnter the account#: ");
        account = getPositiveInteger();
    }
    else account = account;
    while (i <= maxarray && flag != 1)
    {
        if (accounts[i].accNumber == account)
        {
            flag = 1;
            index = i;
        }
        i++;
    }
    if (flag != 1) index = -1;

    return index;
}

