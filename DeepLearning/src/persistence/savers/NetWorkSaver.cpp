//
// Created by 26326 on 2025/8/30.
//

#include "persistence/savers/NetWorkSaver.hpp"

using namespace ml::saver;

bool NetWorkSaver::save_config(const nlohmann::ordered_json & json, const std::filesystem::path & path) const {
	const auto file_path = this->path / path;
	// 如果文件存在，并且是文件，则创建备份
	if (std::filesystem::exists(file_path) && std::filesystem::is_regular_file(file_path)) {
		std::filesystem::path backup_path = file_path;
		backup_path += ".bak";
		std::filesystem::copy_file(file_path, backup_path, std::filesystem::copy_options::overwrite_existing);
	}
	std::fstream file(file_path, std::ios::out);
	if (!file.is_open()) { return false; }
	file << json;
	file.close();
	return true;
}

bool NetWorkSaver::save_bin(const data::LayerData & bin, const std::filesystem::path & path) const {
	const auto file_path = this->path / path;
	// 如果文件存在，并且是文件，则创建备份
	if (std::filesystem::exists(file_path) && std::filesystem::is_regular_file(file_path)) {
		std::filesystem::path backup_path = file_path;
		backup_path += ".bak";
		std::filesystem::copy_file(file_path, backup_path, std::filesystem::copy_options::overwrite_existing);
	}
	std::fstream out(file_path, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!out.is_open()) { return false; }

	// 写入矩阵数量
	size_t num_matrices = bin.items().size();
	out.write(reinterpret_cast<char *>(&num_matrices), sizeof(size_t));
	for (const auto & item: bin.items()) {
		// 写入矩阵名称
		size_t name_len = item.key.size();
		out.write(reinterpret_cast<char *>(&name_len), sizeof(size_t));
		out.write(item.key.c_str(), static_cast<std::streamsize>(name_len));
		// 写入每个矩阵
		Eigen::Index rows = item.rows;
		Eigen::Index cols = item.cols;
		out.write(reinterpret_cast<char *>(&rows), sizeof(Eigen::Index));
		out.write(reinterpret_cast<char *>(&cols), sizeof(Eigen::Index));
		out.write(item.data, static_cast<std::streamsize>(cols * rows * sizeof(double_t)));
	}
	out.close();
	return true;
}

void NetWorkSaver::save_layers(const std::vector<std::unique_ptr<layer::Layer>> & layers) const {
	if (!std::filesystem::exists(path / layer_conf_path) || !std::filesystem::is_directory(path / layer_conf_path))
		std::filesystem::create_directories(path / layer_conf_path);
	if (!std::filesystem::exists(path / layer_bin_path) || !std::filesystem::is_directory(path / layer_bin_path))
		std::filesystem::create_directories(path / layer_bin_path);
	for (const auto & [index,layer]: std::ranges::views::enumerate(layers)) {
		// config
		if (const bool success = save_config(layer->config(),
		                                     layer_conf_path / ("layer_" + std::to_string(index) + ".json"));
			!success) { std::cerr << "save layer " << index << " config failed" << std::endl; }
		// bin
		if (const bool success = save_bin(layer->data(), layer_bin_path / ("layer_" + std::to_string(index) + ".bin"));
			!success) { std::cerr << "save layer " << index << " bin failed" << std::endl; }
	}
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
		std::filesystem::create_directories(path);
	}
	if (const bool success = save_config(net->config(), "net_config.json"); !success) {
		std::cerr << "save net config failed" << std::endl;
	}
	save_layers(net->get_layers());
}
