#include <optional>
#include <random>

using namespace std;

mt19937 get_randomizer(optional<int> seed) {
    if (seed.has_value()) {
        return move(mt19937(seed.value()));
    } else {
        random_device rd;
        return move(mt19937(rd()));
    }
}

vector<int> random_arr(size_t N, optional<int> seed = nullopt, int min = 0, int max = 100) {
    auto rng = get_randomizer(seed);
    uniform_int_distribution<int> uni(min, max);

    vector<int> A;
    for (int i = 0; i < N; ++i) A.push_back(uni(rng));

    return move(A);
}
