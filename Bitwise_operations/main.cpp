#include <iostream>
#include <fstream>
#include <bitset>
#include <array>
#include <vector>
#include <cmath>
using namespace std;

void taskOneA() {
    unsigned char number = 255;
    unsigned char mask = 1;
    cout << (int)(number & (~(mask << 4))) << endl; //should be 239
}

void taskOneB() {
    unsigned char number = 0;
    unsigned char mask = 64;
    cout << (int)(number | mask) << endl; //should be 64
}

void taskOneC() {
    unsigned int number = 25;
    const int bitsAmount = sizeof(int) * 8; //32
    unsigned mask = (1 << bitsAmount - 1);
    cout << "Mask at the beginning: " << bitset<bitsAmount>(mask) << endl;
    cout << "Result: ";
    for (int i = 1; i <= bitsAmount; i++) {//Prints value of number
        cout << ((number & mask) >> (bitsAmount - i)); //prints 1 if number & mask is true, else prints 0
        mask = mask >> 1;
    }
    cout << endl;
}

void taskTwo() {
    int size, number = 0, result = 0;
    cout << "Size of number sequence: ";
    cin >> size;
    cout << "Sequence: ";
    for (int i = 0; i < size; i++) {
        cin >> number;
        result += (int)pow(2, number);
    }
    cout << bitset<8>(result) << endl;
}

int main() {
    taskOneA();
    taskOneB();
    taskOneC();
    taskTwo();
    return 0;
}