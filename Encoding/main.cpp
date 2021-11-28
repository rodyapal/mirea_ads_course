#include <iostream>
#include "HuffmanCoder.h"
#include "ShennonFanoCoder.h"
#include "utils.h"

int main() {
	HuffmanCoder huffman_coder = HuffmanCoder::from("huffman_input.txt");
	auto huffman_codes_file = std::ofstream("huffman_code_table.txt");
	huffman_coder.print_codes(huffman_codes_file);
	auto huffman_encoded = huffman_coder.encode();
	auto huffman_encoded_file = std::ofstream("huffman_encoded.bin", std::ios::binary);
	auto huffman_byte_encoded = to_byte(chunks(huffman_encoded));
	for (const Byte& byte : huffman_byte_encoded) {
		huffman_encoded_file << byte;
	}
	std::cout << huffman_coder.decode(huffman_encoded) << std::endl;

	ShennonFanoCoder shennon_fano_coder = ShennonFanoCoder::from("shennon_fano_input.txt");
	auto shennon_fano_codes_file = std::ofstream("shennon_fano_code_table.txt");
	shennon_fano_coder.print_codes(shennon_fano_codes_file);
	auto shennon_fano_encoded = shennon_fano_coder.encode();
	auto shennon_fano_encoded_file = std::ofstream("shennon_fano_encoded.bin", std::ios::binary);
	auto shennon_fano_byte_encoded = to_byte(chunks(shennon_fano_encoded));
	for (const Byte& byte : shennon_fano_byte_encoded) {
		shennon_fano_encoded_file << byte;
	}
	std::cout << shennon_fano_coder.decode(shennon_fano_encoded) << std::endl;
	return 0;
}