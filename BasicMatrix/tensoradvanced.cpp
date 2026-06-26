#include <iostream>
#include <vector>


using namespace std;

struct Point {
    vector<float> coords;
};



struct Tensor {
    vector<float> data;
    int rows;
    int cols;

    //Runs when Tensor is created
    Tensor(vector<vector<float>> matrix_2d){
        rows = matrix_2d.size();
        cols = rows > 0 ? matrix_2d[0].size() : 0; // condition ? value_ifTrue : value_ifFalse
        // Flatten 2d to 1d
        for (const auto& row : matrix_2d) {
            for (float value : row) {
                data.push_back(value);
            }
        }
    }

    float get(int r, int c) const{
        int index = (r * cols) + c;
        return data[index];
    }



    void print() const {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                cout << get(r, c) << " ";
            }
            cout << endl;
        }
    }


    vector<float> getRow(int r) const {
        vector<float> row;
        for (int c = 0; c < cols; c++) {
            row.push_back(get(r, c));
        }
        return row;
    }

    vector<float> getCol(int c) const {
        vector<float> col;
        for (int r = 0; r < rows; r++) {
            col.push_back(get(r, c));
        }
        return col;
    }

    Tensor(int r, int c) { //Blank tensor
        rows = r;
        cols = c;
        data.resize(r * c, 0.0f);
    }

    void set(int r, int c, float val) { //set items to value
        data[r * cols + c] = val;
    }


};



float dot(const Point& a, const Point& b){
    float final = 0.0f;
    for (size_t i = 0; i < a.coords.size(); i++){
        final += a.coords[i] * b.coords[i];
    };
    return final;
}



Tensor multiply(const Tensor& a, const Tensor& b) {

    Tensor result(a.rows, b.cols);

    for (size_t i = 0; i < a.rows; i++) {

        vector<float> rowA = a.getRow(i);

        for (size_t j = 0; j < b.cols; j++) {

            vector<float> colB = b.getCol(j);

            float sum = 0.0f;
            for (size_t k = 0; k < rowA.size(); k++) {
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

    Tensor My_tensor({{1, 2}, {3, 4}});

    cout << "Dot:" << dot(a, b) << "\n";
    cout << "Matrix A*B: \n";
    finalmult.print();


}