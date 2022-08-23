#include <iostream>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int bgcd(int a, int b) {
    while (b) b ^= a ^= b ^= a %= b;
    return a;
}

int lcm(int a, int b) { return a * b / gcd(a, b); }

int main() {
    cout << gcd(24, 16) << endl;
    cout << bgcd(24, 16) << endl;
    cout << lcm(24, 16) << endl;
    return 0;
}