#include <iostream>
#include <cstdio>

using namespace std;

const int MAX = 10;

void printSub(int sub[], int size)
{
    printf("[ ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", sub[i]);
    }
    printf("]\n");
}

void PowerSet(int set[], int n, int index, int sub[], int subSize)
{
    if (index == n)
    {
        printSub(sub, subSize);
        return;
    }
    PowerSet(set, n, index + 1, sub, subSize);
    sub[subSize] = set[index];
    PowerSet(set, n, index + 1, sub, subSize + 1);
}

int main()
{
    int S[] = {2, 4, 5};
    int n = sizeof(S) / sizeof(S[0]);

    int sub[MAX];
    PowerSet(S, n, 0, sub, 0);

    return 0;
}
