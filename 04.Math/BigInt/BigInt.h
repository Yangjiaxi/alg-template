#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>

using namespace std;

constexpr int BASE = 10000; // 0->9999
constexpr int MAXN = 1001;

class BigInt {
  public:
    BigInt();
    BigInt(long long n);
    BigInt(const string &s);
    BigInt(const BigInt &src);

    BigInt &operator=(const BigInt &rhs);

    // arithmetic
    BigInt operator-() const;
    BigInt operator+(const BigInt &rhs) const;
    BigInt operator-(const BigInt &rhs) const;
    BigInt operator*(const BigInt &rhs) const;

    BigInt operator/(long long rhs) const;
    BigInt operator^(unsigned rhs) const;
    long long operator%(long long rhs) const;

    // relation
    bool operator<(const BigInt &rhs) const;

    friend ostream &operator<<(std::ostream &os, const BigInt &a);

  private:
    bool neg; // neg / pos
    unsigned data[MAXN];
    int len;

  private:
    BigInt &raw_neg();
    BigInt raw_plus(const BigInt &rhs) const;
    BigInt raw_minus(const BigInt &rhs) const;
    bool raw_less(const BigInt &rhs) const;
};

BigInt::BigInt() : neg(false), len(1), data() {}

BigInt::BigInt(long long n) : neg(false), len(0), data() {
    if (n < 0) {
        neg = true;
        n   = -n;
    }
    while (n > BASE - 1) {
        data[len++] = n % BASE;
        n /= BASE;
    }
    data[len++] = n;
}

BigInt::BigInt(const string &s) : neg(false), len(0), data() {
    int f     = 0;
    int n     = s.size();
    int d_len = to_string(BASE - 1).size();

    if (s[0] == '-') neg = f = 1;

    int t, k;
    for (int i = n - 1; i >= f; i -= d_len) {
        t = 0;
        k = max(i - d_len + 1, f);
        for (int j = k; j <= i; ++j) t = t * 10 + s[j] - '0';
        data[len++] = t;
    }
}

BigInt::BigInt(const BigInt &src) : len(src.len), neg(src.neg), data() {
    copy(begin(src.data), begin(src.data) + src.len, begin(data));
}

ostream &operator<<(std::ostream &os, const BigInt &a) {
    if (a.neg) os << "[-]";
    cout << a.data[a.len - 1];
    for (int i = a.len - 2; i >= 0; --i) {
        printf(",%04u", a.data[i]);
    }
    return os;
}

BigInt &BigInt::operator=(const BigInt &rhs) {
    if (this != &rhs) {
        len = rhs.len;
        neg = rhs.neg;
        copy(begin(rhs.data), begin(rhs.data) + rhs.len, begin(data));
    }
    return *this;
}

BigInt BigInt::raw_plus(const BigInt &rhs) const {
    /*
     * a + b -> c
     *
     * 1. c <- a
     * 2. c += b
     */
    BigInt tmp(*this);
    tmp.neg = false;

    int longer = max(rhs.len, len);
    tmp.len    = longer;
    for (int i = 0; i < longer; ++i) {
        tmp.data[i] += rhs.data[i];
        if (tmp.data[i] >= BASE) {
            tmp.data[i + 1] += 1;
            tmp.data[i] -= BASE;
        }
    }
    if (tmp.data[longer]) tmp.len += 1;
    return tmp;
}

BigInt BigInt::raw_minus(const BigInt &rhs) const {
    /*
     * a - b
     *  a >= b -> a - b
     *  a  < b -> -(b - a)
     */
    // small - big
    if (*this < rhs) return rhs.raw_minus(*this).raw_neg();

    // big - small
    BigInt tmp(*this); // big
    tmp.neg = false;
    for (int i = 0; i < len; ++i) {
        if (tmp.data[i] < rhs.data[i]) {
            int j = i + 1;
            while (!tmp.data[j]) ++j;
            --tmp.data[j--];
            while (j > i) tmp.data[j--] += BASE - 1;
            tmp.data[i] += BASE - rhs.data[i];
        } else {
            tmp.data[i] -= rhs.data[i];
        }
    }
    while (!tmp.data[tmp.len - 1] && tmp.len > 1) --tmp.len;
    return tmp;
}

BigInt BigInt::operator+(const BigInt &rhs) const {
    // a + b
    if (!neg && !rhs.neg) return raw_plus(rhs);
    // -a + b = b - a
    if (neg && !rhs.neg) return rhs.raw_minus(*this);
    // a + -b = a - b
    if (!neg && rhs.neg) return raw_minus(rhs);
    // -a + -b = -(a + b)
    return raw_plus(rhs).raw_neg();
}

BigInt BigInt::operator-() const {
    BigInt t(*this);
    t.neg = !neg;
    return t;
}

BigInt BigInt::operator-(const BigInt &rhs) const {
    // a - b
    if (!neg && !rhs.neg) return raw_minus(rhs);
    // -a - b = -(a+b)
    if (neg && !rhs.neg) return raw_plus(rhs).raw_neg();
    // a - -b = a + b
    if (!neg && rhs.neg) return raw_plus(rhs);
    // -a - -b = -a + b = b - a
    return rhs.raw_minus(*this);
}

BigInt &BigInt::raw_neg() {
    neg = !neg;
    return *this;
}

bool BigInt::operator<(const BigInt &rhs) const {
    // -a < b TRUE
    if (neg && !rhs.neg) return true;
    // a < -b FALSE
    if (!neg && rhs.neg) return false;
    // -a < -b -> !(a < b)
    if (neg && rhs.neg) return !raw_less(rhs);
    // a < b
    return raw_less(rhs);
}

bool BigInt::raw_less(const BigInt &rhs) const {
    // a < b
    if (len < rhs.len) return true;
    if (len == rhs.len) {
        int idx = len - 1;
        while (idx >= 0 && data[idx] == rhs.data[idx]) --idx;
        return idx >= 0 && data[idx] < rhs.data[idx];
    }
    return false;
}
BigInt BigInt::operator*(const BigInt &rhs) const {
    BigInt res;
    for (int i = 0; i < len; ++i) {
        int forward = 0;
        for (int j = 0; j < rhs.len; ++j) {
            int t           = data[i] * rhs.data[j] + res.data[i + j] + forward;
            res.data[i + j] = t % BASE;
            forward         = t / BASE;
        }
        res.data[i + rhs.len] = forward;
    }
    res.len = len + rhs.len;

    while (!res.data[res.len - 1] && res.len > 1) --res.len;
    res.neg = neg != rhs.neg;
    return res;
}

BigInt BigInt::operator/(long long rhs) const {
    BigInt res;
    bool rhs_neg = false;
    if (rhs < 0) {
        rhs     = -rhs;
        rhs_neg = true;
    }
    long long backward = 0;
    for (int i = len - 1; i >= 0; --i) {
        res.data[i] = (data[i] + backward * BASE) / rhs;
        backward    = data[i] + backward * BASE - res.data[i] * rhs;
    }
    res.len = len;

    while (!res.data[res.len - 1] && res.len > 1) --res.len;
    res.neg = neg != rhs_neg;
    return res;
}
long long BigInt::operator%(long long rhs) const {
    long long mod = 0;
    for (int i = len - 1; i >= 0; --i) {
        mod = ((mod * BASE) % rhs + data[i]) % rhs;
    }
    return mod;
}

BigInt BigInt::operator^(unsigned rhs) const {
    BigInt base(*this);
    BigInt res(1);
    while (rhs > 0) {
        if (rhs & 1) res = res * base;
        base = base * base;
        rhs >>= 1;
    }
    return res;
}

#endif // BIGINT_H