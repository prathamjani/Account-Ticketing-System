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
#include "account.h"
#include "accountTicketingUI.h"

/************************************************************/
void applicationStartup(Account accounts[], int arrSize)
{
	int num = -2;
	while (num != -1)
	{
		num = menuLogin(accounts, arrSize);
		if (num > -1 && accounts[num].account_type != 'C')
		{
			printf("\n");
			menuAgent(accounts, arrSize, &accounts[num]);
		}
		else if (num > -1 && accounts[num].account_type == 'C')
		{
			printf("\nCUSTOMER: home menu currently unavailable...\n\n");
			pauseExecution();
		}
	}
}

/**********************************************************/

int menuLogin(const Account accounts[], int arrSize)
{
	int returnValue = -1;
	char confirm = ' ';
	printf("==============================================\n");
	printf("Account Ticketing System - Login\n");
	printf("==============================================\n");
	printf("1) Login to the system\n0) Exit application\n----------------------------------------------\n\nSelection: ");
	int selection = getIntFromRange(0, 1);
	if (1 == selection)
	{
		int flag = findAccountIndexByAccountNumOfYour(0, accounts, arrSize, 1);
		if (flag > -1)
		{
			returnValue = flag;
		}
		else
		{
			returnValue = -2;
			printf("\nERROR:  Access Denied.\n\n");
			pauseExecution();
		}
	}
	else
	{
		printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
		confirm = getCharOption("yYnN");
		if ('y' == confirm || 'Y' == confirm)
		{
			returnValue = -1;
			printf("\n==============================================\n");
			printf("Account Ticketing System - Terminated\n");
			printf("==============================================\n");
		}
		else
		{
			returnValue = -2;
		}
		printf("\n");
	}

	return returnValue;
}

/**********************************************************/

void menuAgent(Account accounts[], int arrSize, const Account* account)
{
	int selection = -1;
	while (selection != 0)
	{
		printf("AGENT: %s (%05d)\n", account->userInfo.customer_account, account->account_num);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf("1) Add a new account\n2) Modify an existing account\n3) Remove an account\n4) List accounts: summary view\n5) List accounts: detailed view\n----------------------------------------------\n0) Logout\n\nSelection: ");
		selection = getIntFromRange(0, 5);
		if (1 == selection)
		{
			int Flag = findAccountIndexByAccountNumOfThe(0, accounts, arrSize, 0);

			if (Flag < 0)
			{
				printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}
			else
			{
				printf("\n");
				getAccount(&accounts[Flag]);
				getUserLogin(&accounts[Flag].userInfo);
				getDemographic(&accounts[Flag].usersDemo);
				printf("*** New account added! ***\n\n");
				pauseExecution();
			}
		}
		else if (2 == selection)
		{
			int flag = findAccountIndexByAccountNumOfThe(0, accounts, arrSize, 1);
			if (flag > -1)
			{
				printf("\n");
				updateAccount(&accounts[flag]);
			}
			else
			{
				printf("\nERROR:  Access Denied.\n\n");
				pauseExecution();
			}
		}
		else if (3 == selection)
		{
			int flag = findAccountIndexByAccountNumOfThe(0, accounts, arrSize, 1);;

			if (flag > -1 && accounts[flag].account_num == account->account_num)
			{
				printf("\nERROR: You can't remove your own account!\n\n");
				pauseExecution();
			}
			else if (flag > -1)
			{
				int userInput = ' ';
				displayAccountDetailHeader();
				displayAccountDetailRecord(&accounts[flag]);
				printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
				userInput = getCharOption("YN");
				if (userInput == 'Y')
				{
					accounts[flag].account_num = 0;
					printf("\n*** Account Removed! ***\n\n");
					pauseExecution();
				}
				else
				{
					printf("\n*** No changes made! ***\n\n");
					pauseExecution();
				}
			}
			else
			{
				printf("\nERROR:  Access Denied.\n\n");
				pauseExecution();
			}
		}
		else if (4 == selection)
		{
			displayAllAccountSummaryRecords(accounts, arrSize);
		}
		else if (5 == selection)
		{
			displayAllAccountDetailRecords(accounts, arrSize);
		}
		else
		{
			printf("\n");
			printf("### LOGGED OUT ###\n");
			printf("\n");
		}
	}
	return;
}

/******************************************************************/
int findAccountIndexByAccountNumOfYour(int account, const Account accounts[], int arrSize, int reAccNum)
{
	int i = 0;
	int flag = 0;
	int returnValue = -1;
	if (reAccNum == 1)
	{
		printf("\nEnter your account#: ");
	}
	account = (reAccNum == 1) ? getPositiveInteger() : account;
	while (i < arrSize && !flag)
	{
		if (accounts[i].account_num == account)
		{
			flag = 1;
		}
		else
		{
			i++;
		}
	}
	returnValue = (flag == 1) ? i : -1;
	return returnValue;
}

int findAccountIndexByAccountNumOfThe(int account, const Account accounts[], int arrSize, int reAccNum)
{
	int i = 0;
	int flag = 0;
	int returnValue = -1;
	if (reAccNum == 1)
	{
		printf("\nEnter the account#: ");
	}
	account = (reAccNum == 1) ? getPositiveInteger() : account;
	while (i < arrSize && !flag)
	{
		if (accounts[i].account_num == account)
		{
			flag = 1;
		}
		else
		{
			i++;
		}
	}
	returnValue = (flag == 1) ? i : -1;
	return returnValue;
}

/*******************************************************************/
void displayAllAccountSummaryRecords(const Account accounts[], int arrSize)
{
	int i = 0;
	printf("\n");
	displayAccountSummaryHeader();
	while (i < arrSize)
	{
		if (accounts[i].account_num != 0)
		{
			displayAccountSummaryRecord(&accounts[i]);
		}
		i++;
	}
	printf("\n");
	pauseExecution();
}

/*****************************************************************/
void displayAllAccountDetailRecords(const Account accounts[], int arrSize)
{
	int i = 0;
	printf("\n");
	displayAccountDetailHeader();
	while (i < arrSize)
	{
		if (accounts[i].account_num != 0)
		{
			displayAccountDetailRecord(&accounts[i]);
		}
		i++;
	}
	printf("\n");
	pauseExecution();
}

/*****************************************************************/
void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}

/********************************************************************/
void updateAccount(Account* account)
{
	int selection = -1;
	while (selection != 0)
	{
		printf("Account: %05d - Update Options\n", account->account_num);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->account_type);
		printf("2) Login\n3) Demographics\n0) Done\nSelection: ");
		selection = getIntFromRange(0, 3);
		{
			if (1 == selection)
			{
				printf("\n");
				printf("Enter the account type (A=Agent | C=Customer): ");
				account->account_type = getCharOption("AC");
				printf("\n");
			}
			else if (2 == selection)
			{
				printf("\n");
				updateUserLogin(&account->userInfo);
				printf("\n");
			}
			else if (3 == selection)
			{
				printf("\n");
				updateDemographic(&account->usersDemo);
				printf("\n");
			}
			else
			{
				printf("\n");
			}
		}
	}
	return;
}

/********************************************************************/
void updateUserLogin(UserLogin* userInfo)
{
	int selection = -1;
	while (selection != 0)
	{
		printf("User Login: %s - Update Options\n", userInfo->user_name);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", userInfo->customer_account);
		printf("2) Password\n0) Done\nSelection: ");
		selection = getIntFromRange(0, 2);
		if (1 == selection)
		{
			printf("\nEnter the display name (%d chars max): ", USER_ACC_MAX);
			getCString(userInfo->customer_account, USER_ACC_MIN, USER_ACC_MAX);
			printf("\n");
		}
		else if (2 == selection)
		{
			printf("\nEnter the password (must be %d chars in length): ", USER_PASWD);
			getCString(userInfo->password, USER_PASWD, USER_PASWD);
			printf("\n");
		}
		else
		{
			//printf("\n");
			//return;
		}
	}
	return;
}

/********************************************************************/
void updateDemographic(Demographic* demo)
{
	int selection = -1;
	while (selection != 0)
	{
		printf("Demographic Update Options\n----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", demo->household_income);
		printf("2) Country (current value: %s)\n", demo->country);
		printf("0) Done\nSelection: ");
		selection = getIntFromRange(0, 2);
		if (1 == selection)
		{
			printf("\nEnter the household Income: $");
			demo->household_income = getPositiveDouble();
			printf("\n");
		}
		else if (2 == selection)
		{
			printf("\nEnter the country (30 chars max.): ");
			getCString(demo->country, COUNTRY_NAME_MIN, COUNTRY_NAME_MAX);
			printf("\n");
		}
		else
		{
			return;
		}
	}
	return;
}