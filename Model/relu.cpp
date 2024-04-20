
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
    std::vector<std::vector<float>> result(inputData.size(), std::vector<float>(inputData[0].size(), 0.0));

    // Apply ReLU to each element of the matrix
    for (size_t i = 0; i < inputData.size(); i++) {
        std::vector<float> temp_ph;
        for (size_t j = 0; j < inputData[i].size(); j++) {
            temp_ph.push_back(max(0.0, inputData[i][j]));
        }
        result.push_back(temp_ph);
    }
    std::cout << "opp success" << std::endl;

    return result;
}
		