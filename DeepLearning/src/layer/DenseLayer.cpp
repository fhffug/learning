//
// Created by 26326 on 25-8-5.
//

#include "layer/DenseLayer.hpp"

namespace ml::layer {
DenseLayer::DenseLayer(const int32_t input_dim, const int32_t output_dim)
	: Layer(input_dim, output_dim),
	  m_weight(input_dim, output_dim),
	  m_bias(output_dim) {
	assert(input_dim > 0 && "Input size must be positive");
	assert(output_dim > 0 && "Output size must be positive");
	m_weight = Eigen::MatrixXd::Random(input_dim, output_dim) * 0.5;
	m_bias.setZero();
}


Eigen::MatrixXd DenseLayer::forward(const Eigen::MatrixXd & input) {
	// 保存输入用于反向传播
	m_last_input = input;
	// 线性变换: output = input * weight + bias
	const auto linear_output = input * m_weight + m_bias;

	return linear_output;
}

Eigen::MatrixXd DenseLayer::backward(const Eigen::MatrixXd & grad_output) {
	// 计算权重的梯度: input^T * grad_output
	m_weight_grad = m_last_input.transpose() * grad_output;

	// 计算偏置的梯度: 对每个样本的梯度求和
	m_bias_grad = grad_output.colwise().sum();

	// 返回输入的梯度，用于前一层的反向传播
	return grad_output * m_weight.transpose() + m_bias;
}

void DenseLayer::update(const float learning_rate) {
}

data::LayerData DenseLayer::toData() const {
	data::LayerData layer_data;
	layer_data.at("weight") = this->m_weight;
	layer_data.at("bias") = this->m_bias;
	return layer_data;
}

config::LayerConfig DenseLayer::config() const {
	return {m_input_dim, m_output_dim};
}
}

