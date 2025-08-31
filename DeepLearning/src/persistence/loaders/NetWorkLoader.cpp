//
// Created by 26326 on 2025/8/30.
//

#include "persistence/loaders/NetWorkLoader.hpp"

using namespace ml;

NeuralNetwork * NetWorkLoader::load() {
	if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
		return nullptr;
	}
	const std::filesystem::path config_path = path / "config.json";
	if (!std::filesystem::exists(config_path) || !std::filesystem::is_regular_file(config_path)) {
		return nullptr;
	}
	const nlohmann::ordered_json json = nlohmann::ordered_json::parse(std::ifstream(config_path));
	config::NeuralNetConfig config = json;
	return nullptr;
}

std::shared_ptr<NeuralNetwork> NetWorkLoader::load_shared() {
	return nullptr;
}

std::unique_ptr<NeuralNetwork> NetWorkLoader::load_unique() {
	return nullptr;
}
