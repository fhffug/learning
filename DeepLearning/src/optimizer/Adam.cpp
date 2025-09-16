//
// Created by 26326 on 25-8-21.
//

#include "optimizer/Adam.hpp"

using namespace ml::optimizer;

Adam::Adam(const double_t learning_rate, const double_t beta1, const double_t beta2,
           const double_t epsilon)
	: learning_rate(learning_rate), beta1(beta1), beta2(beta2), epsilon(epsilon) {
}

void Adam::update(Eigen::MatrixXd & params, const Eigen::MatrixXd & grads) {
	t++;
	m_ = beta1 * m_ + (1 - beta1) * grads;
	v_ = beta2 * v_ + (1 - beta2) * grads.array().square().matrix();

	Eigen::MatrixXd m_hat = m_ / (1 - std::pow(beta1, t));
	Eigen::MatrixXd v_hat = v_ / (1 - std::pow(beta2, t));

	// params -= learning_rate * m_hat.array() / (v_hat.array().sqrt() + epsilon);
}
