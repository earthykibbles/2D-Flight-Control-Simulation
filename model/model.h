
#include <iostream>
#include "linear.h"
#include "relu.h"
#include "sigmoid.h"


class Model {
public:
	float learningRate;
	std::vector<int> input_shape;
	std::vector<std::vector<float>> inputData;
	std::vector<std::vector<float>> outputData;


	// Linear Layers
	Linear l1;
	Sigmoid rl1;
	Linear l2;
	Sigmoid rl2;
	Linear l3;


	Model(std::vector<int> input_shape) :
		l1(input_shape, 16),
		rl1(l1.output_shape),
		l2(rl1.output_shape, 32),
		rl2(l2.output_shape),
		l3(rl2.output_shape, 2)
	{}	


	std::vector < std::vector<float>> forward(std::vector<std::vector<float>> inputData) {
		std::vector<std::vector<float>> l1_out = l1.compute(inputData);
		std::vector<std::vector<float>> rl1_out = rl1.compute(l1_out);
		std::vector < std::vector<float >> l2_out = l2.compute(rl1_out);
		std::vector<std::vector<float>> rl2_out = rl2.compute(l2_out);
		std::vector < std::vector<float>> l3_out = l3.compute(rl2_out);

		//std::cout << std::endl;
		//std::cout << l1_out.size() << " , " << l1_out[0].size() << std::endl;
		//std::cout << rl1_out.size() << " , " << rl1_out[0].size() << std::endl;
		//std::cout << l2_out.size() << " , " << l2_out[0].size() << std::endl;
		//std::cout << rl2_out.size() << " , " << rl2_out[0].size() << std::endl;
		//std::cout << l3_out.size() << " , " << l3_out[0].size() << std::endl;

		//std::cout << std::endl;
		//std::cout << l1.inputData.size() << " , " << l1.inputData[0].size() << std::endl;
		//std::cout << rl1.inputData.size() << " , " << rl1.inputData[0].size() << std::endl;
		//std::cout << l2.inputData.size() << " , " << l2.inputData[0].size() << std::endl;
		//std::cout << rl2.inputData.size() << " , " << rl2.inputData[0].size() << std::endl;
		//std::cout << l3.inputData.size() << " , " << l3.inputData[0].size() << std::endl;

		//std::cout << std::endl;
		//std::cout << l1.weights.size() << " , " << l1.weights[0].size() << std::endl;
		////std::cout << rl1_out.size() << " , " << rl1_out[0].size() << std::endl;
		//std::cout << l2.weights.size() << " , " << l2.weights[0].size() << std::endl;
		////std::cout << rl2_out.size() << " , " << rl2_out[0].size() << std::endl;
		//std::cout << l3.weights.size() << " , " << l3.weights[0].size() << std::endl;
		return l3_out;
	}
	void backward() {
		updateWeights(l1.weights);
		updateWeights(l2.weights);
		updateWeights(l3.weights);
	}


	void updateWeights(std::vector<std::vector<float>>& weights) {
		for (int i = 0; i < weights.size(); i++) {
			for (int j = 0; j < weights[0].size(); j++) {
				weights[i][j] = weights[i][j] - (learningRate * weights[i][j]);
			}
		}
	}

	std::vector<float> predict(std::vector<std::vector<float>>& inputData) {
		std::vector<std::vector<float>> prediction = this -> forward(inputData);
		return prediction[0];
	}
};