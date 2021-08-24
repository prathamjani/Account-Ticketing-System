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
#include<string.h>
#include<ctype.h>
#include"ticket.h"
#include"commonHelpers.h"
#include"accountTicketingUI.h"


void updateTicket(AccountTicketingData* ticket, int i, int acc)
{
	int selection = 0, flag = 0, status = 0;

	do
	{

		if (ticket->tickets[i].ticketStatus == 0)
		{
			printf("\nERROR: Ticket is closed - changes are not permitted.\n\n");
			flag = -5;
		}
		else
		{

			int num = 0;

			printf("\n----------------------------------------\nTicket %06d - Update Options\n----------------------------------------\n", ticket->tickets[i].ticketNumber);
			printf("Status  : %s\nSubject : %s\n----------------------------------------\n", ticket->tickets[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", ticket->tickets[i].subjectLine);
			printf("1) Modify the subject\n2) Add a message\n3) Close ticket\n0) Done\nSelection: ");

			selection = getIntFromRange(0, 3);

			if (selection == 2)
			{
				num = ticket->tickets[i].messageCounter;

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
					ticket->tickets[i].mess[num].messageType = 'C';
					strcpy(ticket->tickets[i].mess[num].messageName, ticket->accounts[acc].login_info.userName);
				}
			}
			else if (selection == 1)
			{
				printf("\nEnter the revised ticket SUBJECT (30 chars. maximum): ");
				getCString(ticket->tickets[i].subjectLine, 0, 30);
				clearStandardInputBuffer();

			}
			else if (selection == 3)
			{
				printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				char confirm = getCharOption("YN");
				if (confirm == 'Y' && ticket->tickets[i].messageCounter < 20)
				{
					printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
					char confirm1 = getCharOption("YN");
					if (confirm1 == 'N')
					{
						printf("\n*** Ticket closed! ***\n\n");
						flag = -5, status = 1;
					}
					else
					{
						num = ticket->tickets[i].messageCounter;
						if (ticket->tickets[i].mess[num].messageDetails != 0 && num == 20)
						{
							printf("\nERROR: Message limit has been reached, call ITS Support!\n");
						}
						else
						{
							printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
							getCString(ticket->tickets[i].mess[num].messageDetails, 0, 150);
							clearStandardInputBuffer();
							ticket->tickets[i].messageCounter = ticket->tickets[i].messageCounter + 1;
							strcpy(ticket->tickets[i].mess[num].messageName, ticket->accounts[acc].login_info.userName);
							ticket->tickets[i].mess[num].messageType = 'C';
						}
						printf("\n*** Ticket closed! ***\n\n");
						status = 1, flag = -5;
					}
				}
				else if (confirm == 'Y' && ticket->tickets[i].messageCounter == 20)
				{
					printf("\n*** Ticket closed! ***\n\n");
					status = 1, flag = -5;
				}

			}
			else if (selection == 0)
			{
				flag = -5;
				printf("\n");
			}
			if (status == 1) ticket->tickets[i].ticketStatus = 0;
		}
	} while (flag != -5);

}



void newTicket(AccountTicketingData* ticket, int index)
{
	int maxTicket = 0, i = 0;

	maxTicket = findMaxAccbyNum(ticket, 1);

	for (i = 0; i < ticket->TICKET_MAX_SIZE && ticket->tickets[i].ticketNumber > 0; i++);

	if (i == ticket->TICKET_MAX_SIZE && ticket->tickets[i].accNumber != 0)
	{
		printf("\nERROR: Ticket listing is FULL, call ITS Support!\n\n");
		pauseExecution();
	}
	else
	{
		ticket->tickets[i].mess[0].messageType = ticket->accounts[index].accType;
		ticket->tickets[i].ticketNumber = (maxTicket + 1);
		ticket->tickets[i].ticketStatus = 1;
		ticket->tickets[i].messageCounter = 1;
		ticket->tickets[i].accNumber = ticket->accounts[index].accNumber;

		strcpy(ticket->tickets[i].mess[0].messageName, ticket->accounts[index].login_info.userName);

		printf("\nNew Ticket (Ticket#:%06d)", ticket->tickets[i].ticketNumber);
		printf("\n----------------------------------------\nEnter the ticket SUBJECT (30 chars. maximum): ");
		getCString(ticket->tickets[i].subjectLine, 0, 30);

		printf("\nEnter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MAX_TICKET);
		getCString(ticket->tickets[i].mess[0].messageDetails, 0, MAX_TICKET);
		printf("\n*** New ticket created! ***\n\n");

		clearStandardInputBuffer();
		pauseExecution();

	}
}

