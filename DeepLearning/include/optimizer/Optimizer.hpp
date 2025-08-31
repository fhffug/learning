//
// Created by 26326 on 25-8-16.
//

#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include "lib_export.h"

namespace ml::optimizer {
class DEEPLEARNING_EXPORT Optimizer {
public:
	virtual ~Optimizer() = default;

	virtual void update(float learning_rate) = 0;
};
}

#endif //OPTIMIZER_HPP
