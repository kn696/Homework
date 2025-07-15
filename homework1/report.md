# 51115110

作業一

## 解題說明

題目要求寫出遞迴跟非遞迴的 Ackermann 函數

### 解題策略(遞迴)

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

## 心得
