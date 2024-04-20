
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

	std::vector<std::vector<float>> l1_out;
	std::vector<std::vector<float>> rl1_out;
	std::vector<std::vector<float>> l2_out;
	std::vector<std::vector<float>> rl2_out;
	std::vector<std::vector<float>> l3_out;


	Model(std::vector<int> input_shape) :
		l1(input_shape, 16),
		rl1(l1.output_shape),
		l2(rl1.output_shape, 32),
		rl2(l2.output_shape),
		l3(rl2.output_shape, 2)
	{}

	
	std::vector < std::vector<float>> forward(std::vector<std::vector<float>> inputData) {
		l1_out = l1.compute(inputData);
		rl1_out = rl1.compute(l1_out);
		l2_out = l2.compute(rl1_out);
		rl2_out = rl2.compute(l2_out);
		l3_out = l3.compute(rl2_out);
		return l3_out;
	}


	void backward(float loss) {
		// Final Layer
		float outputgrad5 = loss;

		//l3 Backpropagation
		float outputgrad4 = outputgrad5;


		//rl2 Backpropagation
		std::vector<std::vector<float>> l2_deriv = rl2.computeDerivative(l2_out);
		std::vector<std::vector<float>> outputgrad3;

		for (size_t i = 0; i < l2_deriv.size(); ++i) {
			std::vector<float> temp_og3;
			for (size_t j = 0; j < l2_deriv.size(); ++j) {
				temp_og3.push_back(l2_deriv[i][j] * outputgrad4);
			}
			outputgrad3.push_back(temp_og3);
		}

		//l2 Backpropagation
		// Iterate through the original matrix and fill the new matrix
		std::vector<std::vector<float>> trans_l3weights(l3.weights[0].size(),
			std::vector<float>(l3.weights.size()));
		std::vector<std::vector<float>> outputgrad2;


		//Transpose the Weight Matrix
		for (int i = 0; i < l3.weights[0].size(); ++i) {
			for (int j = 0; j < l3.weights.size(); ++j) {
				trans_l3weights[i][j] = l3.weights[j][i];
			}
		}
		//Compute
		for (int i = 0; i < trans_l3weights.size(); ++i) {
			std::vector<float> temp_og2;
			for (int j = 0; j < outputgrad3[0].size(); ++j) {
				float summation = 0;
				for (int k = 0; k < outputgrad3.size(); ++k) {
					summation += trans_l3weights[i][k] * outputgrad3[k][j];
				}
				temp_og2.push_back(summation);
			}
			outputgrad2.push_back(temp_og2);
		}
		std::cout << "Success" << std::endl;

		//rl1 Backpropagation
		std::vector<std::vector<float>> l1_deriv = rl1.computeDerivative(l1_out);
		std::vector<std::vector<float>> outputgrad1(outputgrad2.size(), std::vector<float>(outputgrad2[0].size(), 0.0));

		for (size_t i = 0; i < outputgrad2.size(); ++i) {
			for (size_t j = 0; j < l1_deriv[0].size(); ++j) {
				outputgrad1[i][j] = outputgrad2[i][j] * l1_deriv[i][j];
			}
		}
		std::cout << "Success" << std::endl;

		//Gradients of the parameters
		//L1
		std::vector<std::vector<float>> trans_inputData(l1.inputData[0].size(), std::vector<float>(l1.inputData.size(), 0.0));
		std::vector<std::vector<float>> weightGrad1(outputgrad1.size(), std::vector<float>(trans_inputData[0].size(), 0.0));


		//Transpose the Weight Matrix
		for (size_t i = 0; i < l1.inputData.size(); ++i) {
			for (size_t j = 0; j < l1.inputData[0].size(); ++j) {
				trans_inputData[i][j] = l1.inputData[j][i];
			}
		}

		for (size_t i = 0; i < outputgrad1.size(); ++i) {
			for (size_t j = 0; j < trans_inputData[0].size(); ++j) {
				for (size_t k = 0; k < trans_inputData.size(); ++k) {
					weightGrad1[i][j] += outputgrad1[i][k] * trans_inputData[k][j];
				}
			}
		}

		//L2
		std::vector<std::vector<float>> trans_rl1out(rl2_out[0].size(), std::vector<float>(rl2_out.size(), 0.0));
		std::vector<std::vector<float>> weightGrad2(outputgrad1.size(), std::vector<float>(trans_inputData[0].size(), 0.0));

		//Transpose the Weight Matrix
		for (size_t i = 0; i < rl2_out.size(); ++i) {
			for (size_t j = 0; j < rl2_out[0].size(); ++j) {
				trans_rl1out[i][j] = rl2_out[j][i];
			}
		}

		for (size_t i = 0; i < outputgrad3.size(); ++i) {
			for (size_t j = 0; j < trans_rl1out[0].size(); ++j) {
				for (size_t k = 0; k < trans_rl1out.size(); ++k) {
					weightGrad2[i][j] += outputgrad3[i][k] * trans_rl1out[k][j];
				}
			}
		}
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