//
// Created by Rodya on 08.09.2021.
//

#ifndef ONE_H
#define ONE_H

#include <iostream>
#include <bitset>

namespace taskOne {
	void a() {
		unsigned char number = 255;
		unsigned char mask = 1;
		std::cout << (int)(number & (~(mask << 4))) << std::endl; //should be 239
	}

	void b() {
		unsigned char number = 0;
		unsigned char mask = 128;
		std::cout << (int)(number | mask) << std::endl; //should be 128
	}

	void c() {
		unsigned int number = 25;
		const int bitsAmount = sizeof(int) * 8; //32
		unsigned mask = (1 << (bitsAmount - 1)); //2^31
		std::cout << "Mask at the beginning: " << std::bitset<bitsAmount>(mask) << std::endl;
		std::cout << "Result: ";
		for (int i = 1; i <= bitsAmount; i++) {//Prints value of number
			std::cout << ((number & mask) >> (bitsAmount - i)); //prints 1 if number & mask is true, else prints 0
			mask = mask >> 1;
		}
		std::cout << std::endl;
	}
}

void runTaskOne() {
	taskOne::a();
	taskOne::b();
	taskOne::c();
}

#endif //ONE_H
