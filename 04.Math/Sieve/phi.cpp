#include <iostream>
#include <vector>

using namespace std;

vector<int> phi_table(int n) {
    vector<int> phi(n + 1, 0);
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!phi[i]) {
            for (int j = i; j <= n; j += i) {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    return move(phi);
}

int main() {
    auto phi = phi_table(99);
    for (int i = 1; i <= 99; ++i) {
        printf("φ(%2d)=%02d", i, phi[i]);
        cout << "\t\n"[i % 5 == 0];
    }
    return 0;
}