//
// Created by 26326 on 25-8-26.
//

#ifndef LAYERCONFIG_HPP
#define LAYERCONFIG_HPP

#include "IConfig.hpp"

namespace ml::config {
class DEEPLEARNING_EXPORT LayerConfig final : public IConfig {
	std::string type;
	Eigen::Index input_dim = 0;
	Eigen::Index output_dim = 0;

public:
	LayerConfig() = default;

	LayerConfig(Eigen::Index input_dim, Eigen::Index output_dim);

	void to_json(nlohmann::json & json) const override;

	void from_json(const nlohmann::json & json) override;

	void to_json(nlohmann::ordered_json & json) const override;

	void from_json(const nlohmann::ordered_json & json) override;

	[[nodiscard]] const std::string & get_type() const { return type; }

	[[nodiscard]] Eigen::Index get_input_dim() const { return input_dim; }

	[[nodiscard]] Eigen::Index get_output_dim() const { return output_dim; }
};
}

#endif //LAYERCONFIG_HPP
