#pragma once
#include <iostream>
#include <vector>

class Sigmoid {
public:
	std::vector<std::vector<float>> inputData;
	std::vector<int> input_shape;
	std::vector<int> output_shape;

	Sigmoid(std::vector<int> input_shape);

	float max(double a, double b);
	std::vector<int> getOutputShape();
	std::vector<std::vector<float>> compute(std::vector<std::vector<float>>& inputData);
	std::vector<std::vector<float>> computeDerivative(std::vector<std::vector<float>>& data);
};