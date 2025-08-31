//
// Created by 26326 on 25-8-13.
//

#include "cmath"
#include "function/activation.hpp"

#include <iostream>

namespace ml::act {
Eigen::MatrixXd sigmoid(const Eigen::MatrixXd & x) {
	return (1.0 / (1.0 + (-x).array().exp())).matrix();
}

Eigen::MatrixXd tanh(const Eigen::MatrixXd & x) {
	return x.array().tanh().matrix();
}

Eigen::MatrixXd relu(const Eigen::MatrixXd & x) {
	return x.array().max(0.0).matrix();
}

Eigen::MatrixXd softmax(const Eigen::MatrixXd & x) {
	const auto slided_x = x.colwise() - x.rowwise().maxCoeff(); // 减去每一行最大值
	const auto exp_x = slided_x.array().exp(); // 求exp
	const auto norm_base = exp_x.rowwise().sum(); // 求和
	return exp_x.colwise() / norm_base; // 除以每一行和
}
}

namespace ml::dact {
Eigen::MatrixXd d_sigmoid(const Eigen::MatrixXd & x) {
	Eigen::MatrixXd sig = act::sigmoid(x);
	return (sig.array() * (1.0 - sig.array())).matrix();
}

Eigen::MatrixXd d_tanh(const Eigen::MatrixXd & x) {
	// tanh导数 = 1 - tanh(x)^2
	Eigen::MatrixXd t = act::tanh(x);
	return (1.0 - t.array().square()).matrix();
}


Eigen::MatrixXd d_relu(const Eigen::MatrixXd & x) {
	return (x.array() > 0).cast<double>().matrix();
}

Eigen::MatrixXd d_softmax(const Eigen::MatrixXd & x) {
	// Softmax导数是一个雅可比矩阵
	// 对于向量情况，我们简化处理，返回softmax值*(1-softmax值)
	// 这在与交叉熵损失函数一起使用时是正确的
	Eigen::MatrixXd s = act::softmax(x);
	return (s.array() * (1.0 - s.array())).matrix();
}
}
