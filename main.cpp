#include <iostream>

#include "class/Table.h"


int main() {
	setlocale(LC_ALL, "ru");
	std::cout << "Таблица\n" << std::endl;
	
	try {
		size_t rows = 3;
		size_t cols = 6;
		Table<int> table(rows, cols);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				table[i][j] = (i + 1) * (j + 1);
			}
		}

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				std::cout << table[i][j] << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		std::cout << "Всего элементов: " << table.size() << std::endl;
	}
	catch (std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}

	system("pause > nul");
	return 0;
}