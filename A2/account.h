// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Pratham Jayesh Jani
//  Student ID    : 134947209
//  Student Email : pjjani@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

// Define Macros
#define MAX_UNAME 15
#define MIN_UNAME 1
#define MAX_USER_ACC 30
#define MIN_USER_ACC 1
#define USER_PASS 8
#define MAX_YEARS 110
#define MIN_YEARS 18
#define MIN_COUNTRY 1
#define MAX_COUNTRY 30
#define MAX_TICKET 150

typedef struct Demographic
{
	int birthYear;
	double income;
	char country[MAX_COUNTRY + 1];
} Demographic;

typedef struct UserLogin
{
	char userName[MAX_USER_ACC + 1];
	char login_name[11];
	char password[USER_PASS+1];
} UserLogin;

typedef struct Account
{
	int accNumber;
	char accType; // Could be A (agent) or C (customer)
	struct UserLogin login_info;
	struct Demographic demo_info;
} Account;

// Function prototypes

void getAccount(Account* accPtr);

void getUserLogin(UserLogin* usrPtr);

void getDemographic(Demographic* demoPtr);

void updateAccount(Account* account);

void updateUserLogin(UserLogin* userInfo);

void updateDemographic(Demographic* demo);

void displayAccountSummaryHeader(void);

void displayAccountSummaryRecord(const Account* account);

void displayAccountDetailHeader(void);

void displayAccountDetailRecord(const Account* account);

int findAccountbyIndex(int account, const Account accounts[], int maxArr, int num);

#endif