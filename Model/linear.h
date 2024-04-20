#pragma once
#include <iostream>
#include <vector>
#include <string>


class Linear {
public:
	std::vector<int> input_shape;
	std::vector<int> output_shape;
	int outputDim;
	std::vector<std::vector<float>> inputData;
	std::vector<std::vector<float>> weights;
	std::vector<float> bias;

	Linear(std::vector<int> input_shape, int outputDim);

	std::vector<std::vector<float>>  generateWeights();
	std::vector<float>  generateBias();
	std::vector<int> getOutputShape();
	std::vector<std::vector<float>>  compute(std::vector<std::vector<float>> &inputData);
};