// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Pratham Jayesh Jani
//  Student ID    : 134947209
//  Student Email : pjjani@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#ifndef TICKET_H_
#define TICKET_H_

#include"account.h"

typedef struct Message
{
	char messageType;
	char messageName[31];
	char messageDetails[151];
}Message;

typedef struct Ticket
{
	int ticketNumber;
	int accNumber;
	int ticketStatus;
	char subjectLine[31];
	int messageCounter;
	struct Message mess[20];
}Ticket;

#endif // !TICKET_H_
