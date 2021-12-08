#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "profile.h"

const size_t SIZE = 8;

std::ostream& operator<<(std::ostream& stream, const std::vector<std::vector<bool>>& data) {
	for (const auto& row : data) {
		for (const auto& item : row) {
			stream << item << " ";
		}
		stream << std::endl;
	}
	return stream;
}

using namespace std;

size_t get_right_dio_index(const int& row, const int& column) {
	return row + column;
}

size_t get_left_dio_index(const int& row, const int& column) {
	return row - column + SIZE - 1;
}

bool calculate_arrangements(
		vector<vector<bool>>& board,
		const int& column,
		vector<bool>& occupied_rows,
		vector<bool>& occupied_right_dio,
		vector<bool>& occupied_left_dio
) {
	if (column >= SIZE) return true; // base case: If all queens are placed then return true

	//Consider this column and try placing this queen in all rows one by one
	for (int row = 0; row < SIZE; row++) {
		// Check if queen can be placed on board[row][col]
		bool can_not_be_placed = occupied_rows[row] || occupied_right_dio[get_right_dio_index(row, column)] || occupied_left_dio[get_left_dio_index(row, column)];
		if (!can_not_be_placed) /* can be placed */{
			// Place this queen in board[row][col]
			board[row][column] = true;
			occupied_rows[row] = true;
			occupied_right_dio[get_right_dio_index(row, column)] = true;
			occupied_left_dio[get_left_dio_index(row, column)] = true;

			// recur to place rest of the queens
			if (calculate_arrangements(board, column + 1, occupied_rows, occupied_right_dio, occupied_left_dio)) {
				return true;
			}

			// If placing queen in board[row][col] doesn't lead to a solution, then backtrack
			// Remove queen from board[row][col]
			board[row][column] = false;
			occupied_rows[row] = false;
			occupied_right_dio[get_right_dio_index(row, column)] = false;
			occupied_left_dio[get_left_dio_index(row, column)] = false;

		}
	}

	// If queen can not be place in any row in this column col then return false
	return false;
}

int main() {

	{
		vector<vector<bool>> board(SIZE);
		for (auto& row : board) row.assign(SIZE, false);

		vector<bool> occupied_rows(SIZE , false);
		vector<bool> occupied_right_dio(2 * SIZE - 1 , false);
		vector<bool> occupied_left_dio(2 * SIZE - 1 , false);
		LOG_DURATION("Bound & brunch method")
		calculate_arrangements(board, 0 , occupied_rows, occupied_right_dio, occupied_left_dio);
		cout << board << endl;
	}
	return 0;
}
