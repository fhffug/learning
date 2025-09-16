//
// Created by 26326 on 25-8-26.
//

#include "config/LayerConfig.hpp"

using namespace ml::config;

LayerConfig::LayerConfig(const Eigen::Index input_dim, const Eigen::Index output_dim)
	: input_dim(input_dim), output_dim(output_dim) {
}

void LayerConfig::to_json(nlohmann::json & json) const {
	json["input_dim"] = input_dim;
	json["output_dim"] = output_dim;
}

void LayerConfig::from_json(const nlohmann::json & json) {
	json.at("input_dim").get_to<Eigen::Index>(input_dim);
	json.at("output_dim").get_to<Eigen::Index>(output_dim);
}

void LayerConfig::to_json(nlohmann::ordered_json & json) const {
	json["input_dim"] = input_dim;
	json["output_dim"] = output_dim;
}

void LayerConfig::from_json(const nlohmann::ordered_json & json) {
	json.at("input_dim").get_to<Eigen::Index>(input_dim);
	json.at("output_dim").get_to<Eigen::Index>(output_dim);
}
