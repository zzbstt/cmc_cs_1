#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

int ll = INT_MIN / 3, rr = INT_MAX / 3;

int gen(int l, int r)
{ // генерирование рандомного числа
    int x = 0;
    x = rand() * rand();
    x = abs(x);
    return l + x % (r - l + 1);
}

int max(int a, int b)
{
    if (a > b) return a;
    else return b;
}

int min(int a, int b)
{
    if (a > b) return b;
    else return a;
}


void genmass(int *a, int n)
{ // генерирование массива
    for (int i = 0; i < n; ++i)
    {
        a[i] = gen(ll, rr);
    }
    return;
}

void swap(int *a, int *b, int *counter)
{ // свап
    int tmp = *a;
	if (a != b) (*counter)++;
    *a = *b;
    *b = tmp;
}

int cmp(int a, int b, int *compare)
{//сравнение
    (*compare)++;
    if (b == INT_MIN && a != INT_MIN) return -1;
    else if (a == INT_MIN && b != INT_MIN) return 1;
	else if (a == INT_MIN && b == INT_MIN) return 0;
    if (abs(a) < abs(b)) return -1;
    else if (abs(a) > abs(b)) return 1;
    else return 0;
}

void simplechoice(int *a, int n, int *counter, int *compare)
{ //сортировка выбором
    for (int i = 0; i < n; ++i)
        {                       //ищем элемент на текующую позицию
        int minpos = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (cmp(a[minpos], a[j], compare) > 0)
            {
                minpos = j;
            }
        }
        if (minpos != i) swap(&a[minpos], &a[i], counter);//меняем его с нашим элементом
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
            if (!(abs(a[i]) == abs(mid) && abs(a[j]) == abs(mid)))
            {
                swap(&a[i], &a[j], counter);
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
    int bob = gen(1,2);
    printf("%d ", bob);
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
        a[0] = gen(ll, rr);
        for (int i = 1; i < n; ++i)
        {
            int znak = gen(1, 2);
            int s = gen(abs(a[i - 1]), min(abs(a[i - 1]) + 1000, rr));
            if (znak == 1)
            {
                a[i] = s;
            }
            else
            {
                a[i] = -s;
            }
        }
    }
    else if (arraytype == 2)
    {
        a[0] = gen(ll, rr);
        for (int i = 1; i < n; ++i)
        {
            int znak = gen(1, 2);
            int s = gen(max(0, abs(a[i-1])-1000), abs(a[i-1]));
            if (znak == 1)
            {
                a[i] = s;
            }
            else
            {
                a[i] = -s;
            }
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
