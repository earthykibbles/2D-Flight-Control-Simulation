#pragma once

#include <iostream>
#include <vector>
#include <string>


class Linear {
public:
	int input_shape;
	std::vector<std::vector<float>> weights;
	std::vector<float> bias;

	Linear(int input_shape, std::vector<float> input);

	std::vector<std::vector<float>>  generateWeights();
	std::vector<float>  generateBias();
	std::vector<float>  compute();
};