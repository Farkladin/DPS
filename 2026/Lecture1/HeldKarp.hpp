//
//  HeldKarp.hpp
//  FarkCompProgSeminar
//
//  Created by Farkladin on 10/6/26.
//

#ifndef HeldKarp_h
#define HeldKarp_h

#include <cstdlib>
#include <cstdint>
#include <array>
#include <algorithm>
#include <cstring>

template<size_t N>
class HeldKarp{
public:
    using ll = uint64_t;
    constexpr static ll MAX_SET_MASK = (1ULL << N) - 1;
    std::array<std::array<ll, N>, (1ULL << N)> DP{}; // Same as DP[1ULL << N][N];
    std::array<std::array<ll, N>, N> W{}; // W[N][N];
    HeldKarp(std::array<std::array<ll, N>, N> weights) {
        memset(DP.data(), 0xFF, sizeof(DP));
        W = weights;
    }
    
private:
    ll solveEngine(ll S, ll u) { /* |V| <= 20 required */
        if (DP[S][u] != UINT64_MAX) {
            return DP[S][u];
        }
        
        if (S == MAX_SET_MASK) {
            return W[u][0];
        }
        
        ll tmp = UINT64_MAX;
        for (ll v = 0ULL; v < N; ++v) {
            if ((1ULL << v) & S) continue;
            tmp = std::min(tmp, solveEngine(S|(1ULL << v), v) + W[u][v]);
        }
        
        DP[S][u] = tmp;
        return tmp;
    }
    
public:
    ll solve() {
        return solveEngine(1ULL, 0ULL);
    }
};

#endif /* HeldKarp_h */
