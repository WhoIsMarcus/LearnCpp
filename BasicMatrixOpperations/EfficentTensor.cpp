#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

struct Tensor {
    vector<float> data;
    size_t rows;
    size_t cols;

    // Construct from 2D vector
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

    // Empty tensor
    Tensor(size_t r, size_t c)
        : rows(r), cols(c), data(r * c, 0.0f) {}

    inline float get(size_t r, size_t c) const {
        return data[r * cols + c];
    }

    inline void set(size_t r, size_t c, float val) {
        data[r * cols + c] = val;
    }

    void print() const {
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < cols; c++) {
                cout << get(r, c) << " ";
            }
            cout << "\n";
        }
    }

    float sum() const {
        float total = 0.0f;
        for (float v : data) total += v;
        return total;
    }

    float mean() const {
        return data.empty() ? 0.0f : sum() / data.size();
    }

    float row_sum(size_t r) const {
        float s = 0.0f;
        size_t base = r * cols;
        for (size_t c = 0; c < cols; c++) {
            s += data[base + c];
        }
        return s;
    }

    float col_sum(size_t c) const {
        float s = 0.0f;
        for (size_t r = 0; r < rows; r++) {
            s += data[r * cols + c];
        }
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

// -------------------- CORE OPERATIONS --------------------

Tensor add(const Tensor& a, const Tensor& b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw runtime_error("Shape mismatch in add");
    }

    Tensor result(a.rows, a.cols);

    for (size_t i = 0; i < a.data.size(); i++) {
        result.data[i] = a.data[i] + b.data[i];
    }

    return result;
}

Tensor subtract(const Tensor& a, const Tensor& b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw runtime_error("Shape mismatch in subtract");
    }

    Tensor result(a.rows, a.cols);

    for (size_t i = 0; i < a.data.size(); i++) {
        result.data[i] = a.data[i] - b.data[i];
    }

    return result;
}

// -------------------- MAIN --------------------

int main() {

    Tensor matrix_a({{1, 2, 3}, {4, 5, 6}});
    Tensor matrix_b({{8, 3, 12}, {5, 6, 9}});

    Tensor matrix_c({{1, 2, 3}, {4, 5, 6}});
    Tensor matrix_d({{1, 1, 1}, {2, 2, 2}});

    cout << "Matrix A:\n";
    matrix_a.print();

    cout << "\nMatrix B:\n";
    matrix_b.print();

    cout << "\nAddition (A + B):\n";
    add(matrix_a, matrix_b).print();

    cout << "\nSubtraction (C - D):\n";
    subtract(matrix_c, matrix_d).print();

    cout << "\nTranspose of A:\n";
    matrix_a.transpose().print();

    cout << "\nSum of A: " << matrix_a.sum() << "\n";
    cout << "Mean of A: " << matrix_a.mean() << "\n";

    cout << "\nRow 0 sum: " << matrix_a.row_sum(0) << "\n";
    cout << "Col 1 mean: " << matrix_a.col_mean(1) << "\n";

    return 0;
}