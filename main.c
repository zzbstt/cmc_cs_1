#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

int gen()
{ // генерирование рандомного числа
	int x = 0;
	x = rand() * rand();
	if (rand() % 2 == 1) x = -x;
	return x;
}

void genmass(int *a, int n)
{ // генерирование массива
	for (int i = 0; i < n; ++i)
    {
		a[i] = gen();
	}
	return;
}

void swap(int a, int b, int *counter)
{ // свап
	int tmp = a;
	(*counter)++;
	a = b;
	b = tmp;
}

int cmp(int a, int b, int *compare)
{//сравнение
    (*compare)++;
    if (abs(a) < abs(b) || (b == INT_MIN)) return -1;
    else if (abs(a) > abs(b) || (a == INT_MIN)) return 1;
    else return 0;
}

void simplechoice(int *a, int n, int *counter, int *compare)
{ //сортировка выбором
	for (int i = 0; i < n; ++i)
        {						//ищем элемент на текующую позицию
		int minpos = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (cmp(a[minpos], a[j], compare) > 0)
            {
				minpos = j;
			}
		}
		if (minpos != i) swap(a[minpos], a[i], counter);//меняем его с нашим элементом
	}
}

void quicksort(int *a, int n, int *counter, int *compare)
{//быстрая сортировка
    int i = 0;
    int j = n - 1;
    int mid = a[n / 2];

    //Делим массив
    do {
        while(cmp(a[i], mid, compare) < 0)
        {
            i++;
        }
        while(cmp(a[j], mid, compare) > 0)
        {
            j--;
        }
        //Меняем элементы местами
        if (i <= j)
        {
            if (!(abs(a[i]) == abs(mid) && abs(a[i]) == abs(mid)))
            {
                swap(a[i], a[j], counter);
            }
            i++;
            j--;
        }
    } while (i <= j);
    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > 0)
    {
        quicksort(a, j + 1, counter, compare);
    }
    if (i < n)
    {
        quicksort(&a[i], n - i, counter, compare);
    }
}

void print(int *a, int n)
{ // вывод массива
	for (int i = 0; i < n; ++i)
    {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main(void) {
	srand(time(0));
	int counter = 0, compare = 0; // счетчики свапов и сравнений
	int n;
	printf("enter a number of elements\nn = ");
	scanf("%d", &n);
	printf("\n");
	if (n <= 0) {
		printf("error");
		return 0;
	}
	else printf("ok\n\n");
	int sorttype;
	printf("select sort type\n1 - simple choice sort\n2 - quick sort\ntype of sort = ");
	scanf("%d", &sorttype);
	printf("\n");
	if (sorttype != 1 && sorttype != 2)
	{
		printf("error!");
		return 0;
	}
	else
	{
		printf("ok\n\n");
	}
	int arraytype;
	printf("select array type\nordered - 1\nreverse order - 2\nrandom - 3\ntype of array = ");
	scanf("%d", &arraytype);
	printf("\n");
	if (arraytype > 3 && arraytype < 1) {
		printf("error!");
		return 0;
	}
	else
	{
		printf("ok\n\n");
	}
	int *a = calloc(n, sizeof(int)); //создаем массив длины n
	if (arraytype == 1)
	{
		int b = gen();
		for (int i = 0; i < n; ++i)
		{
			a[i] = b;
			b += abs(gen());
			if (b < a[i]) b = a[i] + 12;
		}
	}
	else if (arraytype == 2)
	{
		int b = gen();
		for (int i = 0; i < n; ++i)
		{
			a[i] = b;
			b -= abs(gen());
			if (b > a[i]) b = a[i] - 12;
		}
	}
	else
	{
		genmass(a, n);
	}
	if (sorttype == 1)
	{
		simplechoice(a, n, &counter, &compare);
	}
	else
    {
		quicksort(a, n, &counter, &compare);
	}
    printf("Correct sort!\nswaps = %d\ncompares = %d\n\n", counter, compare);
    printf("\n");
    print(a, n);
	free(a);
	return 0;
}
