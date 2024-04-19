
#include "linear.h"

Linear::Linear(int input_shape, std::vector<float> input) : input_shape(input_shape), input(input) {
	weights = getWeights();
	bias = getBias();
}


std::vector<std::vector<float>> generateWeights() {
	std::random_device rd;
	std::mt19937 gen();
	std::uniform_real_distribution<float> dis(0,1);

	std::vector<std::vector<float>> tempWeights;

	for (int r = 0; r < input_shape; r++) {
		std::vector<float> weights_temp;
		for (int c = 0; c < input_shape; c++) {
			weights_temp.push_back(dis(gen));
		}
	}

	return tempWeights;
}


std::vector<float> generateBias() {
	std::random_device rd;
	std::mt19937 gen();
	std::uniform_real_distribution<float> dis(0, 1);

	std::vector<float> bias_temp;

	for (int r = 0; r < input_shape; r++) {
		bias_temp.push_back(dis(gen));
	}

	return bias_temp;
}

std::vector<float> Linear::compute() {
	std::vector<float> tempA;
	for (int r = 0; r < input_shape; r++) {
		float summation;
		for (int c = 0; c < shape; c++) {
			summation += weights[r][c] * input[c] + bias[c];
		}
		tempA.push_back(summation);
	}
	return tempA;
}

