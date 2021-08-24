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


void applicationStartup(Account accounts[], int arrSize);

int menuLogin(const Account accounts[], int arrSize);

void menuAgent(Account accounts[], int arrSize, const Account* account);

int findAccountIndexByAccountNumOfYour(int account, const Account accounts[], int arrSize, int needAcctNum);

int findAccountIndexByAccountNumOfThe(int account, const Account accounts[], int arrSize, int needAcctNum);

void displayAllAccountSummaryRecords(const Account accounts[], int arrSize);

void displayAllAccountDetailRecords(const Account accounts[], int arrSize);

void pauseExecution(void);

void updateAccount(Account* account);

void updateUserLogin(UserLogin* userInfo);

void updateDemographic(Demographic* demo);