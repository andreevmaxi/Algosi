#include <iostream>
#include <algorithm>
#include <fstream>

const int k = 16;
const int N = 1e5;
const int MIN_VALUE = -1; 
struct Item
{
	int value;
	int index;
};

Item table[N][k + 1];
Item Arr[N];

Item Max(Item i1, Item i2)
{
	if (i1.value > i2.value)
	{
		return i1;
	}
	return i2;
}

int main()
{
	FILE* rf;
	FILE* wf;
	rf = fopen("index-max.in", "r");
	int n, L, R, q;
	fscanf(rf, "%d", &n);
	fgetc(rf);
	for (int i = 0; i < n; i++)
	{
		fscanf(rf, "%d", &Arr[i].value);
		fgetc(rf);
		Arr[i].index = i + 1;
	}

	for (int i = 0; i < n; i++)
	{
		table[i][0] = Arr[i];
	}
	for (int j = 1; j <= k; j++) 
	{
		for (int i = 0; i <= n - (1 << j); i++)
		{
			table[i][j] = Max(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
		}
	}

	fscanf(rf, "%d", &q);
	wf = fopen("index-max.out", "w");
	for (int i = 0; i < q; i++) 
	{
		fscanf(rf, "%d %d", &L, &R);
		L--;
		R--;
		Item answer;
		answer.value = MIN_VALUE;
		for (int j = k; j >= 0; j--) 
		{
			if (L + (1 << j) - 1 <= R) 
			{
				answer = Max(answer, table[L][j]);
				L += 1 << j;
			}
		}
		fprintf(wf, "%d\n", answer.index);
	}
	fclose(rf);
	fclose(wf);
	return 0;
}