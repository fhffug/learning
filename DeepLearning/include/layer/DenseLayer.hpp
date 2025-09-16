//
// Created by 26326 on 25-8-5.
//

#ifndef DENSELAYER_HPP
#define DENSELAYER_HPP

#include "lib_export.h"
#include "layer/Layer.hpp"

#include "optimizer/Adam.hpp"

namespace ml::layer {
class DEEPLEARNING_EXPORT DenseLayer final : public Layer {
public:
	~DenseLayer() override {
		delete m_data;
	}

	DenseLayer(Eigen::Index input_dim, Eigen::Index output_dim);

private:
	/// 权重
	Eigen::MatrixXd m_weight;
	/// 偏置
	Eigen::RowVectorXd m_bias;
	/// 权重梯度
	Eigen::MatrixXd m_weight_grad;
	/// 偏置梯度
	Eigen::RowVectorXd m_bias_grad;
	/// 上一次的输入
	Eigen::MatrixXd m_last_input;

	struct DenseLayerData final : data::LayerData {
		DenseLayerData(Eigen::MatrixXd & m_weight,
		               Eigen::RowVectorXd & m_bias,
		               Eigen::MatrixXd & m_weight_grad,
		               Eigen::RowVectorXd & m_bias_grad)
			: m_weight(m_weight),
			  m_bias(m_bias),
			  m_weight_grad(m_weight_grad),
			  m_bias_grad(m_bias_grad) {
		}

		/// 权重
		Eigen::MatrixXd & m_weight;
		/// 偏置
		Eigen::RowVectorXd & m_bias;
		/// 权重梯度
		Eigen::MatrixXd & m_weight_grad;
		/// 偏置梯度
		Eigen::RowVectorXd & m_bias_grad;
	};

	DenseLayerData * m_data = new DenseLayerData{m_weight, m_bias, m_weight_grad, m_bias_grad};

public:
	Eigen::MatrixXd forward(const Eigen::MatrixXd & input) override;

	Eigen::MatrixXd backward(const Eigen::MatrixXd & grad_output) override;

	[[nodiscard]] data::LayerData * data() const override;

	[[nodiscard]] config::LayerConfig * config() const override;
};
}


#endif //DENSELAYER_HPP
