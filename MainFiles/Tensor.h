#pragma once
#include <vector>
#include <stdexcept>
#include <ostream>

struct Tensor {
    std::vector<float> data;
    size_t rows;
    size_t cols;

    Tensor(const std::vector<std::vector<float>>& matrix_2d);
    Tensor(size_t r, size_t c);

    float get(size_t r, size_t c) const;
    void set(size_t r, size_t c, float val);

    float& operator()(size_t r, size_t c);
    const float& operator()(size_t r, size_t c) const;

    void print() const;

    Tensor operator+(const Tensor& other) const;
    Tensor operator-(const Tensor& other) const;
    Tensor operator*(const Tensor& other) const;
    Tensor operator/(const Tensor& other) const;

    Tensor operator*(float scalar) const;
    Tensor operator/(float scalar) const;

    Tensor& operator+=(const Tensor& other);
    Tensor& operator-=(const Tensor& other);

    Tensor matmul(const Tensor& other) const;

    float sum() const;
    float mean() const;

    float row_sum(size_t r) const;
    float col_sum(size_t c) const;

    float row_mean(size_t r) const;
    float col_mean(size_t c) const;

    Tensor transpose() const;
};

std::ostream& operator<<(std::ostream& os, const Tensor& t);