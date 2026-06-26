#include <iostream>
#include <vector>
#include <stdexcept>
#include <ostream>

using namespace std;

struct Tensor {
    vector<float> data;
    size_t rows;
    size_t cols;

    Tensor(const vector<vector<float>>& matrix_2d) {
        rows = matrix_2d.size();
        cols = rows ? matrix_2d[0].size() : 0;

        data.reserve(rows * cols);

        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < cols; c++) {
                data.push_back(matrix_2d[r][c]);
            }
        }
    }

    Tensor(size_t r, size_t c)
        : data(r * c, 0.0f), rows(r), cols(c) {}

    float get(size_t r, size_t c) const {
        if (r >= rows || c >= cols) throw runtime_error("out of bounds");
        return data[r * cols + c];
    }

    void set(size_t r, size_t c, float val) {
        if (r >= rows || c >= cols) throw runtime_error("out of bounds");
        data[r * cols + c] = val;
    }

    float& operator()(size_t r, size_t c) {
        if (r >= rows || c >= cols) throw runtime_error("out of bounds");
        return data[r * cols + c];
    }

    const float& operator()(size_t r, size_t c) const {
        if (r >= rows || c >= cols) throw runtime_error("out of bounds");
        return data[r * cols + c];
    }

    void print() const {
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < cols; c++) {
                cout << get(r, c) << " ";
            }
            cout << "\n";
        }
    }

    Tensor operator+(const Tensor& other) const {
        if (rows != other.rows || cols != other.cols) throw runtime_error("shape mismatch");
        Tensor result(rows, cols);
        for (size_t i = 0; i < data.size(); i++) result.data[i] = data[i] + other.data[i];
        return result;
    }

    Tensor operator-(const Tensor& other) const {
        if (rows != other.rows || cols != other.cols) throw runtime_error("shape mismatch");
        Tensor result(rows, cols);
        for (size_t i = 0; i < data.size(); i++) result.data[i] = data[i] - other.data[i];
        return result;
    }

    Tensor operator*(const Tensor& other) const {
        if (rows != other.rows || cols != other.cols) throw runtime_error("shape mismatch");
        Tensor result(rows, cols);
        for (size_t i = 0; i < data.size(); i++) result.data[i] = data[i] * other.data[i];
        return result;
    }

    Tensor operator/(const Tensor& other) const {
        if (rows != other.rows || cols != other.cols) throw runtime_error("shape mismatch");
        Tensor result(rows, cols);
        for (size_t i = 0; i < data.size(); i++) {
            if (other.data[i] == 0) throw runtime_error("division by zero");
            result.data[i] = data[i] / other.data[i];
        }
        return result;
    }

    Tensor operator*(float scalar) const {
        Tensor result(rows, cols);
        for (size_t i = 0; i < data.size(); i++) result.data[i] = data[i] * scalar;
        return result;
    }

    Tensor operator/(float scalar) const {
        if (scalar == 0) throw runtime_error("division by zero");
        Tensor result(rows, cols);
        for (size_t i = 0; i < data.size(); i++) result.data[i] = data[i] / scalar;
        return result;
    }

    Tensor& operator+=(const Tensor& other) {
        if (rows != other.rows || cols != other.cols) throw runtime_error("shape mismatch");
        for (size_t i = 0; i < data.size(); i++) data[i] += other.data[i];
        return *this;
    }

    Tensor& operator-=(const Tensor& other) {
        if (rows != other.rows || cols != other.cols) throw runtime_error("shape mismatch");
        for (size_t i = 0; i < data.size(); i++) data[i] -= other.data[i];
        return *this;
    }


    //regular matrix multiply (non-elementwise)
    Tensor matmul(const Tensor& other) const {
        if (cols != other.rows) throw runtime_error("shape mismatch");
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

    float sum() const {
        float total = 0.0f;
        for (float v : data) total += v;
        return total;
    }

    float mean() const {
        if (data.empty()) return 0.0f;
        return sum() / data.size();
    }

    float row_sum(size_t r) const {
        if (r >= rows) throw runtime_error("out of bounds");
        float s = 0.0f;
        size_t base = r * cols;
        for (size_t c = 0; c < cols; c++) s += data[base + c];
        return s;
    }

    float col_sum(size_t c) const {
        if (c >= cols) throw runtime_error("out of bounds");
        float s = 0.0f;
        for (size_t r = 0; r < rows; r++) s += data[r * cols + c];
        return s;
    }

    float row_mean(size_t r) const {
        return row_sum(r) / cols;
    }

    float col_mean(size_t c) const {
        return col_sum(c) / rows;
    }

    Tensor transpose() const {
        Tensor result(cols, rows);
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < cols; c++) {
                result.data[c * rows + r] = data[r * cols + c];
            }
        }
        return result;
    }
};

ostream& operator<<(ostream& os, const Tensor& t) {
    for (size_t r = 0; r < t.rows; r++) {
        for (size_t c = 0; c < t.cols; c++) {
            os << t(r, c) << " ";
        }
        os << "\n";
    }
    return os;
}

int main() {
    Tensor a({{1, 2, 3}, {4, 5, 6}});
    Tensor b({{8, 3, 12}, {5, 6, 9}});
    Tensor c({{1, 2, 3}, {4, 5, 6}});
    Tensor d({{1, 1, 1}, {2, 2, 2}});

    cout << "Matrix A:\n" << a;
    cout << "Matrix B:\n" << b;

    cout << "\nA + B:\n" << (a + b);
    cout << "\nA - B:\n" << (a - b);
    cout << "\nC * D:\n" << (c * d);
    cout << "\nB / D:\n" << (b / d);

    cout << "\nA * 3:\n" << (a * 3.0f);
    cout << "\nA / 2:\n" << (a / 2.0f);

    cout << "\nA.matmul(B):\n" << a.matmul(b.transpose());

    cout << "\nTranspose A:\n" << a.transpose();

    cout << "\nA(1,2): " << a(1, 2) << "\n";

    Tensor mod = a;
    mod(0, 0) = 100;

    cout << "\nModified:\n" << mod;

    cout << "\nSum: " << a.sum() << "\n";
    cout << "Mean: " << a.mean() << "\n";

    cout << "Row 0 sum: " << a.row_sum(0) << "\n";
    cout << "Row 1 mean: " << a.row_mean(1) << "\n";
    cout << "Col 1 sum: " << a.col_sum(1) << "\n";
    cout << "Col 2 mean: " << a.col_mean(2) << "\n";

    a += b;
    cout << "\nAfter +=:\n" << a;

    a -= b;
    cout << "\nAfter -=:\n" << a;

    return 0;
}