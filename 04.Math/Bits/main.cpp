#include <iostream>

using namespace std;

int main() {
    int a = 0b01010101100;
    // count number of `1`
    cout << "popcount() = " << __builtin_popcount(a) << endl;
    // get parity of `1`
    cout << "parity(1) = " << __builtin_parity(a) << endl;
    // pos of last `1` (start from 1)
    cout << "ffs() = " << __builtin_ffs(a) << endl;
    // count of trailing `0`s
    cout << "ctz() = " << __builtin_ctz(a) << endl;
    // count of leading `0`s
    cout << "clz() = " << __builtin_clz(a) << endl;

    bitset<10> bs;
    cout << bs << " : " << bs.count() << endl;
    bs.set(5), bs.set(2);
    cout << bs << " : " << bs.count() << endl;
    bs.flip();
    cout << bs << " : " << bs.count() << endl;
    return 0;
}