
#include "linear.h"
#include <random>

Linear::Linear(std::vector<int> input_shape, int outputDim) : input_shape(input_shape), outputDim(outputDim){
	weights = generateWeights();
	bias = generateBias();
	output_shape = getOutputShape();
}


std::vector<std::vector<float>> Linear::generateWeights() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0,1);

	std::vector<std::vector<float>> tempWeights;

	for (int r = 0; r < input_shape[1]; r++) {
		std::vector<float> weights_temp;
		for (int c = 0; c < outputDim; c++) {
			weights_temp.push_back(dis(gen));
		}
		tempWeights.push_back(weights_temp);
	}

	return tempWeights;
}


std::vector<float> Linear::generateBias() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0, 0.2);

	std::vector<float> bias_temp;

	for (int r = 0; r < outputDim; r++) {
		bias_temp.push_back(dis(gen));
	}

	return bias_temp;
}

std::vector<int> Linear::getOutputShape() {
	return{ input_shape[0], outputDim };
};

std::vector<std::vector<float>>  Linear::compute(std::vector<std::vector<float>> &inputData) {
	this->inputData = inputData;
	float rowsA = inputData.size(); // Number of rows in matrixA
	float colsA = inputData[0].size(); // Number of columns in matrixA
	float rowsB = weights.size(); // Number of rows in matrixB
	float colsB = weights[0].size(); // Number of columns in matrixB

	// Check if the number of columns in matrixA matches the number of rows in matrixB
	if (colsA != rowsB) {
		std::cerr << "Matrix multiplication not possible. Columns of matrix A must match rows of matrix B." << std::endl;
		return {};
	}

	std::vector<std::vector<float>> result(inputData.size(), std:: vector<float>(weights[0].size(), 0.0));

	// Perform matrix multiplication
	for (size_t i = 0; i < inputData.size(); ++i) {
		for (size_t j = 0; j < weights[0].size(); ++j) {
			for (size_t k = 0; k < weights.size(); ++k) {
				result[i][j] += inputData[i][k] * weights[k][j];
			}
		}
	}

	weights = generateWeights();
	
	return result;
}

