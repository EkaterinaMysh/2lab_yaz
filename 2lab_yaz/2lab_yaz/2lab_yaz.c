#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int digits[8][10];
int digits_num[8][10];
int number_of_sum = 1;
int already_used = 0;

int if_kolvo(int flag)
{
	int i = 0; int j = 1;
	if (number_of_sum == 2)
		if ((digits[0][0] != digits[7][0]) && (digits[1][0] != digits[7][0]))
		{
			if (already_used != 0)
			{
				i = j; j = 0; already_used = 0;
			}
			if (flag != 6)
			{
				digits_num[i][1] = flag;
				digits_num[j][1] = 10 - flag;
				flag++;
				already_used++;
			}
			else {
				digits_num[i][1] = flag;
				digits_num[j][1] = flag;
				flag++;
			}
		}
	return flag;
}


int sravnen() {
	int k = 2, i1, j1, h, j;
	for (i1 = 0; i1 < number_of_sum; i1++)
		if (digits_num[i1][1] == 0)
			return k;
	if (digits_num[7][1] == 0)
		return k;

	for (i1 = 0; i1 < number_of_sum; i1++)
		for (j1 = 1; j1 <= digits_num[i1][0]; j1++)
		{
			for (h = 0; h < 8; h++)
				for (j = 1; j <= digits_num[h][0]; j++)
				{
					if ((digits_num[h][0] > 0) && ((digits_num[h][j] == digits_num[i1][j1]) && (digits[h][j] != digits[i1][j1])))
						return k;
				}

		}


	for (j1 = 1; j1 <= digits_num[7][0]; j1++)
		for (j = 1; j <= digits_num[7][0]; j++)
			if ((digits_num[7][j] == digits_num[7][j1]) && (digits[7][j] != digits[7][j1]))
				return k;
	k = 1;
	return k;
}

int srav(int a, int slag, int digit)
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 1; j <= digits[i][0]; j++)
			if (digits[i][j] == digits[slag][digit])
				digits_num[i][j] = digits_num[slag][digit];
	}

}

int recurs(int slag, int digit)
{
	int res = 1, flag = 0;
	int i = 1, j;
	time_t start, end;
	start = clock();
	for (i = 0; i < number_of_sum; i++)
		for (j = 1; j <= digits_num[i][0]; j++)
		{
			if (j == 1)
				digits_num[i][j] = 1;
			else
				digits_num[i][j] = flag;
			srav(digits_num[i][j], i, j);
			flag++;
		}
	for (j = 1; j <= digits_num[7][0]; j++)
		if (j == 1)
			digits_num[7][j] = 1;
		else
			digits_num[7][j] = 0;
try_harder:
	//printmat();
	{
		int as = sravnen();
		if (as == 1) {
			if (sum() == 0)
			{
				printmat();
				printf("\n!!!!\n");
				end = clock();
				printf("\n%f\n", ((double)end - start) / ((double)CLOCKS_PER_SEC));
				exit(0);
			}
			else
			{
				plus();
				goto try_harder;
			}
		}
		else
		{
			plus();
			goto try_harder;
		}
	}

}

int plus()
{
	int i = 7, i1 = number_of_sum, j = digits_num[i][0], k, flag = 1;
	try :
		if (digits_num[i][j] != 9)
		{
			digits_num[i][j]++;
			srav(digits_num[i][j], i, j);
		}
		else
		{
			if (j == 1)
			{
				if (i == (number_of_sum - 1))
					flag = if_kolvo(flag);
				else
				{
					digits_num[i][1] = 1;
				}
				srav(digits_num[i][1], i, 1);
				if (i == 7)
					i = number_of_sum;
				i--;
				j = digits_num[i][0];
				goto try;
			}
			else if (j != 1)
			{
				digits_num[i][j] = 0;
				srav(digits_num[i][1], i, 1);
				j--;
				goto try;
			}
			else
			{
				digits_num[i][j] = 1;
				srav(digits_num[i][j], i, j);
				goto try;
			}
		}

}


int printmat()
{
	int i1, j;
	for (i1 = 0; i1 <= 7; i1++) {
		for (j = 1; j <= digits_num[i1][0]; j++)
			if (digits_num[i1][0] != 0)
				printf("%i", digits_num[i1][j]);
		if (i1 == 6)
			printf("=");
		else
			if (i1 == 7)
				printf("\n");
			else  if (digits_num[i1][0] != 0 && i1 != (number_of_sum - 1))
				printf("+");

	}
}


int sum()
{
	int a = 0, b = 0, res_sum = 0, i, j;
	for (i = 0; i < number_of_sum; i++)
	{
		for (j = 1; j <= digits_num[i][0]; j++)
			a = a * 10 + digits_num[i][j];
		b += a;
		a = 0;
	}
	a = 0;
	for (j = 1; j <= digits_num[7][0]; j++)
		a = a * 10 + digits_num[7][j];
	if (b == a)
		res_sum = 0;
	else res_sum = abs(a - b);
	return res_sum;
}


int main()
{

	char stroka[50];
	gets(stroka);

	int kolvo = 0, i = 0, j = 0, fal = 0;
	for (i = 0; i < (int)strlen(stroka); i++)
	{
		int a = (int)(stroka[i]);
		if (stroka[i] == '=') {
			digits[j][0] = kolvo; number_of_sum = j + 1; j = 7; fal = i + 1; kolvo = 0;
		}
		else if (stroka[i] == '+') {
			fal = i + 1;  digits[j][0] = kolvo; kolvo = 0; j++;
		}
		else if (stroka[i] == ' ') fal++;
		else {
			digits[j][i - fal + 1] = a; kolvo++;
		}
	}
	digits[7][0] = kolvo;


	for (i = 0; i <= 7; i++) {
		for (j = 0; j <= digits[i][0]; j++)
		{
			if (j == 0) digits_num[i][j] = digits[i][j];
			else digits_num[i][j] = 10;
		}
	}


	int k = 0, res;
	recurs(0, 1);

}
