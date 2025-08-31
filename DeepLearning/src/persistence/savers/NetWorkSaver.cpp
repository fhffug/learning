//
// Created by 26326 on 2025/8/30.
//

#include "persistence/savers/NetWorkSaver.hpp"

using namespace ml;

void NetWorkSaver::save_config(const nlohmann::ordered_json & json, std::filesystem::path path) const {
	const auto file_path = this->path / path;
	// 如果文件存在，并且是文件，则创建备份
	if (std::filesystem::exists(file_path) && std::filesystem::is_regular_file(file_path)) {
		std::filesystem::path backup_path = file_path;
		backup_path += ".bak";
		std::filesystem::copy_file(file_path, backup_path, std::filesystem::copy_options::overwrite_existing);
	}
	std::fstream file(file_path, std::ios::out);
	const nlohmann::ordered_json config_json = file_path;
	file << config_json;
	file.close();
}

void NetWorkSaver::save(const NeuralNetwork & net) const {
	save(&net);
}

void NetWorkSaver::save(const std::shared_ptr<NeuralNetwork> & net) const {
	save(net.get());
}

void NetWorkSaver::save(const std::unique_ptr<NeuralNetwork> & net) const {
	save(net.get());
}

void NetWorkSaver::save(const NeuralNetwork * net) const {
	if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
		std::filesystem::create_directory(path);
		std::filesystem::create_directory(path / "layer");
	}
	save_config(net->config(), "net_config.json");
	const std::filesystem::path layer_path{"layers"};
	for (const auto & [index,layer]: std::ranges::views::enumerate(net->get_layers())) {
		save_config(layer->config(), layer_path / (std::to_string(index) + ".json"));
	}
}
