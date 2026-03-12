#include "../include/syrk.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

template<typename T>
void fill_random(std::vector<T>& v) {
    std::mt19937 gen(42);
    std::uniform_real_distribution<T> dist(-1.0, 1.0);
    for (auto& x : v) {
        x = dist(gen);
    }
}

int main() {
    int n = 512;
    int k = 512;
    float alpha = 1.0f;
    float beta = 1.0f;

    std::vector<float> A(n * k);
    std::vector<float> C(n * n);

    fill_random(A);
    fill_random(C);

    auto start = std::chrono::high_resolution_clock::now();

    syrk_custom<float>(
        Uplo::Upper,
        Transpose::NoTrans,
        n,
        k,
        alpha,
        A.data(),
        k,
        beta,
        C.data(),
        n
    );

    auto end = std::chrono::high_resolution_clock::now();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Custom SYRK time: " << ms << " ms\n";
    return 0;
}
