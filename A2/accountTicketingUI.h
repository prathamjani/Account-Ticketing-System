// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Pratham Jayesh Jani
//  Student ID    : 134947209
//  Student Email : pjjani@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#include"account.h"
#include"ticket.h"

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

typedef struct AccountTicketingData
{
	struct Account* accounts;				// array of accounts
	const int ACCOUNT_MAX_SIZE;				// maximum elements for account array
	struct Ticket* tickets;					// array of tickets
	const int TICKET_MAX_SIZE;				// maximum elements for ticket array 
}AccountTicketingData;



void applicationStartup(AccountTicketingData* account);

int findTicket(Ticket* tickets, int ticketArraySize);

void displayAllAccountSummaryRecords(AccountTicketingData* account);

void displayAllAccountDetailRecords(AccountTicketingData* account);

int menuLogin(AccountTicketingData* accountt);

void menuAgent(AccountTicketingData* accountData, const Account* account);

void customermenu(AccountTicketingData* ticket, int index);

int loadAccounts(Account* account, int maxAccounts);

int loadTickets(Ticket* tickets, int max);

int loadchanges(AccountTicketingData* tickets);

void archieveAccount(AccountTicketingData* account, int index);

void manageticket(AccountTicketingData* ticket, const Account* account);


int findMaxAccbyNum(AccountTicketingData* account, int num);

void pauseExecution(void);


void newTicket(AccountTicketingData* ticket, int index);

void updateTicket(AccountTicketingData* ticket, int i, int acc);

#endif // !account_Ticketing_UI_H_