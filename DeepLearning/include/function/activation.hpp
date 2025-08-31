//
// Created by 26326 on 25-8-13.
//

#ifndef ACTIVATION_HPP
#define ACTIVATION_HPP

#include "lib_export.h"
#include "Eigen/Eigen"

namespace ml {
/// 激活函数
using Act = Eigen::MatrixXd (*)(const Eigen::MatrixXd &);
/// 激活函数导数
using DAct = Eigen::MatrixXd (*)(const Eigen::MatrixXd &);
}

namespace ml::act {
DEEPLEARNING_EXPORT Eigen::MatrixXd sigmoid(const Eigen::MatrixXd & x);

DEEPLEARNING_EXPORT Eigen::MatrixXd tanh(const Eigen::MatrixXd & x);

DEEPLEARNING_EXPORT Eigen::MatrixXd relu(const Eigen::MatrixXd & x);

DEEPLEARNING_EXPORT Eigen::MatrixXd softmax(const Eigen::MatrixXd & x);
}

namespace ml::dact {
DEEPLEARNING_EXPORT Eigen::MatrixXd d_sigmoid(const Eigen::MatrixXd & x);

DEEPLEARNING_EXPORT Eigen::MatrixXd d_tanh(const Eigen::MatrixXd & x);

DEEPLEARNING_EXPORT Eigen::MatrixXd d_relu(const Eigen::MatrixXd & x);

DEEPLEARNING_EXPORT Eigen::MatrixXd d_softmax(const Eigen::MatrixXd & x);
}

#endif //ACTIVATION_HPP
