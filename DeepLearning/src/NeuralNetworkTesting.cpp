//
// Created by 26326 on 25-8-26.
//

#include "NeuralNetworkTesting.hpp"

using namespace ml;

void NeuralNetworkTesting::add_layer(layer::Layer * layer) {
	if (!layers.empty() && layers.back()->get_output_dim() != layer->get_input_dim()) {
		throw std::runtime_error("Input dimension does not match output dimension of previous layer.");
	}
	layers.push_back(layer);
}

const std::vector<layer::Layer *> & NeuralNetworkTesting::get_layers() const {
	return this->layers;
}

Eigen::MatrixXd NeuralNetworkTesting::forward(const Eigen::MatrixXd & input) {
	auto output = input;
	for (const auto & layer: layers) {
		output = layer->forward(output);
	}
	return output;
}

Eigen::MatrixXd NeuralNetworkTesting::backward(const Eigen::MatrixXd & input) {
	auto output = input;
	for (const auto & layer: std::ranges::reverse_view(layers)) {
		output = layer->backward(output);
	}
	return output;
}

void NeuralNetworkTesting::train(const Eigen::MatrixXd & input, const Eigen::MatrixXd & label) {
	// 计算损失
	const auto output = this->forward(input);
	const auto loss = 2.0 * (output - label);
	this->backward(loss);
	for (const auto & layer: std::ranges::reverse_view(layers)) {
	}
}

config::NeuralNetConfig NeuralNetworkTesting::config() const {
	return {
		name,
		layers | std::views::enumerate | std::views::transform([](const auto & pair) {
			auto [index, layer] = pair;
			return "layer_" + std::to_string(index);
		}) | std::ranges::to<std::vector>(),
		input_shape,
		output_shape,
		"loss",
		"optimizer"
	};
}
