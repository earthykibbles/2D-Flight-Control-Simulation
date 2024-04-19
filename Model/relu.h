#pragma once
#include <iostream>
#include <vector>

class Relu {
public:
	std::vector<std::vector<float>> inputData;
	std::vector<int> input_shape;

	Relu(std::vector<int> input_shape, std::vector<std::vector<float>> inputData);

	float max(double a, double b);
	std::vector<std::vector<float>> compute();
};