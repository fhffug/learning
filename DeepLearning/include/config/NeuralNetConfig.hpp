//
// Created by 26326 on 25-8-28.
//

#ifndef NEURALNETCONFIG_HPP
#define NEURALNETCONFIG_HPP
#include "IConfig.hpp"

namespace ml::config {
class DEEPLEARNING_EXPORT NeuralNetConfig final : public IConfig {
public:
	NeuralNetConfig() = default;

	NeuralNetConfig(std::string name, const std::vector<std::string> & layers_name,
	                const std::vector<int32_t> & input_shape,
	                const std::vector<int32_t> & output_shape, std::string loss,
	                std::string optimizer);

private:
	std::string name;
	std::vector<std::string> layers_name;
	std::vector<int32_t> input_shape;
	std::vector<int32_t> output_shape;
	std::string loss;
	std::string optimizer;

public:
	void to_json(nlohmann::json & json) const override;

	void from_json(const nlohmann::json & json) override;

	void to_json(nlohmann::ordered_json & json) const override;

	void from_json(const nlohmann::ordered_json & json) override;
};
}

#endif //NEURALNETCONFIG_HPP
