
#include "relu.h"
#include <cmath>

Relu::Relu(std::vector<int> input_shape, std::vector<std::vector<float>> inputData) : input_shape(input_shape), inputData(inputData) {}


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
std::vector<std::vector<float>> Relu::compute() {
    std::vector<std::vector<float>> result(inputData.size(), std::vector<float>(inputData[0].size(), 0.0));

    // Apply ReLU to each element of the matrix
    for (size_t i = 0; i < inputData.size(); i++) {
        for (size_t j = 0; j < inputData[i].size(); j++) {
            result[i][j] = max(0.0, inputData[i][j]);
        }
    }

    return result;
}
		