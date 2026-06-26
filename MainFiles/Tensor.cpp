#include "Tensor.h"
#include <iostream>

//Constructor from 2D vector
Tensor::Tensor(const std::vector<std::vector<float>>& matrix_2d) {
    rows = matrix_2d.size();
    cols = rows ? matrix_2d[0].size() : 0;

    data.reserve(rows * cols);

    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            data.push_back(matrix_2d[r][c]);
        }
    }
}

//Empty tensor
Tensor::Tensor(size_t r, size_t c)
    : data(r * c, 0.0f), rows(r), cols(c) {}

//Access
float Tensor::get(size_t r, size_t c) const {
    if (r >= rows || c >= cols) throw std::runtime_error("out of bounds");
    return data[r * cols + c];
}

void Tensor::set(size_t r, size_t c, float val) {
    if (r >= rows || c >= cols) throw std::runtime_error("out of bounds");
    data[r * cols + c] = val;
}

float& Tensor::operator()(size_t r, size_t c) {
    if (r >= rows || c >= cols) throw std::runtime_error("out of bounds");
    return data[r * cols + c];
}

const float& Tensor::operator()(size_t r, size_t c) const {
    if (r >= rows || c >= cols) throw std::runtime_error("out of bounds");
    return data[r * cols + c];
}

//Print
void Tensor::print() const {
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            std::cout << get(r, c) << " ";
        }
        std::cout << "\n";
    }
}

//Elementwise ops
Tensor Tensor::operator+(const Tensor& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::runtime_error("shape mismatch");

    Tensor result(rows, cols);
    for (size_t i = 0; i < data.size(); i++)
        result.data[i] = data[i] + other.data[i];

    return result;
}

Tensor Tensor::operator-(const Tensor& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::runtime_error("shape mismatch");

    Tensor result(rows, cols);
    for (size_t i = 0; i < data.size(); i++)
        result.data[i] = data[i] - other.data[i];

    return result;
}

Tensor Tensor::operator*(const Tensor& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::runtime_error("shape mismatch");

    Tensor result(rows, cols);
    for (size_t i = 0; i < data.size(); i++)
        result.data[i] = data[i] * other.data[i];

    return result;
}

Tensor Tensor::operator/(const Tensor& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::runtime_error("shape mismatch");

    Tensor result(rows, cols);
    for (size_t i = 0; i < data.size(); i++) {
        if (other.data[i] == 0)
            throw std::runtime_error("division by zero");
        result.data[i] = data[i] / other.data[i];
    }

    return result;
}

//Scalar ops
Tensor Tensor::operator*(float scalar) const {
    Tensor result(rows, cols);
    for (size_t i = 0; i < data.size(); i++)
        result.data[i] = data[i] * scalar;

    return result;
}

Tensor Tensor::operator/(float scalar) const {
    if (scalar == 0) throw std::runtime_error("division by zero");

    Tensor result(rows, cols);
    for (size_t i = 0; i < data.size(); i++)
        result.data[i] = data[i] / scalar;

    return result;
}

//Compound ops
Tensor& Tensor::operator+=(const Tensor& other) {
    if (rows != other.rows || cols != other.cols)
        throw std::runtime_error("shape mismatch");

    for (size_t i = 0; i < data.size(); i++)
        data[i] += other.data[i];

    return *this;
}

Tensor& Tensor::operator-=(const Tensor& other) {
    if (rows != other.rows || cols != other.cols)
        throw std::runtime_error("shape mismatch");

    for (size_t i = 0; i < data.size(); i++)
        data[i] -= other.data[i];

    return *this;
}

//Matrix multiply
Tensor Tensor::matmul(const Tensor& other) const {
    if (cols != other.rows)
        throw std::runtime_error("shape mismatch");

    Tensor result(rows, other.cols);

    for (size_t i = 0; i < rows; i++) {
        for (size_t k = 0; k < cols; k++) {
            float a = data[i * cols + k];

            for (size_t j = 0; j < other.cols; j++) {
                result.data[i * other.cols + j] += a * other.data[k * other.cols + j];
            }
        }
    }

    return result;
}

//Stats
float Tensor::sum() const {
    float total = 0.0f;
    for (float v : data) total += v;
    return total;
}

float Tensor::mean() const {
    if (data.empty()) return 0.0f;
    return sum() / data.size();
}

float Tensor::row_sum(size_t r) const {
    if (r >= rows) throw std::runtime_error("out of bounds");

    float s = 0.0f;
    size_t base = r * cols;

    for (size_t c = 0; c < cols; c++)
        s += data[base + c];

    return s;
}

float Tensor::col_sum(size_t c) const {
    if (c >= cols) throw std::runtime_error("out of bounds");

    float s = 0.0f;

    for (size_t r = 0; r < rows; r++)
        s += data[r * cols + c];

    return s;
}

float Tensor::row_mean(size_t r) const {
    return row_sum(r) / cols;
}

float Tensor::col_mean(size_t c) const {
    return col_sum(c) / rows;
}

//Transpose
Tensor Tensor::transpose() const {
    Tensor result(cols, rows);

    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            result.data[c * rows + r] = data[r * cols + c];
        }
    }

    return result;
}

//ostream
std::ostream& operator<<(std::ostream& os, const Tensor& t) {
    for (size_t r = 0; r < t.rows; r++) {
        for (size_t c = 0; c < t.cols; c++) {
            os << t(r, c) << " ";
        }
        os << "\n";
    }
    return os;
}