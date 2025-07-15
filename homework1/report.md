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

1. 時間複雜度：根據m的輸入成指數增長。(最明顯)
2. 空間複雜度：O(ack(m, n))。

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

在online compiler內執行，沒有執行指令與編譯

### 結論

1. 程式能正確計算Ackermann 函數的輸出。  
2. m越大，所需計算時間越多，符合預期。  
3. 測試案例將m跟n以不同大小排列，驗證程式可行性，及所需時間差異

## 效能量測

### 量測程式

使用clock來做計算
以下為主要程式碼:

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

1. 在原有的基礎上將呼叫自己的過程拿掉，改為透過堆疊的方式來取代遞迴

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int ack(int m, int n) {
    const int MAX_STACK = 10000;
    int stack[MAX_STACK];
    int top = 0;

    stack[top++] = m;

    while (top > 0) {
        m = stack[--top];
        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            stack[top++] = m - 1;
            n = 1;
        } else {
            stack[top++] = m - 1; 
            stack[top++] = m;     
            n = n - 1;
        }

        if (top >= MAX_STACK) {
            cout << "Stack overflow!" << endl;
            return -1;
        }
    }
    return n;
}

int main() {
    int m = 2, n = 3;
    int ans = ack(m, n);
    cout << ans << endl;
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

1. 程式能正確計算Ackermann 函數的輸出。  

## 效能量測

### 量測程式

使用clock來做計算
以下為主要程式碼:

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int call_count = 0;
int max_depth = 0;
int current_depth = 0;

int ack(int m, int n) {
    const int MAX_STACK = 10000;
    int stack[MAX_STACK];
    int top = 0;
    call_count++;
    current_depth++;
    if (current_depth > max_depth) max_depth = current_depth;
    
    stack[top++] = m;

    while (top > 0) {
        m = stack[--top];
        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            stack[top++] = m - 1;
            n = 1;
        } else {
            stack[top++] = m - 1; 
            stack[top++] = m;     
            n = n - 1;
        }

        if (top >= MAX_STACK) {
            cout << "Stack overflow!" << endl;
            return -1;
        }
    }
    return n;
}

int main() {
    int m = 2, n = 3;
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

### 編譯與執行指令

在online compiler內執行，沒有執行指令與編譯

### 結論

1. 程式能正確列出所有子集合。  

## 效能量測

### 量測程式

使用clock來做計算
以下為主要程式碼:

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
