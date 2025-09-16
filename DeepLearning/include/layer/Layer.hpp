//
// Created by 26326 on 25-8-5.
//

#ifndef LAYER_HPP
#define LAYER_HPP

#include "lib_export.h"

#include "config/LayerConfig.hpp"
#include "data/LayerData.hpp"

namespace ml::layer {
class DEEPLEARNING_EXPORT Layer {
public:
	Layer(Eigen::Index input_dim, Eigen::Index output_dim) : m_input_dim(input_dim), m_output_dim(output_dim) {
	}

	virtual ~Layer() = default;

protected:
	const Eigen::Index m_input_dim;
	const Eigen::Index m_output_dim;

public:
	/// 前向传播
	virtual Eigen::MatrixXd forward(const Eigen::MatrixXd & input) = 0;

	/// 反向传播
	virtual Eigen::MatrixXd backward(const Eigen::MatrixXd & input) = 0;

	[[nodiscard]] Eigen::Index get_input_dim() const { return m_input_dim; }

	[[nodiscard]] Eigen::Index get_output_dim() const { return m_output_dim; }

	[[nodiscard]] virtual data::LayerData * data() const = 0;

	[[nodiscard]] virtual config::LayerConfig * config() const = 0;
};
}
#endif //LAYER_HPP
