#include <iostream>
#include <cstdio>

using namespace std;
int call_count = 0;
int max_depth = 0;
int current_depth = 0;
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
    call_count++;
    current_depth++;
    if (current_depth > max_depth)
        max_depth = current_depth;

    if (index == n)
    {
        printSub(sub, subSize);
        return;
    }
    PowerSet(set, n, index + 1, sub, subSize);
    sub[subSize] = set[index];
    PowerSet(set, n, index + 1, sub, subSize + 1);
    current_depth--;
}

int main()
{
    int S[] = {3, 6, 5, 7};
    int n = sizeof(S) / sizeof(S[0]);

    int sub[MAX];
    clock_t start = clock();
    PowerSet(S, n, 0, sub, 0);
    clock_t end = clock();
    double dur = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << dur << "\n";
    return 0;
}