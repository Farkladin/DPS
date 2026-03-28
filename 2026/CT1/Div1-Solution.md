## 1. 벌집
바깥쪽 칸의 수가 6씩 증가한다.

```C++
#include <iostream>
using namespace std;

int main() {
    int N; cin >> N;
    
    if (N == 1) {
        cout << "1\n";
    } else {
        --N;
        int a = 6, cnt = 1;
        while (N > 0){
            N -= a;
            ++cnt;
            a += 6;
        }
        cout << cnt << "\n";
    }
    
    return 0;
}

```

---
## 2. 집합
$1$, $2$, $\dots$, $20$ 만이 원소가 될 수 있다. 충분히 작으므로 bitset으로 관리한다.

```C
#include <stdio.h>
#include <stdint.h>
#include <string.h>

char oper[10];

int main(void) {
    int M; scanf("%d", &M);
    
    uint64_t S = 0;
    int x;
    while (M--) {
        scanf("%6s %d\n", oper, &x);
        
        switch (oper[0]) {
            case 'a':
                if (oper[1] == 'd') {
                    S |= 1 << x;
                } else {
                    S = 0xFFFFFFFF;
                }
                break;
                
            case 'r':
                S &= ~(1 << x);
                break;
                    
            case 'c':
                printf("%d\n", (S & (1 << x)) != 0);
                break;
                    
            case 't':
                S ^= 1 << x;
                break;
                    
            case 'e':
                S = 0;
                break;
        }
    }
    
    return 0;
}

```

---
## 3. 연산자 끼워넣기
백트래킹 문제이다.
각 연산자의 남은 개수, 현재 연산자의 영향을 받을 숫자, 현재 상태를 인자로 하는 재귀 함수를 만들어 해결할 수 있다.
```C++
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

using pii = pair<int, int>;
int A[13], N;

inline void update(pii &a, const pii &b) {
    a.first = std::max(a.first, b.first);
    a.second = std::min(a.second, b.second);
}

pii sol(int i, int a, int b, int c, int d, int cur) {
    if (i > N) return pii{cur, cur};
    
    pii ret{-1e9, 1e9};
    
    if (a) {
        pii nxt = sol(i + 1, a - 1, b, c, d, cur + A[i]);
        update(ret, nxt);
    }
    
    if (b) {
        pii nxt = sol(i + 1, a, b - 1, c, d, cur - A[i]);
        update(ret, nxt);
    }
    
    if (c) {
        pii nxt = sol(i + 1, a, b, c - 1, d, cur * A[i]);
        update(ret, nxt);
    }
    
    if (d) {
        pii nxt = sol(i + 1, a, b, c, d - 1, cur / A[i]);
        update(ret, nxt);
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>N;
    for(int i=1; i<=N; ++i) {
        cin >> A[i];
    }
    
    int a, b, c, d; cin >> a >> b >> c >> d;
    auto [mx, mn] = sol(2, a, b, c, d, A[1]);
    std::cout << mx << "\n" << mn <<"\n";
    
    return 0;
}

```

---
## 4. 컨테이너 벨트 위의 로봇
```C++
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int A[203], B[203], R[203], C[203];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    // 입력
    size_t N, K; cin >> N >> K;
    int cnt = 0;
    
    for (size_t i = 1; i <= 2 * N; ++i) {
        cin >> A[i];
        cnt += A[i] == 0;
    }
    
    const size_t n = N << 1;
    
    int ans = 0;
    auto next_i = [&n](const size_t &i)->size_t {
        return i == n ? 1 : i + 1;
    };
    
    while (1) {
        ++ans;
        
        // STEP 1
        for (size_t i = 1; i <= n; ++i) {
            B[next_i(i)] = A[i];
            C[next_i(i)] = R[i];
        }
        
        memcpy(A, B, sizeof(B));
        memcpy(R, C, sizeof(C));
        
        R[N] = 0; // 로봇 내리기
        
        // STEP 2
        for (size_t i = N - 1; i > 0; --i) {
            if (A[i + 1] > 0 && !R[i + 1] && R[i]) {
                R[i + 1] = R[i];
                R[i] = 0;
                --A[i + 1];
                
                if (A[i + 1] == 0) {
                    ++cnt;
                }
            }
        }
        
        R[N] = 0; // 로봇 내리기
        
        // STEP 3
        if (A[1] > 0) {
            --A[1];
            if(A[1] == 0) ++cnt;
            R[1] = 1;
        }
        
        // STEP 4
        if(cnt >= K) {
            cout << ans << "\n";
            
            return EXIT_SUCCESS;
        }
    }
    
    return EXIT_SUCCESS;
}

```
