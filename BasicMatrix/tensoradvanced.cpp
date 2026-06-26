#include <iostream>
#include <vector>

using namespace std;

struct Point {
    vector<float> coords;

    Point(const vector<float>& c) : coords(c) {}
};

struct Tensor {
    vector<float> data;
    size_t rows;
    size_t cols;

    //From 2D vector
    Tensor(const vector<vector<float>>& matrix_2d) {
        rows = matrix_2d.size();
        cols = rows > 0 ? matrix_2d[0].size() : 0;

        for (const auto& row : matrix_2d) {
            for (float value : row) {
                data.push_back(value);
            }
        }
    }

    //Blank tensor
    Tensor(size_t r, size_t c) {
        rows = r;
        cols = c;
        data.resize(r * c, 0.0f);
    }

    float get(size_t r, size_t c) const {
        return data[r * cols + c];
    }

    void set(size_t r, size_t c, float val) {
        data[r * cols + c] = val;
    }

    void print() const {
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < cols; c++) {
                cout << get(r, c) << " ";
            }
            cout << endl;
        }
    }

    vector<float> getRow(size_t r) const {
        vector<float> row;
        for (size_t c = 0; c < cols; c++) {
            row.push_back(get(r, c));
        }
        return row;
    }

    vector<float> getCol(size_t c) const {
        vector<float> col;
        for (size_t r = 0; r < rows; r++) {
            col.push_back(get(r, c));
        }
        return col;
    }
};

float dot(const Point& a, const Point& b) {
    float sum = 0.0f;
    size_t n = min(a.coords.size(), b.coords.size());

    for (size_t i = 0; i < n; i++) {
        sum += a.coords[i] * b.coords[i];
    }

    return sum;
}

Tensor multiply(const Tensor& a, const Tensor& b) {

    Tensor result(a.rows, b.cols);

    for (size_t i = 0; i < a.rows; i++) {

        vector<float> rowA = a.getRow(i);

        for (size_t j = 0; j < b.cols; j++) {

            vector<float> colB = b.getCol(j);

            float sum = 0.0f;
            size_t n = min(rowA.size(), colB.size());

            for (size_t k = 0; k < n; k++) {
                sum += rowA[k] * colB[k];
            }

            result.set(i, j, sum);
        }
    }

    return result;
}

int main() {

    Point a{{1, 2, 3}};
    Point b{{3, 4, 5}};

    Tensor matrix_a({{2, 8, 3}, {5, 4, 1}});
    Tensor matrix_b({{4, 1}, {6, 3}, {2, 4}});

    Tensor finalmult = multiply(matrix_a, matrix_b);

    cout << "Dot: " << dot(a, b) << "\n";
    cout << "Matrix A * B:\n";
    finalmult.print();
}