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
#include <stdio.h>
#include <time.h>
#include "commonHelpers.h"

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
	int num = 0;
	char c = 0;
	int flag = 0;
	do
	{
		scanf("%d%c", &num, &c);
		if (c == '\n')
		{
			flag = 1;
		}
		else
		{
			printf("ERROR: Value must be an integer: ");
			clearStandardInputBuffer();
		}
	} while (flag == 0);
	return num;
}

int getPositiveInteger(void)
{
	int num = 0;
	int flag = 0;
	while (!flag)
	{
		num = getInteger();
		if (num > 0)
		{
			return num;
		}
		else
		{
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}
	}
	return 0;
}

int  getIntFromRange(int lower, int upper)
{
	int num = 0;
	int flag = 0;
	do
	{
		num = getInteger();
		if (num >= lower && num <= upper)
		{
			flag = 1;
		}
		else
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lower, upper);
		}
	} while (flag == 0);
	return num;
}

double  getDouble(void)
{
	double num = 0;
	char c = 0;
	int flag = 0;
	do
	{
		scanf("%lf%c", &num, &c);
		if (c == '\n')
		{
			flag = 1;
		}
		else
		{
			printf("ERROR: Value must be a double floating-point number: ");
			clearStandardInputBuffer();
		}
	} while (flag == 0);
	return num;
}

double getPositiveDouble(void)
{
	double num = 0;
	int flag = 0;
	while (!flag)
	{
		num = getDouble();
		if (num > 0)
		{
			return num;
		}
		else
		{
			printf("ERROR: Value must be a positive double floating-point number: ");
		}
	}
	return 0;
}

char getCharOption(const char* str_input)
{
	char cInput = 0;
	char char_EOL = 0;
	int flag = 0;
	int i = 0;
	do
	{
		scanf("%c%c", &cInput, &char_EOL);
		if (char_EOL == '\n')
		{
			i = 0;
			while (str_input[i] != 0 && flag == 0)
			{
				if (str_input[i] == cInput)
				{
					flag = 1;
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
		if (flag == 0)
		{
			printf("ERROR: Character must be one of [%s]: ", str_input);
		}
	} while (flag == 0);
	return cInput;
}

void getCString(char* cstring_input, int lower, int upper)
{
	char char_EOL = 0;
	int flag = 0;
	int t_flg = 0;
	char cstring_scan[100];
	int count = 0;
	int i = 0;
	do
	{
		scanf("%[^\n]%c", cstring_scan, &char_EOL);
		if (char_EOL == '\n')
		{
			count = 0;
			flag = 0;
			while (flag == 0)
			{
				if (cstring_scan[count] == 0)
				{
					flag = 1;
				}
				else
				{
					count++;
				}
			}
			if (count >= lower && count <= upper)
			{
				for (i = 0; i < count; i++)
				{
					cstring_input[i] = cstring_scan[i];
				}
				cstring_input[count] = 0;
				t_flg = 1;
			}
			else if (count != lower && upper == lower)
			{
				printf("ERROR: String length must be exactly %d chars: ", lower);

			}
			else if (count > upper)
			{
				printf("ERROR: String length must be no more than %d chars: ", upper);
			}
			else
			{
				printf("ERROR: String length must be between %d and %d chars: ", lower, upper);

			}

		}

	} while (t_flg == 0);
	return;
}