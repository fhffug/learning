//
// Created by 26326 on 25-8-4.
//

#ifndef NETWORK_DEBUG_HPP
#define NETWORK_DEBUG_HPP

#include "NeuralNetwork.hpp"
#include "layer/Layer.hpp"

namespace ml {
// Debug
class DEEPLEARNING_EXPORT NeuralNetworkDebug final : public NeuralNetwork {
	std::vector<Eigen::MatrixXd> forward_output;
	std::vector<Eigen::MatrixXd> backward_output;

public:
	using NeuralNetwork::NeuralNetwork;

	void add_layer(layer::Layer * layer) override;

	[[nodiscard]] const std::vector<layer::Layer *> & get_layers() const override;

	[[nodiscard]] Eigen::MatrixXd forward(const Eigen::MatrixXd & input) override;

	/// 反向传播
	Eigen::MatrixXd backward(const Eigen::MatrixXd & input) override;

	void train(const Eigen::MatrixXd & input, const Eigen::MatrixXd & label) override;

	[[nodiscard]] config::NeuralNetConfig config() const override;

	[[nodiscard]] std::string get_type() const override {
		return std::string{"NeuralNetworkDebug"};
	}

	void view();
};
}
#endif //NETWORK_DEBUG_HPP
