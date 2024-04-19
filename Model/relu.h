


class Relu {
public:
	std::vector<float> z;

	Relu(int input_shape, std::vector<float> input);

	std::vector<float> compute();
};