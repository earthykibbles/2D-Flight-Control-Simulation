#pragma once
#include <iostream>
#include <iomanip>
#include "linear.h"
#include "relu.h"
#include "sigmoid.h"

#include "../misc/matrix.h"

#define print(x) std::cout << x<<std::endl

using namespace MatOperations;

class Model {
public:
	const float learningRate = 0.05;
	std::vector<int> input_shape;
	std::vector<std::vector<float>> inputData;
	std::vector<std::vector<float>> outputData;


	// Linear Layers
	Linear l1;
	Sigmoid rl1;
	Linear l2;
	Sigmoid rl2;
	Linear l3;
	Sigmoid rl3;

	std::vector<std::vector<float>> l1_out;
	std::vector<std::vector<float>> rl1_out;
	std::vector<std::vector<float>> l2_out;
	std::vector<std::vector<float>> rl2_out;
	std::vector<std::vector<float>> l3_out;
	std::vector<std::vector<float>> rl3_out;


	Model(std::vector<int> input_shape) :
		l1(input_shape, 16), //10x10 10x16 = 10x16
		rl1(l1.output_shape), //10x16 
		l2(rl1.output_shape, 32), //10x16 16*32 = 10x32
		rl2(l2.output_shape),  //10x32
		l3(rl2.output_shape, 2), //10*32 32*2 = 10x2
		rl3(l3.output_shape) //10x2
	{}

	
	std::vector < std::vector<float>> forward(std::vector<std::vector<float>> inputData) {
		l1_out = l1.compute(inputData);
		rl1_out = rl1.compute(l1_out);
		l2_out = l2.compute(rl1_out);
		rl2_out = rl2.compute(l2_out);
		l3_out = l3.compute(rl2_out);
		rl3_out = rl3.compute(l3_out);
		return rl3_out;
	}


	void backward(float loss) {
		// Final Layer
		float outputgrad6 = loss;

		// rl3 propagation
		std::vector<std::vector<float>> l3_deriv = rl2.computeDerivative(l3_out); // 10x2
		std::vector<std::vector<float>> outputgrad5 = matscal(l3_deriv, outputgrad6); // 10x2

		//l3 Backpropagation
		std::vector<std::vector<float>> trans_l3weights = transpose(l3.weights); //2x32
		std::vector<std::vector<float>> outputgrad4 = matmul(outputgrad5, trans_l3weights);// 10x2 2x32 = 10x32

		//rl2 Backpropagation
		std::vector<std::vector<float>> l2_deriv = rl2.computeDerivative(l2_out); //10x32
		std::vector<std::vector<float>> outputgrad3 = matelementwise(l2_deriv, outputgrad4); //10x32 10x32 = 10x32

		//l2 Backpropagation
		std::vector<std::vector<float>> trans_l2weights = transpose(l2.weights); //32x16
		std::vector<std::vector<float>> outputgrad2 = matmul(outputgrad3, trans_l2weights); // 10x32 32x16 = 10x16

		//rl1 Backpropagation
		std::vector<std::vector<float>> l1_deriv = rl1.computeDerivative(l1_out); // 10x16
		std::vector<std::vector<float>> outputgrad1 = matelementwise(l1_deriv, outputgrad2); //10x16 10x16 = 10x16

		//Gradients of the parameters
		//L1
		std::vector<std::vector<float>> trans_inputData =  transpose(l1.inputData); // 10x10
		std::vector<std::vector<float>> weightGrad1 = matmul(trans_inputData, outputgrad1); // 10x10 10x16 = 10x16
		std::vector<std::vector<float>> biasGrad1 = outputgrad1; // 10x16

		//L2
		std::vector<std::vector<float>> trans_rl1out = transpose(rl1_out); //16x10
		std::vector<std::vector<float>> weightGrad2 = matmul(trans_rl1out, outputgrad3); //16x10 10x32 = 16x32
		std::vector<std::vector<float>> biasGrad2 = outputgrad3; //16x32

		//L3
		std::vector<std::vector<float>> trans_rl2out = transpose(rl2_out); // 32x16
		//std::vector<std::vector<float>> weightGrad3 = matmul(trans_rl1out, outputgrad5); //32x16 10x2

		// Update Parameters
		std::vector<std::vector<float>> tempJ1 = matscal(weightGrad1, learningRate);
		std::vector<std::vector<float>> tempJ2 = matscal(weightGrad2, learningRate);
		//std::vector<std::vector<float>> tempJ3 = matscal(weightGrad3, learningRate);

		l1.weights = matsub(l1.weights, tempJ1);
		
		l2.weights = matsub(l2.weights, tempJ2);
		//l3.weights = matsub(l3.weights, tempJ3);
		
		/*	printWeights(l2_deriv);
	printWeights(outputgrad3);
	printWeights(l1_deriv);
	printWeights(outputgrad2);
	printWeights(outputgrad1);
	printWeights(l1.weights);
	printWeights(l2.weights);
		printWeights(l1.weights);
		printWeights(l2.weights);*/
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