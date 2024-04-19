
#include "linear.h"
#include <random>

Linear::Linear(std::vector<int> input_shape, std::vector<std::vector<float>> inputData, int outputDim) : input_shape(input_shape), inputData(inputData), outputDim(outputDim){
	weights = generateWeights();
	bias = generateBias();
}


std::vector<std::vector<float>> Linear::generateWeights() {
	std::random_device rd;
	std::mt19937 gen();
	std::uniform_real_distribution<float> dis(0,1);

	std::vector<std::vector<float>> tempWeights;

	for (int r = 0; r < input_shape[1]; r++) {
		std::vector<float> weights_temp;
		for (int c = 0; c < outputDim; c++) {
			weights_temp.push_back(dis(gen));
		}
	}

	return tempWeights;
}


std::vector<float> Linear::generateBias() {
	std::random_device rd;
	std::mt19937 gen();
	std::uniform_real_distribution<float> dis(0, 1);

	std::vector<float> bias_temp;

	for (int r = 0; r < outputDim; r++) {
		bias_temp.push_back(dis(gen));
	}

	return bias_temp;
}

std::vector<std::vector<float>>  Linear::compute() {
	float rowsA = inputData.size(); // Number of rows in matrixA
	float colsA = inputData[0].size(); // Number of columns in matrixA
	float rowsB = weights.size(); // Number of rows in matrixB
	float colsB = weights[0].size(); // Number of columns in matrixB

	// Check if the number of columns in matrixA matches the number of rows in matrixB
	if (colsA != rowsB) {
		std::cerr << "Matrix multiplication not possible. Columns of matrix A must match rows of matrix B." << endl;
		return {};
	}

	std::vector<std::vector<float>> result(rowsA, std::vector<float>(colsB, 0.0));


	for (int r = 0; r < rowsA; r++) {
		for (int c = 0; c < colsB; c++) {
			for (size_t k = 0; k < colsA; k++) {
				result[r][c] += (inputData[r][k] * weights[k][c]) + bias[k];
			}
			
		}
	}
	return result;
}

