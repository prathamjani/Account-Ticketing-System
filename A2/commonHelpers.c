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
#include "commonHelpers.h"
#include <time.h>
#include <stdio.h>
#include<ctype.h>

int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}
int getInteger(void)
{
	char newLine;
	int value = 0, j = 0;
	do
	{
		j = scanf("%d%c", &value, &newLine);
		if (j != 2 || newLine != '\n')
		{
			if (newLine != '\n') printf("ERROR: Value must be an integer: ");

			clearStandardInputBuffer();
		}
	} while (j != 2 || newLine != '\n');
	return value;
	clearStandardInputBuffer();
}
int getPositiveInteger(void)
{
	int value = 0;
	int j = 0;
	while (j != 1)
	{
		value = getInteger();
		if (value >= 0)
		{
			j = 1;
		}
		else printf("ERROR: Value must be positive or zero: ");
	}
	return value;
}
double getDouble(void)
{
	char newLine;
	double value = 0;
	double j = 0;
	do
	{
		j = scanf("%lf%c", &value, &newLine);
		if (j != 2 || newLine != '\n')
		{
			if (newLine != '\n') printf("ERROR: Value must be a double floating-point number: ");

			clearStandardInputBuffer();
		}
	} while (j != 2 || newLine != '\n');
	return value;
	clearStandardInputBuffer();
}
double getPositiveDouble(void)
{
	double value = 0;
	int j = 0;
	while (j != 1)
	{
		value = getDouble();
		if (value > 0)
		{
			j = 1;
		}
		else printf("ERROR: Value must be a positive double floating-point number: ");
	}
	return value;
}
int getIntFromRange(int lower, int higher)
{
	int value = 0, j = 0;
	while (j != 1)
	{
		value = getInteger();
		if (value >= lower && value <= higher)
		{
			j = 1;

		}
		else
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lower, higher);
			j = 2;
		}
	}

	return value;
}

char getCharOption(const char* string)
{
	char value = 0;
	char newline = 0;
	int j = 0;
	int i = 0;
	do
	{
		scanf("%c%c", &value, &newline);
		if (newline == '\n')
		{
			i = 0;
			while (string[i] != '\0' && j == 0)
			{
				if (string[i] == value)
				{
					j = 1;
				}
				else
				{
					i++;
				}
			}
		}
		else
		{
			clearStandardInputBuffer();
		}
		if (j == 0)
		{
			printf("ERROR: Character must be one of [%s]: ", string);
		}
	} while (j == 0);
	return value;
}

void getCString(char* p1, int p2, int p3)
{
	char string[150];
	char x[150];
	int  i = 0, j = 0;
	while (j != 1)
	{
		scanf(" %[^\n]", string);
		char* str;
		for (i = 0; string[i] != '\0'; i++)
		{

			x[i] = string[i];
		}
		x[i] = '\0';

		if (p2 == p3)
		{

			if (i != p3)printf("ERROR: String length must be exactly %d chars: ", p3);
			else
			{
				str = x;
				while (*str != '\0')
				{
					*p1 = *str;
					p1++;
					str++;
				}
				*p1 = '\0';
				j = 1;
			}
		}
		else
		{

			if (i > p3)
			{
				printf("ERROR: String length must be no more than %d chars: ", p3);
			}
			else if (i < p2)
			{
				printf("ERROR: String length must be between %d and %d chars: ", p2, p3);
			}

			else
			{


				str = string;


				if (p2 == 1)
				{
					while (*str != '\0')
					{
						*p1 = toupper(*str);
						p1++;
						str++;
					}
				}
				else
				{
					while (*str != '\0')
					{
						*p1 = *str;
						p1++;
						str++;
					}
				}

				*p1 = '\0';
				j = 1;
			}
		}
	}
}

