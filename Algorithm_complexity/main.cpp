#include <iostream>
#include <random>
#include <vector>
#include <climits>
#include "profile.h"

using namespace std;

void delFirstMethod(int* array, size_t size, const int& delete_val) {
    int comps = 0, moves = 0;
    int index = 0;
    while (index < size) {
        comps++;
        if (comps++; array[index] == delete_val) {
            for (int del_index = index; del_index < size - 1; del_index++) {
                array[del_index] = array[del_index + 1];
                comps++;
                moves++;
            }
            size--;
        }
        else index++;
    }
    clog << "delFirstMethod: {\n\t" << "Comps: " << comps << "\n\t" << "Moves: " << moves << "\n}" << endl;
}

void delOtherMethod(int* array, size_t& size, const int& delete_val) {
    int comps = 0, moves = 0;
    int new_size = 0;
    for (int index = 0; index < size; index++) {
        array[new_size] = array[index];
        if (array[index] != delete_val) new_size++;
        comps += 2;
        moves++;
    }
    size = new_size;
    clog << "delOtherMethod: {\n\t" << "Comps: " << comps << "\n\t" << "Moves: " << moves << "\n}" << endl;
}

template<class Iterator>
void fill_random(Iterator first, Iterator last) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution distribution;
    for(auto it = first; it != last; it++) *it = distribution(generator);
}

using Matrix = vector<vector<int>>;

int max_in_upper(const Matrix& data) { LOG_DURATION("max_in_upper")
    int max_item = INT32_MIN;
    for (int row = 0; row < data.size() - 1; row++)
        for (int column = row + 1; column < data[row].size(); column++)
            if (max_item < data[row][column]) max_item = data[row][column];

    return max_item;
}

Matrix get_matrix(const size_t& size) { LOG_DURATION("Matrix created")
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution distribution;

    Matrix matrix(size);
    for (vector<int>& row : matrix) {
        row.resize(size);
        for (int& item : row) item = distribution(generator);
    }
    return matrix;
}

int main() {
    Matrix matrix = get_matrix(10'000);
    cout << endl << max_in_upper(matrix) << endl;
    return 0;
}
