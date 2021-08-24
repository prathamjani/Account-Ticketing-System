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

#ifndef ACOUNT_H_
#define ACCOUNT_H_

#include <stdio.h>
#include "commonHelpers.h"

#define USER_NAME_MAX 10
#define USER_NAME_MIN 1
#define USER_ACC_MAX 30
#define USER_ACC_MIN 1
#define USER_PASWD 8
#define MAX_YRS 110
#define MIN_YRS 18
#define COUNTRY_NAME_MIN 1
#define COUNTRY_NAME_MAX 30

/*********************************************/
typedef struct Demographic
{
	int birth_year;
	double household_income;
	char country[COUNTRY_NAME_MAX + 1];
} Demographic;

/*********************************************/
typedef struct UserLogin
{
	char customer_account[USER_ACC_MAX + 1];
	char user_name[USER_NAME_MAX + 1];
	char password[USER_PASWD + 1];
}UserLogin;

/*********************************************/
typedef struct Account
{
	int account_num;
	char account_type; // A or C
	UserLogin userInfo;
	Demographic usersDemo;
}Account;


/***************************************************/
void getAccount(Account* accPtr);

/************************************************/
void getUserLogin(UserLogin* usrPtr);

/******************************************************/
void getDemographic(Demographic* demoPtr);

/*****************************************************/
void displayAccountSummaryHeader(void);

/*****************************************************/
void displayAccountSummaryRecord(const Account* inputAccount);

/***************************************************/
void displayAccountDetailHeader(void);

/******************************************************/
void displayAccountDetailRecord(const Account* inputAccount);

#endif