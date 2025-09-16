//
// Created by 26326 on 25-8-24.
//

#include "../../include/data/LayerData.hpp"

using namespace ml::data;

LayerData::LayerData(const Eigen::MatrixXd & weight,
                     const Eigen::RowVectorXd & bias,
                     const Eigen::MatrixXd & weight_grad,
                     const Eigen::RowVectorXd & bias_grad)
	: weight(weight), bias(bias), weight_grad(weight_grad), bias_grad(bias_grad) {
}
