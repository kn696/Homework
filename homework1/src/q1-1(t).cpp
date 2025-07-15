#include <iostream>
#include <cstdlib>
using namespace std;

int call_count = 0;
int max_depth = 0;
int current_depth = 0;

int ack(int m, int n)
{
    call_count++;
    current_depth++;
    if (current_depth > max_depth)
        max_depth = current_depth;

    int ans;
    if (m == 0)
    {
        ans = n + 1;
    }
    else if (n == 0)
    {
        ans = ack(m - 1, 1);
    }
    else
    {
        ans = ack(m - 1, ack(m, n - 1));
    }

    current_depth--;
    return ans;
}
int main()
{
    int m = 4, n = 1;
    clock_t start = clock();
    int ans = ack(m, n);
    clock_t end = clock();
    double dur = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << ans << "\n";
    cout << dur << "\n";
    return 0;
}