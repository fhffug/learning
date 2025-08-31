//
// Created by 26326 on 25-8-21.
//

#include "optimizer/Adam.hpp"

ml::optimizer::Adam::Adam(Eigen::MatrixXd & weight, Eigen::MatrixXd & bias)
	: m_weight(weight), m_bias(bias) {
}

void ml::optimizer::Adam::update(const float learning_rate) {
	const auto m_weight_gradient = m_weight;
	m_weight -= learning_rate * m_weight_gradient;
	const auto m_bias_gradient = m_bias;
	m_bias -= learning_rate * m_bias_gradient;
}
