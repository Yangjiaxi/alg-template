#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

int euler_phi(int n) {
    int ans = n;
    int m = sqrt(n);

    for (int i = 2; i <= m; ++i) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

int main() {
    for (int i = 1; i <= 99; ++i) {
        printf("φ(%2d)=%02d", i, euler_phi(i));
        cout << "\t\n"[i % 5 == 0];
    }
    return 0;
}

/*
φ( 1)=01	φ( 2)=01	φ( 3)=02	φ( 4)=02	φ( 5)=04
φ( 6)=02	φ( 7)=06	φ( 8)=04	φ( 9)=06	φ(10)=04
φ(11)=10	φ(12)=04	φ(13)=12	φ(14)=06	φ(15)=08
φ(16)=08	φ(17)=16	φ(18)=06	φ(19)=18	φ(20)=08
φ(21)=12	φ(22)=10	φ(23)=22	φ(24)=08	φ(25)=20
φ(26)=12	φ(27)=18	φ(28)=12	φ(29)=28	φ(30)=08
φ(31)=30	φ(32)=16	φ(33)=20	φ(34)=16	φ(35)=24
φ(36)=12	φ(37)=36	φ(38)=18	φ(39)=24	φ(40)=16
φ(41)=40	φ(42)=12	φ(43)=42	φ(44)=20	φ(45)=24
φ(46)=22	φ(47)=46	φ(48)=16	φ(49)=42	φ(50)=20
φ(51)=32	φ(52)=24	φ(53)=52	φ(54)=18	φ(55)=40
φ(56)=24	φ(57)=36	φ(58)=28	φ(59)=58	φ(60)=16
φ(61)=60	φ(62)=30	φ(63)=36	φ(64)=32	φ(65)=48
φ(66)=20	φ(67)=66	φ(68)=32	φ(69)=44	φ(70)=24
φ(71)=70	φ(72)=24	φ(73)=72	φ(74)=36	φ(75)=40
φ(76)=36	φ(77)=60	φ(78)=24	φ(79)=78	φ(80)=32
φ(81)=54	φ(82)=40	φ(83)=82	φ(84)=24	φ(85)=64
φ(86)=42	φ(87)=56	φ(88)=40	φ(89)=88	φ(90)=24
φ(91)=72	φ(92)=44	φ(93)=60	φ(94)=46	φ(95)=72
φ(96)=32	φ(97)=96	φ(98)=42	φ(99)=60
*/
