#include <iostream>
#include <cstdlib>
using namespace std;

int call_count = 0;
int max_depth = 0;
int current_depth = 0;

int ack(int m, int n)
{
    const int MAX_STACK = 10000;
    int stack[MAX_STACK];
    int top = 0;
    call_count++;
    current_depth++;
    if (current_depth > max_depth)
        max_depth = current_depth;

    stack[top++] = m;

    while (top > 0)
    {
        m = stack[--top];
        if (m == 0)
        {
            n = n + 1;
        }
        else if (n == 0)
        {
            stack[top++] = m - 1;
            n = 1;
        }
        else
        {
            stack[top++] = m - 1;
            stack[top++] = m;
            n = n - 1;
        }

        if (top >= MAX_STACK)
        {
            cout << "Stack overflow!" << endl;
            return -1;
        }
    }
    return n;
}

int main()
{
    int m = 2, n = 3;
    clock_t start = clock();
    int ans = ack(m, n);
    clock_t end = clock();
    double dur = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << ans << "\n";
    cout << dur << "\n";
    return 0;
}