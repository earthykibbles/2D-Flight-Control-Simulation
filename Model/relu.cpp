
#include 'relu.h'

class Relu {

	Relu(int input_shape, std::vector<float> input) : input_shape(input_shape), input(z) {}

	std::vector<float> compute() {
		std::vector<float> tempA;

		for (int im = 0; im < input_shape; im++) {
			float max_value;
			auto max_iter = std::max_element(z.begin(), z.end(), 0);
			if (max_iter < z.end()) {
				max_value = *max_iter;
			}
			tempA.push_back(max_value);
		}

		return tempA;
	}
		
};