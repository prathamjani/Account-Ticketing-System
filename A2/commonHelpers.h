// ===================================================================================
//  Assignment: 2 
//  Milestone : 2
// ===================================================================================
//  Student Name  : Pratham Jayesh Jani
//  Student ID    : 134947209
//  Student Email : pjjani@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

#include <stdio.h>
#include <time.h>

int currentYear(void);
void clearStandardInputBuffer(void);
int getInteger(void);
int getPositiveInteger(void);
int  getIntFromRange(int lower, int upper);
double  getDouble(void);
double getPositiveDouble(void);
char getCharOption(const char* str_input);
void getCString(char* cstringValue, int lower, int upper);

#endif