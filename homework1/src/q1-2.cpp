#include <cstdlib>
#include <iostream>
using namespace std;

int **create_memo(int m_size, int n_size)
{
    int **memo = new int *[m_size];
    for (int i = 0; i < m_size; ++i)
    {
        memo[i] = new int[n_size];
        for (int j = 0; j < n_size; ++j)
            memo[i][j] = -1; // -1 表示尚未計算
    }
    return memo;
}

int ack(int m, int n, int **memo)
{
    if (m == 0)
        return n + 1;
    if (memo[m][n] != -1)
        return memo[m][n];

    int result;
    if (n == 0)
        result = ack(m - 1, 1, memo);
    else
        result = ack(m - 1, ack(m, n - 1, memo), memo);

    memo[m][n] = result;
    return result;
}

int main()
{
    int m, n;
    cout << "請輸入 m n：";
    cin >> m >> n;

    // 動態配置 memo 表
    int m_size = m + 1;
    int n_size = n + 1;

    int **memo = create_memo(m_size, max(100, n_size)); // 為避免 recursive call n+1、n+2 導致 out of bound，可設定較大的 n_size

    int result = ack(m, n, memo);
    cout << "Ack(" << m << ", " << n << ") = " << result << endl;

    // 釋放記憶體
    for (int i = 0; i < m_size; ++i)
        delete[] memo[i];
    delete[] memo;

    return 0;
}
