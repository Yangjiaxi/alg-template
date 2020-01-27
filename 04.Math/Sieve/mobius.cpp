#include <iostream>
#include <vector>

using namespace std;

vector<int> calc_mu(int n) {
    vector<int> prime;
    vector<bool> not_prime(n + 1, false);
    vector<int> mu(n + 1, 0);

    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
            prime.push_back(i);
            mu[i] = -1;
        }
        for (auto v : prime) {
            if (v * i > n) break;
            not_prime[v * i] = 1;
            if (i % v == 0) break;
            mu[v * i] = -mu[i];
        }
    }
    return move(mu);
}

int main() {
    constexpr int N = 9;

    auto mu = calc_mu(N);
    for (int i = 1; i <= N; ++i) {
        printf("μ(%d) = %d\n", i, mu[i]);
    }
    return 0;
}