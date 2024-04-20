
#include <iostream>
#include "linear.h"
#include "relu.h"


class Model {
public:
	float learningRate;
	std::vector<int> input_shape;
	std::vector<std::vector<float>> inputData;
	std::vector<std::vector<float>> outputData;


	// Linear Layers
	Linear l1;
	Relu rl1;
	Linear l2;
	Relu rl2;
	Linear l3;


	Model(std::vector<int> input_shape) :
		l1(input_shape, 16),
		rl1(l1.output_shape),
		l2(rl1.output_shape, 32),
		rl2(l2.output_shape),
		l3(rl2.output_shape, 16)
	{

	}	


	std::vector < std::vector<float>> forward(std::vector<std::vector<float>> inputData) {
		std::vector<std::vector<float>> l1_out = l1.compute(inputData);
		std::cout << l1.output_shape[0]<<" , "<< l1.output_shape[1] << std::endl;
		std::vector<std::vector<float>> rl1_out = rl1.compute(l1_out);
		std::cout << rl1.output_shape[0] << " , " << rl1.output_shape[1] << std::endl;
		std::vector < std::vector<float >> l2_out = l2.compute(rl1_out);
		std::cout << l2.output_shape[0] << " , " << l2.output_shape[1] << std::endl;
		std::vector<std::vector<float>> rl2_out = rl2.compute(l2_out);
		std::cout << rl2.output_shape[0] << " , " << rl2.output_shape[1] << std::endl;
		std::vector < std::vector<float>> l3_out = l3.compute(rl2_out);
		std::cout << l3.output_shape[0] << " , " << l3.input_shape[1] << std::endl;

		return l3_out;
	}

	void backward() {

	}


	void predict() {

	}

	void evaluate() {

	}


	void lossFunction() {

	}
};