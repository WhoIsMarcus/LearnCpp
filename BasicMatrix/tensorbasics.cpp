#include <iostream>
#include <vector>


using namespace std;

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

};


Tensor add(const Tensor& a, const Tensor& b) {

    Tensor result = a;

    for (size_t i = 0; i < a.data.size(); ++i) {
        result.data[i] = a.data[i] + b.data[i];
    }
    return result;
}

Tensor subtract(const Tensor& a, const Tensor& b) {

    Tensor result = a;

    for (size_t i = 0; i < a.data.size(); ++i) {
        result.data[i] = a.data[i] - b.data[i];
    }
    return result;


}






int main() {
    Tensor matrix_a({{1, 2, 3}, {4, 5, 6}});
    Tensor matrix_b({{8, 3, 12}, {5, 6, 9}});

    Tensor finaladd = add(matrix_a, matrix_b);
    Tensor finalsub = subtract(matrix_a, matrix_b);
    finaladd.print();
    finalsub.print();
}




