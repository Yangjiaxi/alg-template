#include "./BigInt.h"
#include <iostream>

using namespace std;

int main() {
    BigInt a("1231123");
    BigInt b(10);
    cout << "        a = " << a << endl;
    cout << "        b = " << b << endl;
    cout << "    a + b = " << a + b << endl;
    cout << "    a - b = " << a - b << endl;
    cout << "    a * b = " << a * b << endl;
    cout << "a / (-20) = " << a / (-20) << endl;
    cout << " a % 1024 = " << a % 1024 << endl;
    cout << "  2 ^ 177 = " << (BigInt(2) ^ 177)
         << endl; // 191561942608236107294793378393788647952342390272950272
    return 0;
}

//         a = 123,1123
//         b = 10
//     a + b = 123,1133
//     a - b = 123,1113
//     a * b = 1231,1230
// a / (-20) = [-]6,1556
//  a % 1024 = 275
//   2 ^ 177 = 19,1561,9426,0823,6107,2947,9337,8393,7886,4795,2342,3902,7295,0272
