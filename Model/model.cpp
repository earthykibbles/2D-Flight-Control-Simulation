
#include <iostream>
#include "linear.h"
#include "relu.h"


class Model {
	std::vector<int> input_shape;
	std::vector<std::vector<float>> inputData;
	std::vector<std::vector<float>> outputData;


	Model(){
		std::vector<std::vector<float>> l1 = Linear(input_shape, inputData, 16).compute();
		std::vector<std::vector<float>> rl1 = Relu(input_shape, l1).compute();
		std::vector < std::vector<float >> l2 = Linear(input_shape, rl1, 10).compute();
		std::vector<std::vector<float>> rl2 = Relu(input_shape, l2).compute();
	}	
};