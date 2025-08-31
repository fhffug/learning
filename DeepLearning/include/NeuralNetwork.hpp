//
// Created by 26326 on 25-8-26.
//

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "config/NeuralNetConfig.hpp"
#include "layer/Layer.hpp"

namespace ml {
class DEEPLEARNING_EXPORT NeuralNetwork {
public:
	NeuralNetwork() = default;

	NeuralNetwork(std::string name, const std::vector<int32_t> & input_shape,
	              const std::vector<int32_t> & output_shape);

	virtual ~NeuralNetwork() = default;

protected:
	std::string name{"network"};
	std::vector<int32_t> input_shape;
	std::vector<int32_t> output_shape;
	std::vector<std::unique_ptr<layer::Layer>> layers;

public:
	virtual void add_layer(std::unique_ptr<layer::Layer> layer) = 0;

	[[nodiscard]] virtual const std::vector<std::unique_ptr<layer::Layer>> & get_layers() const = 0;

	/// 前向传播
	[[nodiscard]] virtual Eigen::MatrixXd forward(const Eigen::MatrixXd & input) = 0;

	/// 反向传播
	virtual Eigen::MatrixXd backward(const Eigen::MatrixXd & input) = 0;

	virtual void train(const Eigen::MatrixXd & input, const Eigen::MatrixXd & label) = 0;

	[[nodiscard]] virtual config::NeuralNetConfig config() const = 0;
};
}

#endif //NETWORK_HPP
