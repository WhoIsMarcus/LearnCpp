#include <iostream>
#include "Tensor.h"

int main() {

    Tensor a({{1, 2, 3}, {4, 5, 6}});
    Tensor b({{8, 3, 12}, {5, 6, 9}});
    Tensor c({{1, 2, 3}, {4, 5, 6}});
    Tensor d({{1, 1, 1}, {2, 2, 2}});

    std::cout << "A:\n" << a;
    std::cout << "B:\n" << b;

    std::cout << "\nA + B:\n" << (a + b);
    std::cout << "\nA - B:\n" << (a - b);
    std::cout << "\nC * D:\n" << (c * d);
    std::cout << "\nB / D:\n" << (b / d);

    std::cout << "\nA * 3:\n" << (a * 3.0f);
    std::cout << "\nA / 2:\n" << (a / 2.0f);

    std::cout << "\nA.matmul(B^T):\n" << a.matmul(b.transpose());

    std::cout << "\nTranspose A:\n" << a.transpose();

    std::cout << "\nA(1,2): " << a(1, 2) << "\n";

    Tensor mod = a;
    mod(0, 0) = 100;

    std::cout << "\nModified:\n" << mod;

    std::cout << "\nSum: " << a.sum();
    std::cout << "\nMean: " << a.mean();

    std::cout << "\nRow 0 sum: " << a.row_sum(0);
    std::cout << "\nCol 1 mean: " << a.col_mean(1);

    a += b;
    std::cout << "\nAfter +=\n" << a;

    a -= b;
    std::cout << "\nAfter -=\n" << a;

    std::cout << "\nReLU A:\n" << a.relu();
    std::cout << "\nSigmoid A:\n" << a.sigmoid();
    std::cout << "\nTanh A:\n" << a.tanh();

    return 0;
}