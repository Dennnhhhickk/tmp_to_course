#include <array>
#include <iostream>

constexpr bool is_odd(int a) {
    return a % 2;
}

template<int N>
constexpr std::array<std::array<int, N - 1>, N - 1> SubMatrix(const std::array<std::array<int, N>, N>& matrix, int l, int r) {
    std::array<std::array<int, N - 1>, N - 1> sub{};
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - 1; ++j) {
            (&std::get<0>(((&std::get<0>(sub))[i])))[j] = matrix[i + (i >= l ? 1 : 0)][j + (j >= r ? 1 : 0)];
        }
    }
    return sub;
}

template <int N>
constexpr int Det(const std::array<std::array<int, N>, N>& matrix) {
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        ans += (is_odd(i) ? -1 : 1) * matrix[0][i] * Det<int(N - 1)>(SubMatrix<N>(matrix, 0, i));
    }
    return ans;
}

template<>
constexpr int Det<2>(const std::array<std::array<int, 2>, 2>& matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

template<>
constexpr int Det<1>(const std::array<std::array<int, 1>, 1>& matrix) {
    return matrix[0][0];
}

int main() {
    constexpr std::array<std::array<int, 3>, 3> matrix = {{
    {0, 1, 2},
    {1, 2, 3},
    {2, 3, 7}
    }};
    constexpr int result = Det<3>(matrix);
    static_assert(result == -3);
    std::cout << result << std::endl;
    constexpr std::array<std::array<int, 4>, 4> matrix2 = {{
    {1, 3, 5, 6},
    {12, 6, 4, 2},
    {0, 7, 9, 7},
    {2, 7, 2, 6}
    }};
    constexpr int result1 = Det<4>(matrix2);
    static_assert(result1 == 1746);
    std::cout << result1 << std::endl;
    return 0;
}



//FIRST ATTEMPT
//Incorrect due to partial specialization of functions

// template<int N, int M, int K>
// // constexpr typename std::enable_if<M == 1 && K == 1, std::array<std::array<int, 1>, 1>>::type
// constexpr std::array<std::array<int, 1>, 1>
// SubArray(const std::array<std::array<int, N>, N>& matrix, int r, int l, int rc, int lc) {
//     return {{{matrix.at(lc).at(rc)}}};
// }

// template<int N, int M>
// constexpr std::array<std::array<int, M>, 1> SubArray2(const std::array<std::array<int, N>, N>& matrix, int r, int l, int rc, int lc) {
//     if (r == rc) {
//         return SubArray<N, M, 1>(matrix, r, l, rc + 1, lc);
//     }
//     return {{matrix.at(lc).at(rc), SubArray<N, M - 1, 1>(matrix, r, l, rc + 1, lc)}};
// }

// template <int N, int K>
// constexpr std::array<std::array<int, N - 1>, K> SubArray1(const std::array<std::array<int, N>, N>& matrix, int r, int l, int rc, int lc) {
//     if (l == lc) {
//         return SubArray<N, K>(matrix, r, l, rc, lc + 1);
//     }
//     return {SubArray2<N, N - 1>(matrix, r, l, rc, lc), SubArray1<N, K - 1>(matrix, r, l, rc, lc + 1)};
// }




//SECOND ATTEMPT
//Has a lot of bugs and looks like a monster

// template<int N>
// constexpr int get_val_from_matrix(const std::array<std::array<int, N>, N>& matrix, int i, int j) {
//     return matrix[i][j];
// }


// template <typename T, std::size_t N1, std::size_t N2>
// constexpr std::array<T, N1 + N2> concat(std::array<T, N1> lhs, std::array<T, N2> rhs)
// {
//     std::array<T, N1 + N2> result{};
//     std::size_t index = 0;

//     for (auto& el : lhs) {
//         result[index] = std::move(el);
//         ++index;
//     }
//     for (auto& el : rhs) {
//         result[index] = std::move(el);
//         ++index;
//     }

//     return result;
// }

// template <int N, int M, int K>
// class SubArray{
// public:
//     std::array<std::array<int, M>, K> arr_;

//     SubArray() = delete;
//     constexpr SubArray(const std::array<std::array<int, N>, N>&matrix, int r, int l, int rc, int lc) {
//     }
// };

// template <int N, int M>
// constexpr std::array<std::array<int, M>, 1> func(const std::array<std::array<int, N>, N>&matrix, int r, int l, int rc, int lc) {
//     if (rc == r) {
//         return {SubArray<N, M, 1>(matrix, r, l, rc + 1, lc).arr_};
//     }
//     SubArray<N, M - 1, 1> tmp = SubArray<N, M - 1, 1>(matrix, r, l, rc + 1, lc);
//     return {concat(std::array<int, 1>{get_val_from_matrix<N>(matrix, lc, rc)}, (&std::get<0>(tmp.arr_))[0])};
// }

// template <int N, int M>
// class SubArray<N, M, 1>{
// public:
//     std::array<std::array<int, M>, 1> arr_;

//     SubArray() = delete;
//     constexpr SubArray(const std::array<std::array<int, N>, N>&matrix, int r, int l, int rc, int lc) : arr_{func<N, M>(matrix, r, l, rc, lc)} {
//     }
// };

// template <int N>
// class SubArray<N, 1, 1>{
// public:
//     std::array<std::array<int, 1>, 1> arr_;

//     SubArray() = delete;
//     constexpr SubArray(const std::array<std::array<int, N>, N>&matrix, int r, int l, int rc, int lc) : arr_{{get_val_from_matrix<N>(matrix, lc, rc)}} {
//     }
// };