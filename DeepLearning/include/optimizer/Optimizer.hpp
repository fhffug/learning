//
// Created by 26326 on 25-8-16.
//

#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include "layer/Layer.hpp"

namespace ml::optimizer {
class DEEPLEARNING_EXPORT Optimizer {
public:
	virtual ~Optimizer() = default;

	virtual void update(Eigen::MatrixXd & params, const Eigen::MatrixXd & grads) = 0;
};
}

#endif //OPTIMIZER_HPP
