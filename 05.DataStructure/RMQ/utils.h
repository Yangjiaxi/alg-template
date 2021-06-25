#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

vector<int> array_init(size_t N, int min = 0, int max = 100) {
    random_device rd;  // only used once to initialise (seed) engine
    mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

    vector<int> A;
    for (int i = 0; i < N; ++i) A.push_back(uni(rng));

    return move(A);
}

size_t count_chars(int num) {
    size_t cnt = 0;
    if (num < 0) {
        num = -num;
        cnt = 1;
    }

    while (num > 0) {
        num /= 10;
        cnt += 1;
    }
    return cnt;
}

void output_array(vector<int> &A, bool with_idx = false) {
    if (with_idx) {
        int max_num = *max_element(A.cbegin(), A.cend());
        int min_num = *min_element(A.cbegin(), A.cend());
        size_t max_len = max(count_chars(max_num), count_chars(min_num));
        for (int i = 0; i < A.size(); ++i) cout << right << setw(max_len) << i << " ";
        cout << endl;
        for (int a : A) cout << right << setw(max_len) << a << " ";
        cout << endl;
    } else {
        for (int a : A) cout << a << " ";
        cout << endl;
    }
}