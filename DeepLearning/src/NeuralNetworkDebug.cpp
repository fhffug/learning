//
// Created by 26326 on 25-8-4.
//

#include "NeuralNetworkDebug.hpp"

// Debug
using namespace ml;

void NeuralNetworkDebug::add_layer(layer::Layer * layer) {
	if (!layers.empty() && layers.back()->get_output_dim() != layer->get_input_dim()) {
		throw std::runtime_error("Input dimension does not match output dimension of previous layer.");
	}
	layers.push_back(layer);
}

const std::vector<layer::Layer *> & NeuralNetworkDebug::get_layers() const {
	return this->layers;
}

Eigen::MatrixXd NeuralNetworkDebug::forward(const Eigen::MatrixXd & input) {
	forward_output.clear();
	auto output = input;
	forward_output.push_back(output);
	for (const auto & layer: layers) {
		output = layer->forward(output);
		forward_output.push_back(output);
	}
	return std::move(forward_output.back());
}

Eigen::MatrixXd NeuralNetworkDebug::backward(const Eigen::MatrixXd & input) {
	backward_output.clear();
	auto output = input;
	backward_output.push_back(output);
	for (const auto & layer: std::ranges::reverse_view(layers)) {
		output = layer->backward(output);
		backward_output.push_back(output);
	}
	return output;
}

void NeuralNetworkDebug::train(const Eigen::MatrixXd & input, const Eigen::MatrixXd & label) {
	const auto & output = this->forward(input);
	// 计算损失
	const auto & loss = label - output;
	this->backward(loss);
	for (const auto & layer: std::ranges::reverse_view(layers)) {
	}
}

config::NeuralNetConfig NeuralNetworkDebug::config() const {
	return {};
}

void NeuralNetworkDebug::view() {
}


