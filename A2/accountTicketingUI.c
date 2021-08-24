// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Pratham Jayesh Jani
//  Student ID    : 134947209
//  Student Email : pjjani@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"accountTicketingUI.h"
#include"account.h"
#include"commonHelpers.h"
#include"ticket.h"
#include<string.h>



void applicationStartup(AccountTicketingData* account)
{
	int index;
	do
	{
		index = menuLogin(account);
		if (account->accounts[index].accType == 'C' && index >= 0)
		{
			customermenu(account, index);
		}

		if (account->accounts[index].accType == 'A' && index >= 0)
		{
			printf("\n");
			menuAgent(account, &account->accounts[index]);
		}
	} while (index != -1);
}


int findTicket(Ticket* tickets, int ticketArraySize) // Get index of ticket matched with user's input
{
	int i = 0, rValue = 1;

	int found = getPositiveInteger();

	if (found != 0)
	{
		for (i = 0; i <= ticketArraySize && found != tickets[i].ticketNumber; i++);
		{
			if (found == tickets[i].ticketNumber) rValue = i;
			else rValue = -1;
		}
		if (rValue == 1) rValue = i;
	}
	else rValue = -3;

	return(rValue);
}

void displayAllAccountSummaryRecords(AccountTicketingData* account) // Displays all accounts summary
{
	int num = 0;
	printf("\n");
	displayAccountSummaryHeader();
	while (num < account->ACCOUNT_MAX_SIZE)
	{
		displayAccountSummaryRecord(&account->accounts[num]);
		num++;
	}
	printf("\n");
	pauseExecution();
}

void displayAllAccountDetailRecords(AccountTicketingData* account) // Displays all accounts detail records
{
	int num = 0;
	printf("\n");
	displayAccountDetailHeader();
	while (num < account->ACCOUNT_MAX_SIZE)
	{
		displayAccountDetailRecord(&account->accounts[num]);
		num++;
	}
	printf("\n");
	pauseExecution();
}

int menuLogin(AccountTicketingData* accountt)
{
	int returnValue = -1, count;
	char confirm = 0;

	do
	{
		count = 3;
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n0) Exit application\n----------------------------------------------\n\nSelection: ");

		int selection = getIntFromRange(0, 1);

		if (selection == 1)
		{

			int i = 0, check = 0, account = 0;
			char string[31];
			char login[31];
			
			printf("\n");
			do
			{
				count--;
				printf("Enter the account#: ");
				i = 0;
				account = getPositiveInteger();

				for (i = 0; i <= accountt->ACCOUNT_MAX_SIZE && account != accountt->accounts[i].accNumber; i++);

				printf("User Login    : ");
				getCString(login, 0, MAX_USER_ACC);

				printf("Password      : ");
				getCString(string, 0, 20);

				if (strcmp(login, accountt->accounts[i].login_info.login_name) == 0 && strcmp(string, accountt->accounts[i].login_info.password) == 0)
				{
					check = -3;
				}
				else
				{
					printf("INVALID user login/password combination! [attempts remaining:%d]\n\n", count);
				}

				if (count == 0)
				{
					printf("ERROR:  Login failed!\n\n");
					clearStandardInputBuffer();
					pauseExecution();
					check = -3;
				}
				returnValue = i;
			} while (check != -3);
		}

		if (selection == 0)
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

	} while (count == 0);
	return returnValue;
}

void menuAgent(AccountTicketingData* acccountData, const Account* account)
{
	int selection = -1;

	while (selection != 0)
	{
		printf("AGENT: %s (%05d)\n", account->login_info.userName, account->accNumber);
		
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		
		printf(" 1) Add a new account\n 2) Modify an existing account\n 3) Remove an account\n 4) List accounts: summary view\n 5) List accounts: detailed view\n----------------------------------------------\n 6) List new tickets\n 7) List active tickets\n 8) List closed tickets\n 9) Manage a ticket\n10) Archive closed tickets\n----------------------------------------------\n11) View archived account statistics\n12) View archived tickets statistics\n----------------------------------------------\n0) Logout\n\nSelection: ");

		selection = getIntFromRange(0, 12);
		
		if (1 == selection)
		{
			int greatestAccount = 0;
			int flag = 0;
			for (flag = 0; flag < acccountData->ACCOUNT_MAX_SIZE && acccountData->accounts[flag].accNumber != 0; flag++);

			if (flag == acccountData->ACCOUNT_MAX_SIZE && acccountData->accounts[flag].accNumber > 0)
			{
				printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}
			else
			{
				greatestAccount = findMaxAccbyNum(acccountData, 0);
				acccountData->accounts[flag].accNumber = (greatestAccount + 1);

				printf("\n");
				getAccount(&acccountData->accounts[flag]);

				getUserLogin(&acccountData->accounts[flag].login_info);
				
				getDemographic(&acccountData->accounts[flag].demo_info);
				
				printf("*** New account added! ***\n\n");
				
				clearStandardInputBuffer();
				pauseExecution();
			}
		}
		else if (2 == selection)
		{
			int flag = findAccountbyIndex(0, acccountData->accounts, acccountData->ACCOUNT_MAX_SIZE, 1);
			
			if (flag > -1)
			{
				printf("\n");
				updateAccount(&acccountData->accounts[flag]);
			}
			else
			{
				printf("\nERROR:  Access Denied.\n\n");
				pauseExecution();
			}
		}
		else if (3 == selection)
		{
			int flag = findAccountbyIndex(0, acccountData->accounts, acccountData->ACCOUNT_MAX_SIZE, 1);
			int num = 0;

			if (flag > -1 && acccountData->accounts[flag].accNumber == account->accNumber)
			{
				printf("\nERROR: You can't remove your own account!\n\n");
				pauseExecution();
			}
			else if (flag > -1)
			{
				char userInput = 0;

				displayAccountDetailHeader();

				displayAccountDetailRecord(&acccountData->accounts[flag]);

				printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");

				userInput = getCharOption("YN");

				if (userInput == 'Y')
				{
					archieveAccount(acccountData, flag);

					printf("\n*** Account Removed! ***\n\n");

					pauseExecution();
					for (num = 0; num < acccountData->TICKET_MAX_SIZE; num++)
					{
						if (acccountData->tickets[num].accNumber == acccountData->accounts[flag].accNumber)
						{
							acccountData->tickets[num].ticketNumber = 0;
						}
					}

					acccountData->accounts[flag].accNumber = 0;
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
			displayAllAccountSummaryRecords(acccountData);
		}
		else if (5 == selection)
		{
			displayAllAccountDetailRecords(acccountData);
		}
		else if (6 == selection)
		{
			int exit = 0, selection = 0, num = 0, i = 0, j = 0;

			printf("\n");
			do
			{
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
				printf("------ ----- --------------- ------ ------------------------------ --------\n");

				for (j = 0; j <= acccountData->TICKET_MAX_SIZE; j++)
				{
					if (acccountData->tickets[j].messageCounter == 1)
					{
						printf("%06d %5d %-15s %-6s %-30s %5d\n", acccountData->tickets[j].ticketNumber, acccountData->tickets[j].accNumber, acccountData->tickets[j].mess->messageName, acccountData->tickets[j].ticketStatus == 0 ? "CLOSED" : "ACTIVE", acccountData->tickets[j].subjectLine, acccountData->tickets[j].messageCounter);
					}
				}
				
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("\nEnter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				
				selection = findTicket(acccountData->tickets, acccountData->TICKET_MAX_SIZE);
				
				if (selection == -1)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();
				}
				else if (selection == -3)
				{
					num = -1;
				}
				else
				{
					printf("\n================================================================================\n");
					printf("%06d (%s) Re: %s\n", acccountData->tickets[selection].ticketNumber, acccountData->tickets[selection].ticketStatus == 0 ? "CLOSED" : "ACTIVE", acccountData->tickets[selection].subjectLine);
					printf("================================================================================\n");

					for (i = 0; acccountData->tickets[selection].mess[i].messageType != 0 && i < acccountData->tickets[selection].messageCounter; i++)
					{
						printf("%s (%s):\n", acccountData->tickets[selection].mess[i].messageType == 'C' ? "CUSTOMER" : "AGENT", acccountData->tickets[selection].mess[i].messageName);
						printf("   %s\n\n", acccountData->tickets[selection].mess[i].messageDetails);
						if ((i + 1) % 5 == 0)
						{
							pauseExecution();
							exit = 1;
						}
						else
						{
							exit = 0;
						}
					}
					if (exit == 0) pauseExecution();
				}
			} while (num != -1);
			printf("\n");
		}
		else if (selection == 7)
		{
			int select = 0, exit = 0;

			printf("\n");
			
			do
			{
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				
				int i = 0;
				for (i = 0; i <= acccountData->TICKET_MAX_SIZE; i++)
				{
					if (acccountData->tickets[i].ticketStatus == 1 && acccountData->tickets[i].ticketNumber > 0)
					{
						printf("%06d %5d %-15s %-6s %-30s %5d\n", acccountData->tickets[i].ticketNumber, acccountData->tickets[i].accNumber, acccountData->tickets[i].mess->messageName, acccountData->tickets[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", acccountData->tickets[i].subjectLine, acccountData->tickets[i].messageCounter);

					}
				}

				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("\nEnter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				
				select = findTicket(acccountData->tickets, acccountData->TICKET_MAX_SIZE);
				
				if (select == -1)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();
				}
				else if (select == -3)
				{
					select = -3;
				}
				else
				{
					printf("\n================================================================================\n");
					printf("%06d (%s) Re: %s\n", acccountData->tickets[select].ticketNumber, acccountData->tickets[select].ticketStatus == 0 ? "CLOSED" : "ACTIVE", acccountData->tickets[select].subjectLine);
					printf("================================================================================\n");

					for (i = 0; acccountData->tickets[select].mess[i].messageType != 0 && i < acccountData->tickets[select].messageCounter; i++)
					{
						printf("%s (%s):\n", acccountData->tickets[select].mess[i].messageType == 'C' ? "CUSTOMER" : "AGENT", acccountData->tickets[select].mess[i].messageName);
						printf("   %s\n\n", acccountData->tickets[select].mess[i].messageDetails);
						if ((i + 1) % 5 == 0)
						{
							pauseExecution();
							exit = 1;
						}
						else
						{
							exit = 0;
						}
					}
					if (exit == 0) pauseExecution();
				}
			} while (select != -3);
			
			printf("\n");

		}
		else if (selection == 8)
		{
			int select = 0, exit = 0;
			printf("\n");
			do
			{
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				
				int i = 0;
				for (i = 0; i <= acccountData->TICKET_MAX_SIZE; i++)
				{
					if (acccountData->tickets[i].ticketStatus == 0 && acccountData->tickets[i].ticketNumber > 0)
					{
						printf("%06d %5d %-15s %-6s %-30s %5d\n", acccountData->tickets[i].ticketNumber, acccountData->tickets[i].accNumber, acccountData->tickets[i].mess->messageName, acccountData->tickets[i].ticketStatus == 0 ? "CLOSED" : "ACTIVE", acccountData->tickets[i].subjectLine, acccountData->tickets[i].messageCounter);
					}
				}
				
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("\nEnter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				
				select = findTicket(acccountData->tickets, acccountData->TICKET_MAX_SIZE);
				if (select == -1)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();
				}
				else if (select == -3)
				{
					select = -3;
				}
				else
				{

					printf("\n================================================================================\n");
					printf("%06d (%s) Re: %s\n", acccountData->tickets[select].ticketNumber, acccountData->tickets[select].ticketStatus == 0 ? "CLOSED" : "ACTIVE", acccountData->tickets[select].subjectLine);
					printf("================================================================================\n");

					for (i = 0; acccountData->tickets[select].mess[i].messageType != 1 && i < acccountData->tickets[select].messageCounter; i++)
					{

						printf("%s (%s):\n", acccountData->tickets[select].mess[i].messageType == 'C' ? "CUSTOMER" : "AGENT", acccountData->tickets[select].mess[i].messageName);
						printf("   %s\n\n", acccountData->tickets[select].mess[i].messageDetails);
						if ((i + 1) % 5 == 0)
						{
							pauseExecution();
							exit = 1;
						}
						else
						{
							exit = 0;
						}
					}
					if (exit == 0)pauseExecution();
				}

			} while (select != -3);

			printf("\n");

		}
		else if (selection == 9)
		{
			manageticket(acccountData, account);
		}
		else if (selection == 10)
		{
			const char filename[] = "tickets_arc.txt";

			int i = 0, j = 0, num = 0;

			FILE* fp = fopen(filename, "a");

			if (fp != NULL)
			{
				printf("\nAre you sure? This action cannot be reversed. ([Y]es|[N]o): ");

				char select = getCharOption("YN");

				if (select == 'Y')
				{
					for (i = 0; i < acccountData->TICKET_MAX_SIZE; i++)
					{
						if (acccountData->tickets[i].ticketStatus == 0 && acccountData->tickets[i].ticketNumber > 0)
						{
							fprintf(fp, "%d|%d|%d|%s|%d|", acccountData->tickets[i].ticketNumber, acccountData->tickets[i].accNumber, acccountData->tickets[i].ticketStatus, acccountData->tickets[i].subjectLine, acccountData->tickets[i].messageCounter);

							for (j = 0; j < acccountData->tickets[i].messageCounter; j++)
							{
								fprintf(fp, "%c|%s|%s|", acccountData->tickets[i].mess[j].messageType, acccountData->tickets[i].mess[j].messageName, acccountData->tickets[i].mess[j].messageDetails);
							}

							fprintf(fp, "\n");

							acccountData->tickets[i].ticketNumber = 0;

							num++;
						}
					}
					fclose(fp);
				}
			}
			else
			{
				printf("No closed tickets\n");
			}

			printf("\n*** %d tickets archived ***\n\n", num);

			pauseExecution();
		}
		else if (selection == 11)
		{
			int num = 0;
			const char filename[] = "accounts_arc.txt";
			FILE* fp = fopen(filename, "r");

			if (fp != NULL)
			{
				while (!(feof(fp)))
				{
					if (fgetc(fp) == '\n')
					{
						num++;
					}
				}
				fclose(fp);

				printf("\nThere are %d account(s) currently archived.\n\n", num);

				pauseExecution();

			}

			if (fp == NULL)
			{
				printf("\nThere are 0 account(s) currently archived.\n\n");
				pauseExecution();
			}
		}
		else if (selection == 12)
		{

			struct Ticket str[10] = { {0} };

			const char filename[] = "tickets_arc.txt";

			int i = 0, j = 0, msg = 0;

			FILE* fp = fopen(filename, "r");

			if (fp != NULL)
			{
				while (i < acccountData->TICKET_MAX_SIZE && fscanf(fp, "%d|%d|%d|%31[^|]|%d|", &str[i].ticketNumber, &str[i].accNumber, &str[i].ticketStatus, str[i].subjectLine, &str[i].messageCounter) == 5)
				{
					for (j = 0; j < str[i].messageCounter; j++)
					{
						fscanf(fp, "%c|%31[^|]|%151[^|]|", &str[i].mess[j].messageType, str[i].mess[j].messageName, str[i].mess[j].messageDetails);
					}
					i++;
					fprintf(fp, "\n");
					msg = msg+ j;
				}
				printf("\nThere are %d ticket(s) and a total of %d message(s) archived.\n\n", i, msg);
				pauseExecution();
				fclose(fp);
			}
			else
			{
				printf("\nThere are 0 ticket(s) and a total of 0 message(s) archived.\n\n");
				pauseExecution();
			}
		}
		else if (selection == 0)
		{
			int tickets = loadchanges(acccountData);
			int num = 0, i = 0;

			const char filename[] = "accounts.txt";

			FILE* fp = fopen(filename, "w");

			if (fp != NULL)
			{
				for (i = 0; i < acccountData->ACCOUNT_MAX_SIZE; i++)
				{
					if (acccountData->accounts[i].accNumber > 0)
					{
						fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n", acccountData->accounts[i].accNumber, acccountData->accounts[i].accType, acccountData->accounts[i].login_info.userName, acccountData->accounts[i].login_info.login_name, acccountData->accounts[i].login_info.password, acccountData->accounts[i].demo_info.birthYear, acccountData->accounts[i].demo_info.income, acccountData->accounts[i].demo_info.country);
						num++;
					}
				}
				fclose(fp);
			}

			printf("\nSaving session modifications...\n");
			printf("   %d account saved.\n   %d tickets saved.\n", num, tickets);
			printf("### LOGGED OUT ###\n");
			printf("\n");
		}
	}
}

void customermenu(AccountTicketingData* ticket, int index)
{
	int selection = -1;

	printf("\n");

	do
	{
		printf("CUSTOMER: %s (%d)\n", ticket->accounts[index].login_info.userName, ticket->accounts[index].accNumber);
		printf("==============================================\nCustomer Main Menu\n==============================================\n1) View your account detail\n2) Create a new ticket\n3) Modify an active ticket\n4) List my tickets\n----------------------------------------------\n0) Logout\n\nSelection: ");

		selection = getIntFromRange(0, 4);

		if (1 == selection)
		{
			printf("\n");

			displayAccountDetailHeader();
			
			displayAccountDetailRecord(&ticket->accounts[index]);
			
			printf("\n");
			
			pauseExecution();
		}
		else if (2 == selection)
		{
			newTicket(ticket, index);
		}
		else if (3 == selection)
		{
			int i = 0;
			
			printf("\nEnter ticket number: ");
			
			int ticketNum = getPositiveInteger();
			
			for (i = 0; i < ticket->TICKET_MAX_SIZE && ticketNum != ticket->tickets[i].ticketNumber; i++);
			
			if (ticket->tickets[i].accNumber == ticket->accounts[index].accNumber)
			{
				updateTicket(ticket, i, index);
			}
			else
			{
				printf("\nERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
			}
			
			pauseExecution();
		}
		else if (4 == selection)
		{
			int select = 0, num = 0, exit = 0;

			printf("\n");
			do
			{
				int i = 0;

				printf("------ ------ ------------------------------ --------\n");
				printf("Ticket Status Subject                        Messages\n");
				printf("------ ------ ------------------------------ --------\n");

				for (i = 0; i <= ticket->TICKET_MAX_SIZE; i++)
				{
					if (ticket->accounts[index].accNumber == ticket->tickets[i].accNumber)
					{
						printf("%06d %-6s %-30s %5d\n", ticket->tickets[i].ticketNumber, ticket->tickets[i].ticketStatus == 0 ? "CLOSED" : "ACTIVE", ticket->tickets[i].subjectLine, ticket->tickets[i].messageCounter);
					}
				}

				printf("------ ------ ------------------------------ --------\n");
				printf("\nEnter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");

				select = findTicket(ticket->tickets, ticket->TICKET_MAX_SIZE);

				if (select == -1)
				{
					printf("\nERROR: Invalid ticket number.\n\n");

				}
				else if (select == -3)
				{
					num = -1;
					exit = 1;
				}
				else
				{
					if (ticket->tickets[select].accNumber == ticket->accounts[index].accNumber)
					{
						printf("\n================================================================================\n");
						printf("%06d (%s) Re: %s\n", ticket->tickets[select].ticketNumber, ticket->tickets[select].ticketStatus == 0 ? "CLOSED" : "ACTIVE", ticket->tickets[select].subjectLine);
						printf("================================================================================\n");

						for (i = 0; i < ticket->tickets[select].messageCounter; i++)
						{
							printf("%s (%s):\n", ticket->tickets[select].mess[i].messageType == 'C' ? "CUSTOMER" : "AGENT", ticket->tickets[select].mess[i].messageName);
							printf("   %s\n\n", ticket->tickets[select].mess[i].messageDetails);
							if ((i + 1) % 5 == 0)
							{
								pauseExecution();
								exit = 1;
							}
							else
							{
								exit = 0;
							}
						}
					}
					else
					{

						printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n\n");

					}
				}
				if (exit == 0)
				{
					pauseExecution();
				}
			} while (num != -1);
			printf("\n");
		}
		else
		{
			int ticketsLoaded = loadchanges(ticket);

			printf("\nSaving session modifications...\n");
			printf("   %d tickets saved.", ticketsLoaded);
			printf("\n### LOGGED OUT ###\n\n");

		}
	}while (selection != 0);
}

void manageticket(AccountTicketingData* ticket, const Account* account)
{
	int i = 0, j = 0, flag = 0, selection = -1;

	printf("\nEnter ticket number: ");

	int ticketNumber = getPositiveInteger();

	for (i = 0; i < ticket->TICKET_MAX_SIZE && ticketNumber != ticket->tickets[i].ticketNumber; i++);

	for (j = 0; j < ticket->ACCOUNT_MAX_SIZE && ticket->tickets[i].accNumber != ticket->accounts[j].accNumber; j++);

	do
	{
		printf("\n----------------------------------------\nTicket %06d - Update Options\n----------------------------------------\n", ticket->tickets[i].ticketNumber);
		printf("Status  : %s\nSubject : %s\nAcct#   : %d\nCustomer: %s", ticket->tickets[i].ticketStatus == 0 ? "CLOSED" : "ACTIVE", ticket->tickets[i].subjectLine, ticket->tickets[i].accNumber, ticket->accounts[j].login_info.userName);
		printf("\n----------------------------------------\n1) Add a message\n2) Close ticket\n3) Re-open ticket\n0) Done\nSelection: ");

		selection = getIntFromRange(0, 3);

		if (1 == selection)
		{
			if (ticket->tickets[i].ticketStatus == 0)
			{
				printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
			}
			else
			{
				int num = ticket->tickets[i].messageCounter;

				if (ticket->tickets[i].mess[num].messageDetails != 0 && num == 20)
				{
					printf("\nERROR: Message limit has been reached, call ITS Support!\n");
				}
				else
				{
					printf("\nEnter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MAX_TICKET);
					
					getCString(ticket->tickets[i].mess[num].messageDetails, 0, MAX_TICKET);
					
					clearStandardInputBuffer();
					
					ticket->tickets[i].messageCounter = (ticket->tickets[i].messageCounter + 1);
					ticket->tickets[i].mess[num].messageType = 'A';
					
					strcpy(ticket->tickets[i].mess[num].messageName, account->login_info.userName);
				}
			}
		}
		else if (2 == selection)
		{
			if (ticket->tickets[i].ticketStatus == 0)
			{
				printf("\nERROR: Ticket is already closed!\n");
			}
			else
			{
				printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");

				char YorN = getCharOption("YN");

				if (YorN == 'Y')
				{
					if (ticket->tickets[i].messageCounter != 20)
					{
						printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");

						char YorN1 = getCharOption("YN");

						if (YorN1 == 'Y')
						{
							int k = ticket->tickets[i].messageCounter;

							printf("\nEnter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MAX_TICKET);
							
							getCString(ticket->tickets[i].mess[k].messageDetails, 0, MAX_TICKET);
							
							clearStandardInputBuffer();
							
							ticket->tickets[i].messageCounter = (ticket->tickets[i].messageCounter + 1);
							ticket->tickets[i].mess[k].messageType = 'A';
							
							strcpy(ticket->tickets[i].mess[k].messageName, account->login_info.userName);
						}
					}

					ticket->tickets[i].ticketStatus = 0;
					printf("\n*** Ticket closed! ***\n");

				}
			}
		}
		else if (3 == selection)
		{
			if (ticket->tickets[i].ticketStatus == 0)
			{
				printf("\nAre you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");

				char option = getCharOption("YN");
				
				if (option == 'Y')
				{
					ticket->tickets[i].ticketStatus = 1;
					printf("\n*** Ticket re-opened! ***\n");
				}
			}
			else
			{
				printf("\nERROR: Ticket is already active!\n");
			}
		}
		else
		{
			flag = -3;
			printf("\n");
		}
	} while (flag != -3);
}

int loadAccounts(Account* account, int maxAccounts)    // Takes input from file to get data of accounts
{
	const char filename[] = "accounts.txt";

	int i = 0;

	FILE* fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (i <= maxAccounts && fscanf(fp, "%d~%c~%31[^~]~%11[^~]~%9[^~]~%d~%lf~%31[^\n]\n", &account[i].accNumber, &account[i].accType, account[i].login_info.userName, account[i].login_info.login_name, account[i].login_info.password, &account[i].demo_info.birthYear, &account[i].demo_info.income, account[i].demo_info.country))
		{
			i++;
		}
		fclose(fp);
	}

	return(i - 1);

}

int loadTickets(Ticket* tickets, int max)  // Takes input from file to get data of tickets
{
	const char filename[] = "tickets.txt";

	int i = 0, j = 0;

	FILE* fp = fopen(filename, "r");

	if (fp != NULL)
	{
		while (i <= max && fscanf(fp, "%d|%d|%d|%31[^|]|%d|", &tickets[i].ticketNumber, &tickets[i].accNumber, &tickets[i].ticketStatus, tickets[i].subjectLine, &tickets[i].messageCounter) == 5)
		{
			for (j = 0; j < tickets[i].messageCounter; j++)
			{
				fscanf(fp, "%c|%31[^|]|%151[^|]|", &tickets[i].mess[j].messageType, tickets[i].mess[j].messageName, tickets[i].mess[j].messageDetails);
			}
			fprintf(fp, "\n");

			i++;
		}
		fclose(fp);
	}
	return(i);
}

int loadchanges(AccountTicketingData* tickets)  // load program data to File
{
	const char filename[] = "tickets.txt";
	int i = 0, j = 0, k = 0;
	int num = 0;

	FILE* fp = fopen(filename, "w");
	if (fp != NULL)
	{
		for (i = 0; i < tickets->TICKET_MAX_SIZE; i++)
		{
			for (k = 0; k < tickets->ACCOUNT_MAX_SIZE && tickets->tickets[i].accNumber != tickets->accounts[k].accNumber; k++);

			if (tickets->tickets[i].ticketNumber > 0 && tickets->tickets[i].accNumber == tickets->accounts[k].accNumber && tickets->accounts[k].accNumber > 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|", tickets->tickets[i].ticketNumber, tickets->tickets[i].accNumber, tickets->tickets[i].ticketStatus, tickets->tickets[i].subjectLine, tickets->tickets[i].messageCounter);

				for (j = 0; j < tickets->tickets[i].messageCounter; j++)
				{
					fprintf(fp, "%c|%s|%s|", tickets->tickets[i].mess[j].messageType, tickets->tickets[i].mess[j].messageName, tickets->tickets[i].mess[j].messageDetails);
				}

				fprintf(fp, "\n");
				num++;
			}
		}
		fclose(fp);
	}
	return(num);
}

void archieveAccount(AccountTicketingData* account, int index)  // Delete closed account and save thier data in archieved files
{
	const char filename[] = "tickets_arc.txt";
	int i = 0, j = 0;

	FILE* fp = fopen(filename, "a");

	if (fp != NULL)
	{
		for (i = 0; i < account->TICKET_MAX_SIZE; i++)
		{
			if (account->accounts[index].accNumber == account->tickets[i].accNumber && account->tickets[i].ticketStatus == 0 && account->tickets[i].ticketNumber > 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|", account->tickets[i].ticketNumber, account->tickets[i].accNumber, account->tickets[i].ticketStatus, account->tickets[i].subjectLine, account->tickets[i].messageCounter);
				for (j = 0; j < account->tickets[i].messageCounter; j++)
				{
					fprintf(fp, "%c|%s|%s|", account->tickets[i].mess[j].messageType, account->tickets[i].mess[j].messageName, account->tickets[i].mess[j].messageDetails);
				}
				fprintf(fp, "\n");

				account->tickets[i].ticketNumber = 0;
			}
		}
		fclose(fp);
	}

	const char secondfilename[] = "accounts_arc.txt";
	FILE* fp1 = fopen(secondfilename, "a");

	if (fp1 != NULL)
	{
		fprintf(fp1, "%d~%c~%s~%s~%s~%d~%lf~%s\n", account->accounts[index].accNumber, account->accounts[index].accType, account->accounts[index].login_info.userName, account->accounts[index].login_info.login_name, account->accounts[index].login_info.password, account->accounts[index].demo_info.birthYear, account->accounts[index].demo_info.income, account->accounts[index].demo_info.country);
		fclose(fp1);
	}
}

int findMaxAccbyNum(AccountTicketingData* account, int num)
{
	int i = 0, count = 0;
	if (num != 0)
	{
		for (i = 0; i <= account->TICKET_MAX_SIZE; i++)
		{
			if (account->tickets[i].ticketNumber > count)
			{
				count = account->tickets[i].ticketNumber;
			}
		}
	}
	else
	{
		for (i = 0; i <= account->ACCOUNT_MAX_SIZE; i++)
		{
			if (account->accounts[i].accNumber > count)
			{
				count = account->accounts[i].accNumber;
			}
		}
	}
	return count;
}

void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}