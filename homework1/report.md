# 51115110

作業一

## 解題說明(題目一)

題目要求寫出遞迴跟非遞迴的 Ackermann 函數

### 以下為遞迴

### 解題策略

1. 根據題目給的判斷將其轉換成函式
2. 透過主程式呼叫函式並輸出結果

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;
int ack(int m, int n){
    if(m == 0){
        return n + 1;
    }else if(n == 0){
        return ack(m - 1, 1);
    }else{
        return ack(m - 1, ack(m, n - 1));
    }
    
}
int main()
{
    int ans = ack(2, 3);
    cout << ans << "\n";
    return 0;
}
```

## 效能分析

1. 時間複雜度：根據m的輸入成超指數增長(我不會算)
2. 空間複雜度：O(2**n)。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m$ &n$ | 預期輸出 | 實際輸出 |
|----------|-----------------|----------|----------|
| 測試一   | $m = 1$ $n = 2$ | 4        | 4        |
| 測試二   | $m = 2$ $n = 3$ | 9        | 9        |
| 測試三   | $m = 3$ $n = 2$ | 29       | 29       |
| 測試四   | $m = 4$ $n = 1$ | 65533    | 65533    |
| 測試五   | $m = 1$ $n = 4$ | 6        | 6        |

### 結論

1. 程式能正確計算Ackermann 函數的輸出
2. m越大，所需計算時間越多，符合預期。  

## 效能量測

### 量測程式

使用clock來做計算

以下為測量程式碼:

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int call_count = 0;
int max_depth = 0;
int current_depth = 0;

int ack(int m, int n){
    call_count++;
    current_depth++;
    if (current_depth > max_depth) max_depth = current_depth;
    
    int ans;
    if(m == 0){
        ans = n + 1;
    }else if(n == 0){
        ans = ack(m - 1, 1);
    }else{
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
```

### 五項測試案例所需時間

| 測試案例 | 輸入參數 $m$ &n$ | 預期時間 | 實際時間 |
|----------|-----------------|----------|----------|
| 測試一   | $m = 1$ $n = 2$ | 0.001ms  | 0.001ms  |
| 測試二   | $m = 2$ $n = 3$ | 0.001ms  | 0.002ms  |
| 測試三   | $m = 3$ $n = 2$ | 0.003ms  | 0.005ms  |
| 測試四   | $m = 4$ $n = 1$ | 50000ms  | 21649.7ms|
| 測試五   | $m = 1$ $n = 4$ | 0.005ms  | 0.001ms  |

### 以下為非遞迴

### 解題策略

1. 使用動態配置的二維陣列來做查表
2. 再加上用堆疊的方式模擬遞迴

## 程式實作

以下為主要程式碼：

```cpp
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;


int** memo = nullptr;
int memo_rows = 0;
int memo_cols = 0;


void ensure_memo_size(int m, int n) {
    int new_rows = max(memo_rows, m + 1);
    int new_cols = max(memo_cols, n + 1);

    if (new_rows > memo_rows) {
        int** new_memo = new int*[new_rows];
        for (int i = 0; i < new_rows; ++i) {
            if (i < memo_rows)
                new_memo[i] = memo[i];
            else {
                new_memo[i] = new int[new_cols];
                for (int j = 0; j < new_cols; ++j)
                    new_memo[i][j] = -1;
            }
        }
        for (int i = 0; i < memo_rows; ++i) {
            int* new_row = new int[new_cols];
            for (int j = 0; j < new_cols; ++j)
                new_row[j] = (j < memo_cols) ? memo[i][j] : -1;
            delete[] memo[i];
            new_memo[i] = new_row;
        }
        delete[] memo;
        memo = new_memo;
        memo_rows = new_rows;
        memo_cols = new_cols;
    } else if (new_cols > memo_cols) {
        for (int i = 0; i < memo_rows; ++i) {
            int* new_row = new int[new_cols];
            for (int j = 0; j < new_cols; ++j)
                new_row[j] = (j < memo_cols) ? memo[i][j] : -1;
            delete[] memo[i];
            memo[i] = new_row;
        }
        memo_cols = new_cols;
    }
}


int ackermann(int m_init, int n_init) {
    const int STACK_SIZE = 1000000;
    int* stack_m = new int[STACK_SIZE];
    int* stack_n = new int[STACK_SIZE];
    int top = 0;

    stack_m[top] = m_init;
    stack_n[top] = n_init;
    top++;

    while (top > 0) {
        top--;
        int m = stack_m[top];
        int n = stack_n[top];

        ensure_memo_size(m, n);

        if (memo[m][n] != -1) {
            if (top == 0) {
                int result = memo[m][n];
                delete[] stack_m;
                delete[] stack_n;
                return result;
            }
            stack_n[top - 1] = memo[m][n];
            continue;
        }

        int result;
        if (m == 0) {
            result = n + 1;
        } else if (n == 0) {
            stack_m[top++] = m - 1;
            stack_n[top - 1] = 1;
            continue;
        } else {
            stack_m[top++] = m - 1;
            stack_m[top++] = m;
            stack_n[top - 1] = n - 1;
            continue;
        }

        memo[m][n] = result;
        if (top == 0) {
            delete[] stack_m;
            delete[] stack_n;
            return result;
        }
        stack_n[top - 1] = result;
    }

    delete[] stack_m;
    delete[] stack_n;
    return -1;
}

int main() {
    int m = 4, n = 1;


    memo = nullptr;
    memo_rows = memo_cols = 0;

    int result = ackermann(m, n);
    cout << "Ack(" << m << ", " << n << ") = " << result << endl;

    for (int i = 0; i < memo_rows; ++i)
        delete[] memo[i];
    delete[] memo;

    return 0;
}

```

## 效能分析

同上

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m$ &n$ | 預期輸出 | 實際輸出 |
|----------|-----------------|----------|----------|
| 測試一   | $m = 1$ $n = 2$ | 4        | 4        |
| 測試二   | $m = 2$ $n = 3$ | 9        | 9        |
| 測試三   | $m = 3$ $n = 2$ | 29       | 29       |
| 測試四   | $m = 4$ $n = 1$ | 65533    | 65533    |
| 測試五   | $m = 1$ $n = 4$ | 6        | 6        |

### 編譯與執行指令

同上

### 結論

1. 程式能正確計算Ackermann 函數的輸出
2. 即便用了查表法在做計算時還是很花時間

## 效能量測

### 量測程式

使用clock來做計算

以下為測量程式碼:

```cpp
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;


int** memo = nullptr;
int memo_rows = 0;
int memo_cols = 0;

int call_count = 0;
int max_depth = 0;
int current_depth = 0;

void ensure_memo_size(int m, int n) {
    int new_rows = max(memo_rows, m + 1);
    int new_cols = max(memo_cols, n + 1);

    if (new_rows > memo_rows) {
        int** new_memo = new int*[new_rows];
        for (int i = 0; i < new_rows; ++i) {
            if (i < memo_rows)
                new_memo[i] = memo[i];
            else {
                new_memo[i] = new int[new_cols];
                for (int j = 0; j < new_cols; ++j)
                    new_memo[i][j] = -1;
            }
        }
        for (int i = 0; i < memo_rows; ++i) {
            int* new_row = new int[new_cols];
            for (int j = 0; j < new_cols; ++j)
                new_row[j] = (j < memo_cols) ? memo[i][j] : -1;
            delete[] memo[i];
            new_memo[i] = new_row;
        }
        delete[] memo;
        memo = new_memo;
        memo_rows = new_rows;
        memo_cols = new_cols;
    } else if (new_cols > memo_cols) {
        for (int i = 0; i < memo_rows; ++i) {
            int* new_row = new int[new_cols];
            for (int j = 0; j < new_cols; ++j)
                new_row[j] = (j < memo_cols) ? memo[i][j] : -1;
            delete[] memo[i];
            memo[i] = new_row;
        }
        memo_cols = new_cols;
    }
}


int ackermann(int m_init, int n_init) {
    const int STACK_SIZE = 1000000;
    int* stack_m = new int[STACK_SIZE];
    int* stack_n = new int[STACK_SIZE];
    int top = 0;
    
    call_count++;
    current_depth++;
    if (current_depth > max_depth) max_depth = current_depth;
    
    stack_m[top] = m_init;
    stack_n[top] = n_init;
    top++;

    while (top > 0) {
        top--;
        int m = stack_m[top];
        int n = stack_n[top];

        ensure_memo_size(m, n);

        if (memo[m][n] != -1) {
            if (top == 0) {
                int result = memo[m][n];
                delete[] stack_m;
                delete[] stack_n;
                return result;
            }
            stack_n[top - 1] = memo[m][n];
            continue;
        }

        int result;
        if (m == 0) {
            result = n + 1;
        } else if (n == 0) {
            stack_m[top++] = m - 1;
            stack_n[top - 1] = 1;
            continue;
        } else {
            stack_m[top++] = m - 1;
            stack_m[top++] = m;
            stack_n[top - 1] = n - 1;
            continue;
        }

        memo[m][n] = result;
        if (top == 0) {
            delete[] stack_m;
            delete[] stack_n;
            return result;
        }
        stack_n[top - 1] = result;
    }
    
    
    current_depth--;
    delete[] stack_m;
    delete[] stack_n;
    return -1;
}

int main() {
    int m = 3, n = 3;


    memo = nullptr;
    memo_rows = memo_cols = 0;
    clock_t start = clock();
    int result = ackermann(m, n);
    clock_t end = clock();
    double dur = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << "Ack(" << m << ", " << n << ") = " << result << endl;
    cout << dur << "\n";

    for (int i = 0; i < memo_rows; ++i)
        delete[] memo[i];
    delete[] memo;

    return 0;
}

```

### 五項測試案例所需時間

| 測試案例 | 輸入參數 $m$ &n$ | 預期時間 | 實際時間 |
|----------|-----------------|----------|----------|
| 測試一   | $m = 1$ $n = 2$ | 0.001ms  | 0.001ms  |
| 測試二   | $m = 2$ $n = 3$ | 0.001ms  | 0.018ms  |
| 測試三   | $m = 3$ $n = 2$ | 0.003ms  | 0.0051ms  |
| 測試四   | $m = 4$ $n = 1$ | 50000ms  | 21648.2ms|
| 測試五   | $m = 1$ $n = 4$ | 0.005ms  | 0.002ms  |

## 解題說明(題目二)

題目要求透過遞迴函數算出一集合的所有子集合

### 解題策略

1. 透過遞迴層層決定要加入的元素
2. 對於每個元素分別做加入即不加入

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int MAX = 10;  

void printSub(int sub[], int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", sub[i]);
    }
    printf("]\n");
}

void PowerSet(int set[], int n, int index, int sub[], int subSize) {
    if (index == n) {
        printSub(sub, subSize);
        return;
    }
    PowerSet(set, n, index + 1, sub, subSize);
    sub[subSize] = set[index];
    PowerSet(set, n, index + 1, sub, subSize + 1);
}

int main() {
    int S[] = {2, 4, 5};
    int n = sizeof(S) / sizeof(S[0]);

    int sub[MAX]; 
    PowerSet(S, n, 0, sub, 0);

    return 0;
}

```

## 效能分析

1. 時間複雜度：O(2^n * n)
2. 空間複雜度：O(n)

## 測試與驗證

### 測試案例

| 測試案例 | 輸入                 | 輸出                                                                                                            |
|----------|---------------------|-----------------------------------------------------------------------------------------------------------------|
| 測試一   | S[] = {2, 4, 5}     | [ ],[ 5 ],[ 4 ],[ 4 5 ],[ 2 ],[ 2 5 ],[ 2 4 ],[ 2 4 5 ]                                                         |
| 測試二   | S[] = {3, 6, 5, 7}  | [ 5 7 ],[ 6 ],[ 6 7 ],[ 6 5 ],[ 6 5 7 ],[ 3 ],[ 3 7 ],[ 3 5 ],[ 3 5 7 ],[ 3 6 ],[ 3 6 7 ],[ 3 6 5 ],[ 3 6 5 7 ] |

### 結論

1. 程式能正確列出所有子集合。  

## 效能量測

### 量測程式

使用clock來做計算

以下為測量程式碼:

```cpp
#include <iostream>
#include <cstdio>

using namespace std;
int call_count = 0;
int max_depth = 0;
int current_depth = 0;
const int MAX = 10;  

void printSub(int sub[], int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", sub[i]);
    }
    printf("]\n");
}

void PowerSet(int set[], int n, int index, int sub[], int subSize) {
    call_count++;
    current_depth++;
    if (current_depth > max_depth) max_depth = current_depth;
    
    if (index == n) {
        printSub(sub, subSize);
        return;
    }
    PowerSet(set, n, index + 1, sub, subSize);
    sub[subSize] = set[index];
    PowerSet(set, n, index + 1, sub, subSize + 1);
    current_depth--;
}

int main() {
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
```

### 五項測試案例所需時間

| 測試案例  | 輸入               | 預期時間  | 實際時間  |
|----------|--------------------|----------|----------|
| 測試一   | S[] = {2, 4, 5}    | 0.01ms  | 0.044ms  |
| 測試二   | S[] = {3, 6, 5, 7} | 0.05ms  | 0.05ms  |

## 心得

學到了怎麼使用github、如何自己寫出一些標頭內的功能、對程式效能的部分有更加深刻的理解
