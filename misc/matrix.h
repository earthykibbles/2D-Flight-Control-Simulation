#pragma once
#include <iostream>
#include <vector>


namespace MatOperations {
	std::vector<std::vector<float>> matmul(std::vector <std::vector<float>>& mata, std::vector<std::vector<float>>& matb) {
		size_t rowsA = mata.size(); // Number of rows in matrixA
		size_t colsA = mata[0].size(); // Number of columns in matrixA
		size_t rowsB = matb.size(); // Number of rows in matrixB
		size_t colsB = matb[0].size(); // Number of columns in matrixB

		// Check if the number of columns in matrixA matches the number of rows in matrixB
		if (colsA != rowsB) {
			std::cerr << "Matrix multiplication not possible. Columns of matrix A must match rows of matrix B." << std::endl;
			return {};
		}

		std::vector< std::vector<float>> output(rowsA, std::vector<float>(colsB, 0.0));

		for (size_t i = 0; i < rowsA; ++i) {
			for (size_t j = 0; j < colsB; ++j) {
				for (size_t k = 0; k < rowsB; ++k) {
					output[i][j] += mata[i][k] * matb[k][j];
				}
			}
		}

		return output;
	}

	std::vector<std::vector<float>> matscal(std::vector <std::vector<float>>& mata, float scal) {
		size_t rowsA = mata.size(); // Number of rows in matrixA
		size_t colsA = mata[0].size(); // Number of columns in matrixA

		std::vector< std::vector<float>> output(rowsA, std::vector<float>(colsA, 0.0));

		for (size_t r = 0; r < rowsA; r++) {
			for (size_t c = 0; c < colsA; c++) {
				output[r][c] = mata[r][c] * scal;
			}
		}

		return output;
	}

	std::vector<std::vector<float>> matelementwise(std::vector <std::vector<float>>& mata, std::vector <std::vector<float>>& matb) {
		size_t rowsA = mata.size(); // Number of rows in matrixA
		size_t colsA = mata[0].size(); // Number of columns in matrixA
		size_t rowsB = matb.size(); // Number of rows in matrixB
		size_t colsB = matb[0].size(); // Number of columns in matrixB

		// Check if the number of columns in matrixA matches the number of rows in matrixB
		if (colsA != colsB && rowsA != rowsB) {
			std::cerr << "Element Wise Matrix multiplication not possible. Columns, Rows of matrix A must match Columns, Rows of matrix B." << std::endl;
			return {};
		}

		std::vector< std::vector<float>> output(rowsA, std::vector<float>(colsB, 0.0));

		for (size_t r = 0; r < rowsA; r++) {
			for (size_t c = 0; c < colsA; c++) {
				output[r][c] = mata[r][c] * matb[r][c];
			}
		}

		return output;
	}


	std::vector<std::vector<float>> matadd(std::vector <std::vector<float>>& mata, std::vector<std::vector<float>>& matb) {
		size_t rowsA = mata.size(); // Number of rows in matrixA
		size_t colsA = mata[0].size(); // Number of columns in matrixA
		size_t rowsB = matb.size(); // Number of rows in matrixB
		size_t colsB = matb[0].size(); // Number of columns in matrixB

		// Check if the number of columns in matrixA matches the number of rows in matrixB
		if (colsA != colsB && rowsA != colsA) {
			std::cerr << "Matrix Addition not possible. Your matrix must be a square matrix." << std::endl;
			return {};
		}
		std::vector< std::vector<float>> output(rowsA, std::vector<float>(colsB, 0.0));

		for (size_t r = 0; r < rowsA; r++) {
			for (size_t c = 0; c < colsB; c++) {
				output[r][c] = mata[r][c] + matb[r][c];
			}
		}

		return output;
	}

	std::vector<std::vector<float>> matsub(std::vector <std::vector<float>>& mata, std::vector<std::vector<float>>& matb) {
		size_t rowsA = mata.size(); // Number of rows in matrixA
		size_t colsA = mata[0].size(); // Number of columns in matrixA
		size_t rowsB = matb.size(); // Number of rows in matrixB
		size_t colsB = matb[0].size(); // Number of columns in matrixB

		// Check if the number of columns in matrixA matches the number of rows in matrixB
		if (colsA != colsB && rowsA != colsA) {
			std::cerr << "Matrix Subtraction not possible. Your matrix must be a square matrix." << std::endl;
			return {};
		}

		std::vector< std::vector<float>> output(rowsA, std::vector<float>(colsB, 0.0));

		for (size_t r = 0; r < rowsA; r++) {
			for (size_t c = 0; c < colsB; c++) {
				output[r][c] = mata[r][c] - matb[r][c];
			}
		}

		return output;
	}

	std::vector<std::vector<float>> transpose(std::vector <std::vector<float>>& mata) {
		std::vector<std::vector<float>> output(mata[0].size(),
			std::vector<float>(mata.size(), 0.0));

		//Transpose the Weight Matrix
		for (size_t i = 0; i < mata[0].size(); ++i) {
			for (size_t j = 0; j < mata.size(); ++j) {
				output[i][j] = mata[j][i];
			}
		}

		return output;
	}

	std::string matsize(std::vector <std::vector<float>>& mata) {
		return "Size of matrix: " + std::to_string(mata.size()) + std::to_string(mata[0].size()) + "\n";
	}
}