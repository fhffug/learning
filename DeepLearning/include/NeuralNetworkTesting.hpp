//
// Created by 26326 on 25-8-26.
//

#ifndef NETWORK_TESTING_HPP
#define NETWORK_TESTING_HPP

#include "NeuralNetwork.hpp"
#include "config/NeuralNetConfig.hpp"

namespace ml {
// Testing
class DEEPLEARNING_EXPORT NeuralNetworkTesting final : public NeuralNetwork {
public:
	NeuralNetworkTesting();

	NeuralNetworkTesting(std::string name, const std::vector<int32_t> & input_shape,
	                     const std::vector<int32_t> & output_shape);

	void add_layer(std::unique_ptr<layer::Layer> layer) override;

	[[nodiscard]] const std::vector<std::unique_ptr<layer::Layer>> & get_layers() const override;

	/// 前向传播
	[[nodiscard]] Eigen::MatrixXd forward(const Eigen::MatrixXd & input) override;

	/// 反向传播
	Eigen::MatrixXd backward(const Eigen::MatrixXd & input) override;

	void train(const Eigen::MatrixXd & input, const Eigen::MatrixXd & label) override;

	[[nodiscard]] config::NeuralNetConfig config() const override;

	[[nodiscard]] std::string get_type() const override {
		return "NeuralNetworkTesting";
	}
};
}

#endif //NETWORK_TESTING_HPP
