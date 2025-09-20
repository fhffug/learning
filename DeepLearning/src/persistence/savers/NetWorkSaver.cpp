//
// Created by 26326 on 2025/8/30.
//

#include "persistence/savers/NetWorkSaver.hpp"

using namespace ml::saver;

bool NetWorkSaver::save_network_config(const nlohmann::ordered_json & json) const {
	// 如果文件存在，并且是文件，则创建备份
	if (std::filesystem::exists(network_conf_path) && std::filesystem::is_regular_file(network_conf_path)) {
		std::filesystem::path backup_path = network_conf_path;
		backup_path += ".bak";
		std::filesystem::copy_file(network_conf_path, backup_path, std::filesystem::copy_options::overwrite_existing);
	}
	std::fstream file(network_conf_path, std::ios::out);
	if (!file.is_open()) { return false; }
	file << json;
	file.close();
	return true;
}

bool NetWorkSaver::save_layer_config(const nlohmann::ordered_json & json, size_t index) const {
	const auto layer_path = layer_conf_path / ("layer_" + std::to_string(index) + ".json");
	// 如果文件存在，并且是文件，则创建备份
	if (std::filesystem::exists(layer_path) && std::filesystem::is_regular_file(layer_path)) {
		std::filesystem::path backup_path = layer_path;
		backup_path += ".bak";
		std::filesystem::copy_file(layer_path, backup_path, std::filesystem::copy_options::overwrite_existing);
	}
	std::fstream file{layer_path, std::ios::out};
	if (!file.is_open()) { return false; }
	file << json;
	file.close();
	return true;
}

bool NetWorkSaver::save_layer_bin(const data::LayerData * bin, size_t index) const {
	const auto bin_path = layer_bin_path / ("layer_" + std::to_string(index) + ".bin");
	// 如果文件存在，并且是文件，则创建备份
	if (std::filesystem::exists(bin_path) && std::filesystem::is_regular_file(bin_path)) {
		std::filesystem::path backup_path = bin_path;
		backup_path += ".bak";
		std::filesystem::copy_file(bin_path, backup_path, std::filesystem::copy_options::overwrite_existing);
	}
	std::fstream out{bin_path, std::ios::out | std::ios::binary | std::ios::trunc};
	if (!out.is_open()) { return false; }

	// 写入矩阵数量
	size_t num_matrices = bin->items().size();
	out.write(reinterpret_cast<char *>(&num_matrices), sizeof(size_t));
	for (const auto & [name, rows, cols, data]: bin->items()) {
		// 写入矩阵名称
		size_t name_len = name.size();
		out.write(reinterpret_cast<char *>(&name_len), sizeof(size_t));
		out.write(name.c_str(), static_cast<std::streamsize>(name_len));
		// 写入每个矩阵
		out.write(reinterpret_cast<const char *>(&rows), sizeof(Eigen::Index));
		out.write(reinterpret_cast<const char *>(&cols), sizeof(Eigen::Index));
		out.write(data, static_cast<std::streamsize>(cols * rows * sizeof(double_t)));
	}
	out.close();
	return true;
}

void NetWorkSaver::save(const NeuralNetwork * net) const {
	if (!std::filesystem::exists(m_path) || !std::filesystem::is_directory(m_path)) {
		std::filesystem::create_directories(m_path);
	}
	if (!std::filesystem::exists(layer_conf_path) || !std::filesystem::is_directory(layer_conf_path)) {
		std::filesystem::create_directories(layer_conf_path);
	}
	if (!std::filesystem::exists(layer_bin_path) || !std::filesystem::is_directory(layer_bin_path)) {
		std::filesystem::create_directories(layer_bin_path);
	}
	if (!save_network_config(net->config())) {
		std::cerr << "save net config failed" << std::endl;
	}
	for (const auto & [index,layer]: std::views::enumerate(net->get_layers())) {
		if (!save_network_config(*layer->config())) {
			std::cerr << "save layer " << index << " config failed" << std::endl;
		}
		if (!save_layer_bin(layer->data(), index)) {
			std::cerr << "save layer " << index << " bin failed" << std::endl;
		}
	}
}
