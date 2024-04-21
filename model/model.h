
#include <iostream>
#include <iomanip>
#include "linear.h"
#include "relu.h"
#include "sigmoid.h"


class Model {
public:
	float learningRate = 0.5;
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
		std::cout << loss << std::endl;

		//l3 Backpropagation
		float outputgrad4 = outputgrad5;


		//rl2 Backpropagation
		std::vector<std::vector<float>> l2_deriv = rl2.computeDerivative(l2_out);
		std::vector<std::vector<float>> outputgrad3;

		//std::cout << l2_deriv.size() << l2_deriv[0].size() << std::endl;

		for (size_t i = 0; i < l2_deriv.size(); ++i) {
			std::vector<float> temp_og3;
			for (size_t j = 0; j < l2_deriv[0].size(); ++j) {
				temp_og3.push_back(l2_deriv[i][j] * outputgrad4);
			}
			outputgrad3.push_back(temp_og3);
		}
		
		//std::cout << outputgrad3.size() << outputgrad3[0].size() << std::endl;

		//l2 Backpropagation
		// Iterate through the original matrix and fill the new matrix
		std::vector<std::vector<float>> trans_l2weights(l2.weights[0].size(),
			std::vector<float>(l2.weights.size()));
		std::vector<std::vector<float>> outputgrad2;


		//Transpose the Weight Matrix
		for (int i = 0; i < l2.weights[0].size(); ++i) {
			for (int j = 0; j < l2.weights.size(); ++j) {
				trans_l2weights[i][j] = l2.weights[j][i];
			}
		}

		//Compute
		for (int i = 0; i < outputgrad3.size(); ++i) {
			std::vector<float> temp_og2;
			for (int j = 0; j < trans_l2weights[0].size(); ++j) {
				float summation = 0;
				for (int k = 0; k < trans_l2weights.size(); ++k) {
					summation += outputgrad3[i][k] * trans_l2weights[k][j];
				}
				temp_og2.push_back(summation);
			}
			outputgrad2.push_back(temp_og2);
		}

		//rl1 Backpropagation
		std::vector<std::vector<float>> l1_deriv = rl1.computeDerivative(l1_out);
		std::vector<std::vector<float>> outputgrad1;

		// Should be similar in size

		for (size_t i = 0; i < outputgrad2.size(); ++i) {
			std::vector<float> temp_og1;
			for (size_t j = 0; j < l1_deriv[0].size(); ++j) {
				temp_og1.push_back(outputgrad2[i][j] * l1_deriv[i][j]);
			}
			outputgrad1.push_back(temp_og1);
		}

		//Gradients of the parameters
		//L1

		std::vector<std::vector<float>> trans_inputData(l1.inputData[0].size(),
			std::vector<float>(l1.inputData.size()));
		std::vector<std::vector<float>> weightGrad1;


		//Transpose the Weight Matrix
		for (int i = 0; i < l1.inputData[0].size(); ++i) {
			for (int j = 0; j < l1.inputData.size(); ++j) {
				trans_inputData[i][j] = l1.inputData[j][i];
			}
		}

		for (size_t i = 0; i < trans_inputData.size(); ++i) {
			std::vector<float> temp_wg1;
			for (size_t j = 0; j < outputgrad1[0].size(); ++j) {
				float summation = 0;
				for (size_t k = 0; k < outputgrad1.size(); ++k) {
					summation+= trans_inputData[i][k] * outputgrad1[k][j];
				}
				temp_wg1.push_back(summation);
			}
			weightGrad1.push_back(temp_wg1);
		}

		//L2
		std::vector<std::vector<float>> trans_rl1out(rl1_out[0].size(),
			std::vector<float>(rl1_out.size()));
		std::vector<std::vector<float>> weightGrad2;


		//Transpose the Weight Matrix
		for (int i = 0; i < rl1_out[0].size(); ++i) {
			for (int j = 0; j < rl1_out.size(); ++j) {
				trans_rl1out[i][j] = rl1_out[j][i];
			}
		}

		for (size_t i = 0; i < trans_rl1out.size(); ++i) {
			std::vector<float> temp_wg2;
			for (size_t j = 0; j < outputgrad3[0].size(); ++j) {
				float summation = 0;
				for (size_t k = 0; k < outputgrad3.size(); ++k) {
					summation += trans_rl1out[i][k] * outputgrad3[k][j];
				}
				temp_wg2.push_back(summation);
			}
			weightGrad2.push_back(temp_wg2);
		}

		printWeights(l2_deriv);
		printWeights(outputgrad3);
		printWeights(l1_deriv);
		printWeights(outputgrad2);
		printWeights(outputgrad1);
		printWeights(l1.weights);
		printWeights(l2.weights);

		// Update Parameters
		for (int r = 0; r < l1.weights.size(); r++) {
			for (int c = 0; c < l1.weights[0].size(); c++) {
				l1.weights[r][c] = l1.weights[r][c] - (learningRate * weightGrad1[r][c]);
			}
		}

		for (int r = 0; r < l2.weights.size(); r++) {
			for (int c = 0; c < l2.weights[0].size(); c++) {
				l2.weights[r][c] = l2.weights[r][c] - (learningRate * weightGrad2[r][c]);
			}
		}

		printWeights(l1.weights);
		printWeights(l2.weights);
	}


	void printWeights(std::vector<std::vector<float>> weightMatrix) {
		std::cout << std::endl;
		std::cout << std::endl;

		for (int r = 0; r < weightMatrix.size(); r++) {
			for (int c = 0; c < weightMatrix[0].size(); c++) {
				std::cout << std::fixed
					<< std::setprecision(2) << weightMatrix[r][c] << "\t";
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
		std::cout << std::endl;

	}

	std::vector<float> predict(std::vector<std::vector<float>>& inputData) {
		std::vector<std::vector<float>> prediction = this -> forward(inputData);
		return prediction[0];
	}
};