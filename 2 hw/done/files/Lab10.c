#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int ACaseRead(int* BSize, FILE* f, int** buffer, int* MinPtr) {
	int tmp;
	int intSize = 0;

	while (fscanf(f, "%d ", &tmp) == 1) {
		++intSize;
		if (*BSize < intSize) {
			*BSize *= 2;
			*buffer = (int*)realloc(*buffer, *BSize);
			if (*buffer == NULL) {
				return 0;
			}
		}

		*(*buffer + intSize - 1) = tmp;
		if (tmp < *(*buffer + *MinPtr)) {
			*MinPtr = intSize - 1;
		}
	}
	fclose(f);

	if (intSize < *BSize) {
		*BSize = intSize;
		*buffer = (int*)realloc(*buffer, *BSize);
	}

	return 1;
}

int ACaseProcessing(int* buffer, int BSize, unsigned long long* ans) {
	for (int i = 0; i < BSize; i++) {
		*ans += *(buffer + i) * (*(buffer + i));
	}

	return 1;
}

int ACaseOutput(FILE* f, int* buffer, int MinPtr, int BSize, unsigned long long ans) {
	for (int i = 0; i < MinPtr; i++) {
		fprintf(f, "%d ", *(buffer + i));
	}
	fprintf(f, "%llu ", ans);

	for (int i = MinPtr; i < BSize; i++) {
		fprintf(f, "%d ", *(buffer + i));
	}
	return 1;
}


int BCaseRead(int* BSize, char** buffer, FILE* f) {
	char tmp;
	int StrSize = 0;
	rewind(f);

	tmp = (char)fgetc(f);
	while (tmp != EOF) {
		if (tmp != '\r') {
			StrSize++;
			if (*BSize < StrSize) {
				*BSize += 10;
				*buffer = (char*)realloc(*buffer, *BSize);
				if (*buffer == NULL) {
					return 0;
				}
			}

			*(*buffer + StrSize - 1) = tmp;
		}
		tmp = (char)fgetc(f);
	}

	if (StrSize < *BSize) {
		*BSize = StrSize + 1;
		*buffer = (char*)realloc(*buffer, *BSize);
	}
	else {
		(*BSize)++;
		*buffer = (char*)realloc(*buffer, *BSize);
	}
	fclose(f);

	*(*buffer + *BSize - 1) = (char)0;
	return 1;
}

int BCaseProcessing(int BSize, char* buffer) {
	for (int i = 0; i < BSize; i++) {
		if ((*(buffer + i) > 64) && (*(buffer + i) < 91)) {
			*(buffer + i) += 32;
		}
	}

	return 1;
}

int BCaseOutput(FILE* f, char* buffer, int bSize) {
	int i = 0;

	while (i < bSize && *(buffer + i) != (char)0) {
		fprintf(f, "%c", *(buffer + i));
		i++;
	}

	return 1;
}

void Error(int err) {
	switch (err) {
	case(1): {
		printf("Err1: No file found!\n");
	}
			 break;

	case(2): {
		printf("Err2: Not enough memory!\n");
	}
			 break;

	case(3): {
		printf("Err3: Can't open file in case a!\n");
	}
			 break;
	}

	abort();
	return;
}

int ACASE(FILE* f) {
	int bSize = 4;
	int* buffer = (int*)calloc(4, sizeof(int));
	int MinPtr = 0;

	if (!ACaseRead(&bSize, f, &buffer, &MinPtr)) {
		Error(2);
	}

	unsigned long long ans = 0;

	ACaseProcessing(buffer, bSize, &ans);

	f = fopen("f.txt", "w");

	if (f == NULL) {
		Error(3);
	}

	ACaseOutput(f, buffer, MinPtr, bSize, ans);

	fclose(f);
	printf("A case done!\n");
	return 1;
}

int BCASE(FILE* f) {
	int bSize = 4;
	char* buffer = (char*)calloc(4, sizeof(char));

	if (!BCaseRead(&bSize, &buffer, f)) {
		Error(2);
	}

	BCaseProcessing(bSize, buffer);

	f = fopen("g.txt", "w");

	BCaseOutput(f, buffer, bSize);
	fclose(f);
	printf("B case done!\n");
	return 1;
}

int main() {
	FILE* f;
	FILE* t = fopen("t.txt", "w");
	f = fopen("f.txt", "rb");
	if (f == NULL) {
		Error(1);
	}

	char Ans[5];

	printf("What case do you want to use now?(a||b)\n");
	scanf("%s", Ans);

	if (Ans[0] == 'a') {
		ACASE(f);
	}
	else {
		BCASE(f);
	}

	return 0;
}
