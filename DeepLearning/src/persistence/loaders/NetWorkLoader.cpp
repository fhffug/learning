//
// Created by 26326 on 2025/8/30.
//

#include "persistence/loaders/NetWorkLoader.hpp"

#include "NeuralNetworkDebug.hpp"
#include "NeuralNetworkTesting.hpp"

#include "layer/DenseLayer.hpp"

#include "persistence/savers/NetWorkSaver.hpp"

using namespace ml;
using namespace ml::loader;

bool NetWorkLoader::test() {
	std::fstream in(R"(E:\models\layers_bin\0.bin)", std::ios::in | std::ios::binary);
	if (!in.is_open()) { return false; }
	std::vector<Eigen::MatrixXd> matrices;
	// 读取矩阵数量
	size_t num_matrices = 0;
	in.read(reinterpret_cast<char *>(&num_matrices), sizeof(size_t));
	std::vector<std::string> name_list;
	name_list.resize(num_matrices);
	matrices.resize(num_matrices);
	for (size_t i = 0; i < num_matrices; ++i) {
		// 读取矩阵名称
		size_t name_len = 0;
		in.read(reinterpret_cast<char *>(&name_len), sizeof(size_t));
		name_list[i].resize(name_len);
		in.read(&name_list[i][0], static_cast<std::streamsize>(name_len));

		// 读取矩阵数据
		Eigen::Index rows = 0;
		Eigen::Index cols = 0;
		in.read(reinterpret_cast<char *>(&rows), sizeof(Eigen::Index));
		in.read(reinterpret_cast<char *>(&cols), sizeof(Eigen::Index));

		matrices[i].resize(rows, cols);
		Eigen::MatrixXd matrix;
		in.read(reinterpret_cast<char *>(matrix.data()), static_cast<std::streamsize>(rows * cols * sizeof(double_t)));
	}
	for (size_t i = 0; i < num_matrices; ++i) {
		std::cout << name_list[i] << ": " << std::endl;
		std::cout << matrices[i] << std::endl;
	}
	in.close();
	return true;
}

NeuralNetwork * NetWorkLoader::select_network(const config::NeuralNetConfig & conf) {
	switch (conf.get_type()) {
		case "NeuralNetwork":
			return new NeuralNetworkTesting{conf.get_name(), conf.get_input_shape(), conf.get_output_shape()};
		case "NeuralNetworkDebug":
			return new NeuralNetworkDebug{conf.get_name(), conf.get_input_shape(), conf.get_output_shape()};
		default: return nullptr;
	}
}

layer::Layer * NetWorkLoader::select_layer(const config::LayerConfig & conf) {
	switch (conf.get_type()) {
		case "NeuralNetwork":
			return new layer::DenseLayer{conf.get_input_dim(), conf.get_output_dim()};
		default: return nullptr;
	}
}

NeuralNetwork * NetWorkLoader::load() throw (std::invalid_argument) {
	if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path))
		throw std::invalid_argument("Invalid path");

	const std::filesystem::path config_path = path / "config.json";
	if (!std::filesystem::exists(config_path) || !std::filesystem::is_regular_file(config_path))
		throw std::invalid_argument("Invalid config path");

	const nlohmann::ordered_json json = nlohmann::ordered_json::parse(std::ifstream(config_path));
	NeuralNetwork * net = select_network(json);
	if (!net) throw std::invalid_argument("Invalid network type");

	for (const std::filesystem::path layers_path = path / saver::layer_conf_path;
	     const auto & entry: std::filesystem::directory_iterator(layers_path)) {
		if (!std::filesystem::is_regular_file(entry) || entry.path().extension() != ".json")
			continue;
		nlohmann::ordered_json layer_json = nlohmann::ordered_json::parse(std::ifstream(entry.path()));
		layer::Layer * layer = select_layer(json);
		if (!layer) throw std::invalid_argument("Invalid layer type");
		net->add_layer(std::unique_ptr<layer::Layer>(layer));
	}
	for (const std::filesystem::path layers_path = path / saver::layer_bin_path;
	     const auto & entry: std::filesystem::directory_iterator(layers_path)) {
		if (!std::filesystem::is_regular_file(entry) || entry.path().extension() != ".bin")
			continue;
		std::fstream in(entry.path(), std::ios::in | std::ios::binary);
		if (!in.is_open()) throw std::invalid_argument("Invalid layer data path");
		std::vector<Eigen::MatrixXd> matrices;
		size_t num_matrices = 0;
		in.read(reinterpret_cast<char *>(&num_matrices), sizeof(size_t));
		matrices.resize(num_matrices);
		for (size_t i = 0; i < num_matrices; ++i) {
			size_t name_len = 0;
			in.read(reinterpret_cast<char *>(&name_len), sizeof(size_t));
			std::string name;
			name.resize(name_len);
			in.read(&name[0], static_cast<std::streamsize>(name_len));

			Eigen::Index rows = 0;
			Eigen::Index cols = 0;
			in.read(reinterpret_cast<char *>(&rows), sizeof(Eigen::Index));
			in.read(reinterpret_cast<char *>(&cols), sizeof(Eigen::Index));
			matrices[i].resize(rows, cols);
		}
	}
	return net;
}

std::shared_ptr<NeuralNetwork> NetWorkLoader::load_shared() throw (std::invalid_argument) {
	return std::shared_ptr<NeuralNetwork>(load());
}

std::unique_ptr<NeuralNetwork> NetWorkLoader::load_unique() throw (std::invalid_argument) {
	return std::unique_ptr<NeuralNetwork>(load());
}
