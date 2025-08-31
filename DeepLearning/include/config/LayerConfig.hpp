//
// Created by 26326 on 25-8-26.
//

#ifndef LAYERCONFIG_HPP
#define LAYERCONFIG_HPP

#include "IConfig.hpp"

namespace ml::config {
class DEEPLEARNING_EXPORT LayerConfig final : public IConfig {
public:
	LayerConfig() = default;

	LayerConfig(int32_t input_dim, int32_t output_dim);

private:
	int32_t input_dim = 0;
	int32_t output_dim = 0;

public:
	[[nodiscard]] int32_t get_input_dim() const;

	[[nodiscard]] int32_t get_output_dim() const;

	void to_json(nlohmann::json & json) const override;

	void from_json(const nlohmann::json & json) override;

	void to_json(nlohmann::ordered_json & json) const override;

	void from_json(const nlohmann::ordered_json & json) override;
};
}

#endif //LAYERCONFIG_HPP
