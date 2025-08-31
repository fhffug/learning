//
// Created by 26326 on 25-8-28.
//

#include <utility>

#include "config/NeuralNetConfig.hpp"

using namespace ml::config;

NeuralNetConfig::NeuralNetConfig(std::string name,
                                 const std::vector<std::string> & layers_name,
                                 const std::vector<int32_t> & input_shape,
                                 const std::vector<int32_t> & output_shape,
                                 std::string loss,
                                 std::string optimizer)
	: name(std::move(name)), layers_name(layers_name), input_shape(input_shape), output_shape(output_shape),
	  loss(std::move(loss)),
	  optimizer(std::move(optimizer)) {
}

void NeuralNetConfig::to_json(nlohmann::json & json) const {
	json["name"] = name;
	json["layers"] = layers_name;
	json["input_dim"] = input_shape;
	json["output_dim"] = output_shape;
	json["loss"] = loss;
	json["optimizer"] = optimizer;
}

void NeuralNetConfig::from_json(const nlohmann::json & json) {
	json.at("name").get_to(name);
	json.at("layers").get_to(layers_name);
	json.at("input_dim").get_to(input_shape);
	json.at("output_dim").get_to(output_shape);
	json.at("loss").get_to(loss);
	json.at("optimizer").get_to(optimizer);
}

void NeuralNetConfig::to_json(nlohmann::ordered_json & json) const {
	json["name"] = name;
	json["layers"] = layers_name;
	json["input_dim"] = input_shape;
	json["output_dim"] = output_shape;
	json["loss"] = loss;
	json["optimizer"] = optimizer;
}

void NeuralNetConfig::from_json(const nlohmann::ordered_json & json) {
	json.at("name").get_to(name);
	json.at("layers").get_to(layers_name);
	json.at("input_dim").get_to(input_shape);
	json.at("output_dim").get_to(output_shape);
	json.at("loss").get_to(loss);
	json.at("optimizer").get_to(optimizer);
}
