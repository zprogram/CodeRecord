// 20180208_�����ַ���ȥ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>


void printArray(char **, size_t);
void selectionSort(char **, size_t);
size_t removeDuplicates(char **a, int n);

char *fileList[] = {
	"input1.txt", "input1.txt", "input5.txt", "input8.txt",
	"input1.txt", "input9.txt", "input9.txt" };

int main(int argc, char *argv[]) {
	char **strPtrArray;
	size_t i, len = sizeof(fileList) / sizeof(char *), newSize;

	/*
	* Allocate and initialize an array of pointers to the
	* C-strings in the fileList array. Sorting this array and
	* removing duplicates is then just a matter of rearranging
	* and moving pointers, rather than moving the C-strings
	* themselves; easier and more efficient this way.
	*/
	strPtrArray = (char**)calloc(len, sizeof(char*));
	for (i = 0; i < len; i++) {
		strPtrArray[i] = fileList[i];
	}

	/* Display */
	printf("\nUnsorted:\n");
	printArray(strPtrArray, len);

	/* Sort */
	selectionSort(strPtrArray, len);

	/* Display */
	printf("\nSorted:\n");
	printArray(strPtrArray, len);

	/* Remove duplicates */
	newSize = removeDuplicates(strPtrArray, len);

	/* Display */
	printf("\nDuplicates removed:\n");
	printArray(strPtrArray, newSize);

	/* Free */
	free(strPtrArray);

	return 0;
}

/*
* Selection Sort of array of pointers to C-strings. This is
* a normal selection sort, but it knows that to compare
* values it needs to call strcmp.
*/
void selectionSort(char **a, size_t rows) {
	int i, j, min;
	char *t;

	for (i = 0; i < rows; i++) {
		min = i;
		for (j = i + 1; j < rows; j++) {
			if (strcmp(a[j], a[min]) < 0) {  //string1 �� string2С��
				min = j;
			}
		}
		t = a[min];
		a[min] = a[i];
		a[i] = t;
	}
}

/*
* Delete duplicate entries in the given sorted array of
* pointers to C-string. Return the new size of the array.
*/
size_t removeDuplicates(char **a, int n) {
	int newSize = n, i = 0, j;

	while (i < newSize - 1) {
		j = i + 1;
		while ((j < newSize) && (strcmp(a[j], a[i]) == 0)) 
			++j;
		if ((j - i) > 1) {
			if (j < newSize) {
				memcpy(&a[i + 1], &a[j], (n - j) * sizeof(char *));  //�����ظ�ֵ
			}
			newSize -= (j - i - 1);
		}
		++i;
	}
	return newSize;
}

void printArray(char **a, size_t rows) {
	size_t i;

	for (i = 0; i < rows; i++) {
		printf("%s\n", a[i]);
	}
}