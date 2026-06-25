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

};


float dot(const Point& a, const Point& b){
    float final = 0.0f;
    for (size_t i = 0; i < a.coords.size(); i++){
        final += a.coords[i] * b.coords[i];
    };
    return final;
}

int main() {

    Point a{{1, 2, 3}};
    Point b{{3, 4, 5}};

    cout << dot(a, b);
}