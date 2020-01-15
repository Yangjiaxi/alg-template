#include <iostream>

using namespace std;
using ll = long long;

ll fast_pow_trivial_rec(ll a, ll b) {
    if (b == 0) return 1;
    ll res = fast_pow_trivial_rec(a, b / 2);
    if (b & 1) return res * res * a;
    return res * res;
}

ll fast_pow_trivial_iter(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

bool is_prime(ll n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i)
        if (!(n % i)) return false;
    return true;
}

ll fast_pow_mod(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    if (is_prime(m)) b %= m - 1;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int main() {
    constexpr ll a = 2;
    constexpr ll b = 61;
    constexpr ll m = 17;
    cout << a << "^" << b << " = " << endl;
    cout << fast_pow_trivial_rec(a, b) << endl;
    cout << fast_pow_trivial_iter(a, b) << endl << endl;

    cout << a << "^" << b << " mod " << m << " = " << endl;
    cout << fast_pow_mod(a, b, m) << endl;
    return 0;
}