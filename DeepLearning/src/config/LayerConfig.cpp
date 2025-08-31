//
// Created by 26326 on 25-8-26.
//

#include "config/LayerConfig.hpp"

using namespace ml::config;

LayerConfig::LayerConfig(const int32_t input_dim, const int32_t output_dim)
	: input_dim(input_dim), output_dim(output_dim) {
}

int32_t LayerConfig::get_input_dim() const {
	return input_dim;
}

int32_t LayerConfig::get_output_dim() const {
	return output_dim;
}

void LayerConfig::to_json(nlohmann::json & json) const {
	json["input_dim"] = input_dim;
	json["output_dim"] = output_dim;
}

void LayerConfig::from_json(const nlohmann::json & json) {
	json.at("input_dim").get_to<int32_t>(input_dim);
	json.at("output_dim").get_to<int32_t>(output_dim);
}

void LayerConfig::to_json(nlohmann::ordered_json & json) const {
	json["input_dim"] = input_dim;
	json["output_dim"] = output_dim;
}

void LayerConfig::from_json(const nlohmann::ordered_json & json) {
	json.at("input_dim").get_to<int32_t>(input_dim);
	json.at("output_dim").get_to<int32_t>(output_dim);
}
