#include <iostream>
#include <vector>

using namespace std;

vector<bool> prime_table(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            // 从i*i开始，因为对于i*k(k<i)，是被k筛过了的
            for (int j = i * i; j <= n; j += i) is_prime[j] = 0;
        }
    }
    return move(is_prime);
}

int main() {
    auto is_p1 = prime_table(100);
    for (int i = 0, j = 0; i < is_p1.size(); ++i) {
        if (is_p1[i]) {
            cout << i << "\t\n"[(++j) % 5 == 0];
        }
    }
    return 0;
}