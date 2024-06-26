
#include "relu.h"
#include <cmath>

Relu::Relu(std::vector<int> input_shape) : input_shape(input_shape), inputData(inputData) {
    output_shape = getOutputShape();
}

// Function to get the maximum between two numbers
float Relu::max(double a, double b) {
    // Return the maximum of the two numbers
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

std::vector<int> Relu::getOutputShape() {
    return { input_shape[0], input_shape[1] };
}
std::vector<std::vector<float>> Relu::compute(std::vector<std::vector<float>> &inputData) {
    this->inputData = inputData;
    std::vector<std::vector<float>> result(inputData.size(), std::vector<float>(inputData[0].size(), 0.0));

    // Apply ReLU to each element of the matrix
    for (int r = 0; r < input_shape[0]; ++r) {
        for (int c = 0; c < input_shape[1]; ++c) {
            result[r][c] = max(0.0, inputData[r][c]);
        }
    }
    return result;
}
		