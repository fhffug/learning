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
	Layer(int32_t input_dim, int32_t output_dim);

	virtual ~Layer() = default;

protected:
	const int32_t m_input_dim;
	const int32_t m_output_dim;

public:
	/// 前向传播
	virtual Eigen::MatrixXd forward(const Eigen::MatrixXd & input) = 0;

	/// 反向传播
	virtual Eigen::MatrixXd backward(const Eigen::MatrixXd & input) = 0;

	/// 更新参数
	virtual void update(double learning_rate) = 0;

	[[nodiscard]] int32_t get_input_dim() const;

	[[nodiscard]] int32_t get_output_dim() const;

	/// 保存层
	virtual data::LayerData toData() const = 0;

	virtual config::LayerConfig config() const = 0;
};

template<typename T>
concept LayerConcept = std::derived_from<T, Layer>;
DEEPLEARNING_EXPORT Layer * load_layer(const std::string & path);
}
#endif //LAYER_HPP
