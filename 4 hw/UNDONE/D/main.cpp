#include <iostream>
#include <algorithm>

std::pair<int, int> table[100000][16 + 1];
std::pair<int, int> Arr[100000];

std::pair<int, int> Max(std::pair<int, int> i1, std::pair<int, int> i2)
{
	if (i1.first > i2.first)
		return i1;
  else
    return i2;
}

int main()
{
	FILE* Read;
	FILE* Write;
	Read = fopen("index-max.in", "r");
	int n, L, R, q;
	fscanf(Read, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(Read, "%d", &Arr[i].first);
		Arr[i].second = i + 1;
	}

	for (int i = 0; i < n; ++i)
		table[i][0] = Arr[i];

	for (int j = 1; j <= 16; ++j)
		for (int i = 0; i <= n - (1 << j); ++i)
			table[i][j] = Max(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);

	fscanf(Read, "%d", &q);
	Write = fopen("index-max.out", "w");
	for (int i = 0; i < q; ++i)
	{
		fscanf(Read, "%d %d", &L, &R);
		--L;
		--R;
		std::pair<int, int> answer;
		answer.first = -1;
		for (int j = 16; j >= 0; --j)
		{
			if (L + (1 << j) - 1 <= R)
			{
				answer = Max(answer, table[L][j]);
				L += 1 << j;
			}
		}
		fprintf(Write, "%d\n", answer.second);
	}
	fclose(Read);
	fclose(Write);
	return 0;
}
