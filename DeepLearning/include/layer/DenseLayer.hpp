//
// Created by 26326 on 25-8-5.
//

#ifndef DENSELAYER_HPP
#define DENSELAYER_HPP

#include "lib_export.h"
#include "data/LayerData.hpp"
#include "layer/Layer.hpp"

namespace ml::layer {
class DEEPLEARNING_EXPORT DenseLayer final : public Layer {
public:
	explicit DenseLayer(int32_t input_dim, int32_t output_dim);

private:
	/// 权重
	Eigen::MatrixXd m_weight;
	/// 偏置
	Eigen::RowVectorXd m_bias;
	Eigen::MatrixXd m_weight_grad;
	Eigen::RowVectorXd m_bias_grad;

	/// 上一次的输入
	Eigen::MatrixXd m_last_input;

public:
	Eigen::MatrixXd forward(const Eigen::MatrixXd & input) override;

	Eigen::MatrixXd backward(const Eigen::MatrixXd & grad_output) override;

	void update(double learning_rate) override;

	[[nodiscard]] data::LayerData toData() const override;

	[[nodiscard]] config::LayerConfig config() const override;
};
}


#endif //DENSELAYER_HPP
