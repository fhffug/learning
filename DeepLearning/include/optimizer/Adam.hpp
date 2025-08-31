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
	Adam(Eigen::MatrixXd &, Eigen::MatrixXd &);

private:
	/// 权重
	Eigen::MatrixXd & m_weight;
	/// 偏置
	Eigen::MatrixXd & m_bias;

public:
	void update(float learning_rate) override;
};
}

#endif //ADAM_HPP
