//
// Created by Rodya on 03.04.2021.
//

#ifndef THIRD_PART_ONE_H
#define THIRD_PART_ONE_H

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

void delOtherMethod(int* array, size_t size, const int& delete_val) {
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

#endif //THIRD_PART_ONE_H
