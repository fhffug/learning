//
// Created by 26326 on 25-8-21.
//

#ifndef ADAM_HPP
#define ADAM_HPP

#include "Eigen/Eigen"
#include "lib_export.h"
#include "Optimizer.hpp"

namespace ml::optimizer {
class DEEPLEARNING_EXPORT Adam final : public Optimizer {
public:
	Adam(double_t learning_rate, double_t beta1, double_t beta2, double_t epsilon);

private:
	double_t learning_rate{0.001};
	double_t beta1{0.9};
	double_t beta2{0.999};
	double_t epsilon{1e-8};
	Eigen::MatrixXd m_ = Eigen::MatrixXd::Zero(0, 0); // 动态调整大小
	Eigen::MatrixXd v_ = Eigen::MatrixXd::Zero(0, 0);
	int32_t t = 0;

public:
	void update(Eigen::MatrixXd & params, const Eigen::MatrixXd & grads) override;
};
}

#endif //ADAM_HPP
