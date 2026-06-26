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

    Tensor transpose() const {
        Tensor result(cols, rows);

        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < cols; c++) {
                result.set(c, r, get(r, c));
            }
        }

        return result;
    }

    float row_sum(size_t r) const {
        float sum = 0.0f;

        for (size_t c = 0; c < cols; c++) {
            sum += get(r, c);
        }

        return sum;
    }

    float col_sum(size_t c) const {
        float sum = 0.0f;

        for (size_t r = 0; r < rows; r++) {
            sum += get(r, c);
        }

        return sum;
    }

    float sum() const {
        float total = 0.0f;

        for (float value : data) {
            total += value;
        }

        return total;
    }


    float mean() const {
        if (data.empty()) {
            return 0.0f;
        }

        return sum() / data.size();
    }

    float row_mean(size_t r) const {
        return row_sum(r) / cols;
    }

    float col_mean(size_t c) const {
        return col_sum(c) / rows;
    }


};



//Function with tensors



float dot(const Point& a, const Point& b) {
    float sum = 0.0f;
    size_t n = min(a.coords.size(), b.coords.size());

    for (size_t i = 0; i < n; i++) {
        sum += a.coords[i] * b.coords[i];
    }

    return sum;
}

Tensor scalar_multiply(float num, const Tensor& matrix) {

    Tensor result(matrix.rows, matrix.cols);

    for (size_t r = 0; r < matrix.rows; r++) {
        for (size_t c = 0; c < matrix.cols; c++) {
            result.set(r, c, matrix.get(r, c) * num);
        }
    }

    return result;
}

Tensor multiply(const Tensor& a, const Tensor& b) {

    if (a.cols != b.rows) {
        throw runtime_error("Tensor size mismatch");
    }



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


Tensor divide(const Tensor& a, const Tensor& b) {

    if (a.rows != b.rows || a.cols != b.cols) {
        throw runtime_error("Tensor size mismatch");
    }

    Tensor result(a.rows, a.cols);

    for (size_t i = 0; i < a.rows; i++) {
        for (size_t j = 0; j < a.cols; j++) {

            float denom = b.get(i, j);

            if (denom == 0) {
                throw runtime_error("Division by zero");
            }

            result.set(i, j, a.get(i, j) / denom);
        }
    }

    return result;
}


Tensor elementwise_multiply(const Tensor& a, const Tensor& b) {

    if (a.rows != b.rows || a.cols != b.cols) {
        throw runtime_error("Tensor size mismatch");
    }

    Tensor result(a.rows, a.cols);

    for (size_t i = 0; i < a.rows; i++) {
        for (size_t j = 0; j < a.cols; j++) {
            result.set(i, j, a.get(i, j) * b.get(i, j));
        }
    }

    return result;
}




int main() {

    Point a{{1, 2, 3}};
    Point b{{3, 4, 5}};

    Tensor matrix_a({{2, 8, 3}, {5, 4, 1}});
    Tensor matrix_b({{4, 1}, {6, 3}, {2, 4}});

    Tensor matrix_c({{1,2,3},{4,5,6}});
    Tensor matrix_d({{1,1,1},{2,2,2}});

    //Dot product
    cout << "Dot Product:\n";
    cout << dot(a, b) << "\n\n";

    //Original matrix
    cout << "Matrix A:\n";
    matrix_a.print();

    //Matrix multiplication
    cout << "\nMatrix A * B:\n";
    Tensor finalmult = multiply(matrix_a, matrix_b);
    finalmult.print();

    //Element-wise division
    cout << "\nMatrix C / D:\n";
    Tensor finaldiv = divide(matrix_c, matrix_d);
    finaldiv.print();

    //Element-wise multiplication
    cout << "\nMatrix C element-wise * D:\n";
    Tensor elem = elementwise_multiply(matrix_c, matrix_d);
    elem.print();

    //Scalar multiplication
    cout << "\nMatrix A * 3:\n";
    Tensor scalarmul = scalar_multiply(3, matrix_a);
    scalarmul.print();

    //Transpose
    cout << "\nTranspose of Matrix A:\n";
    Tensor trans = matrix_a.transpose();
    trans.print();

    //Get one element
    cout << "\nElement (1,2): ";
    cout << matrix_a.get(1, 2) << endl;

    //Get row
    cout << "\nRow 0:\n";
    for (float x : matrix_a.getRow(0))
        cout << x << " ";
    cout << endl;

    //Get column
    cout << "\nColumn 1:\n";
    for (float x : matrix_a.getCol(1))
        cout << x << " ";
    cout << endl;

    //Modify one element
    cout << "\nset() example:\n";
    Tensor modified = matrix_a;
    modified.set(0, 0, 100);
    modified.print();

    //Statistics
    cout << "\nSum: " << matrix_a.sum() << endl;
    cout << "Mean: " << matrix_a.mean() << endl;

    cout << "\nRow 0 Sum: " << matrix_a.row_sum(0) << endl;
    cout << "Row 1 Sum: " << matrix_a.row_sum(1) << endl;

    cout << "\nColumn 0 Sum: " << matrix_a.col_sum(0) << endl;
    cout << "Column 1 Sum: " << matrix_a.col_sum(1) << endl;
    cout << "Column 2 Sum: " << matrix_a.col_sum(2) << endl;

    cout << "\nRow 0 Mean: " << matrix_a.row_mean(0) << endl;
    cout << "Row 1 Mean: " << matrix_a.row_mean(1) << endl;

    cout << "\nColumn 0 Mean: " << matrix_a.col_mean(0) << endl;
    cout << "Column 1 Mean: " << matrix_a.col_mean(1) << endl;
    cout << "Column 2 Mean: " << matrix_a.col_mean(2) << endl;

    return 0;
}