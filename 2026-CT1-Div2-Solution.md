## 1. A+B

```C++
#include <iostream>
int main(){
    int A,B;std::cin>>A>>B;
    std::cout<<A+B<<std::endl;
    return 0;
}
```

```OCaml
let () =
    Scanf.scanf "%d %d\n" (fun a b ->
        Printf.printf "%d\n" (a+b)
    )
```

```Python
A,B = map(int, input().split())
print(A + B)
```

```Golfscript
~+
```

---

## 2. A/B
```C++
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    double a,b; cin >> a >> b;
    cout << fixed << setprecision(10) << a/b << "\n";
    return 0;
}
```

```OCaml
let () =
    Scanf.scanf "%f %f\n" (fun a b ->
        Printf.printf "%.10f\n" (a /. b)
    )
```

```Python
A,B = map(int, input().split())
print(A / B)
```

---

## 3. 두 수 비교하기
```C++
#include <iostream>

int main() {
    int A, B; std::cin >> A >> B;
    
    std::cout << (A > B ? ">" : (A < B ? "<" : "==")) << "\n";
    
    return 0;
}

```

```OCaml
let () =

    Scanf.scanf "%d %d\n" (fun a b ->
        Printf.printf "%s\n" (if a > b then ">" else (if a < b then "<" else "=="))

    )
```

```Python
a,b=map(int,input().split())
print('>' if a>b else ('<' if a<b else '=='))
```

---

## 4. 펠린드롬인지 확인하기
```C++
#include <iostream>
#include <iostream>
#include <string>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    string s;cin>>s;
    cout << (s == string(s.rbegin(), s.rend())) << "\n";
    return 0;
}

```

```OCaml
let () =
    Scanf.scanf "%s\n" (fun s ->
    let len = String.length s in
	    let rev_s = String.init len (fun i -> s.[len - 1 - i]) in
		    let ans = if s = rev_s then 1 else 0 in
			    Printf.printf "%d\n" ans
	)
```

```Python
S = input()
print(int(S == S[::-1]))
```

---

## 5. 별 찍기 - 7
```C++
#include <iostream>
#include <string>

using namespace std;
using namespace std::string_literals;

using str = string;

string operator*(const str rhs, int lhs) {
    string ret = "";
    while (lhs--) ret += rhs;
    
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    
    int N; cin >> N;
    
    for(int i=1; i<=N; ++i) cout << " "s * (N - i) + "*"s * (2 * i - 1) + "\n";
    for(int i=N-1; i>0; --i) cout << " "s * (N - i) + "*"s * (2 * i - 1) + "\n";
    
    return 0;
}


```

```OCaml
let () =
    Scanf.scanf "%d\n" @@ fun n ->
        let rec f i =
            if i <= n then (
                Printf.printf "%s%s\n" (String.make (n-i) ' ') (String.make (2 * i - 1) '*');
                f (i + 1)
            )
            in
        
        let rec g i =
            if i > 0 then (
                Printf.printf "%s%s\n" (String.make (n-i) ' ') (String.make (2 * i - 1) '*');
                g (i - 1)
            )
            in
        
        f 1;
        g (n - 1)

```

```Python
N = int(input())

for i in range(N):
    print(" " * (N - i - 1) + "*" * (2 * i + 1))
    
for i in range(1,N):
    print(" " * i + "*" * (2 * (N - i) - 1))

```

---

## 6. 소인수분해
```C++
#include <iostream>
#include <cstdint>

using namespace std;

using ll = uint64_t;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll N; cin >> N;
    ll d = 2;
    
    while (N > 1) {
        while (N % d == 0) {
            cout << d << "\n";
            N /= d;
        }
        ++d;
    }
    
    return 0;
}
```

```OCaml
let () =
    Scanf.scanf "%d\n" @@ fun n ->
        let rec g curN d =
            if (curN > 1) then
                if (curN mod d = 0) then (
                    Printf.printf "%d\n" d;
                    g (curN/d) d
                ) else (
                    g curN (d + 1)
                )
            else ()
        in
        g n 2

```

```Python
N = int(input())

d = 2
while N > 1:
    if N % d == 0:
        print(d)
        N //= d
    else:
        d += 1
```

---

## 7. 그룹 단어 체커
- $S$가 주어진 단어라고 합시다.
- 각 문자가 연속해서 나타나는 경우만 **그룹 단어**입니다.
- 즉, $\forall c \in \{\mathrm{a},\ \mathrm{b},\ \mathrm{c},\ \dots, \ \mathrm{z}\}$, $i,j \in \mathbb{N}$ and $i+1 < j \le |S|$ such that $S_i = S_j$, $\forall k \in \mathbb{N}$ such that $i < k < j$, $S_k = S_i = S_j$ 를 만족해야 그룹 단어입니다.
- $|S| \le 100$으로, 단어의 길이가 상당히 작기 때문에, 나이브하게 모든 $i,j$ 쌍에 대해 $k$가 반드시 존재하는지 확인해도 괜찮습니다. (Python, $O(N|S|^3)$)
- 단어를 위 조건을 만족하는 최대 길이 부분 문자열들로 나누고, 그 부분 문자열들 중 같은 문자를 가지는 것이 있는지 확인해도 괜찮습니다. (C++, $O(N|S|)$)
- 별해는 기존 C++ 풀이에서 STL을 이용하여 같은 행위를 한 코드입니다.
```C++
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int N; cin >> N;
    int ans = 0;
    
    while (N--) {
        string s; cin >> s;
        vector<int> count(256);
        
        ++count[s[0]];
        for (size_t i = 1; i < s.size(); ++i) {
            if (s[i - 1] != s[i]) {
                ++count[s[i]];
            }
        }
        
        int8_t flag = 1;
        for(char c = 'a'; c <= 'z'; ++c) {
            flag &= static_cast<int8_t>(count[c] <= 1);
        }
        
        if (flag) {
            ++ans;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
```

```C++
// 별해

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int N; cin >> N;
    int ans = 0;
    
    while (N--) {
        string s; cin >> s;
        s.erase(unique(s.begin(), s.end()), s.end());
        size_t sz = s.size();
        
        sort(s.begin(), s.end());
        s.erase(unique(s.begin(), s.end()), s.end());
        
        if (sz == s.size()) {
            ++ans;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}

```

```Python
def sol(S):
    n = len(S)
    for i in range(n):
        for j in range(i+1,n):
            if S[i] != S[j]:
                continue
            
            for k in range(i+1,j):
                if S[k] != S[i] or S[k] != S[j]:
                    return 0
    
    return 1


ans = 0
for _ in range(int(input())):
    ans += sol(input())

print(ans)
```
