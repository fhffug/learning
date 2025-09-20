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

NeuralNetwork * NetWorkLoader::load() throw (std::invalid_argument) {
	if (!std::filesystem::exists(m_path) || !std::filesystem::is_directory(m_path)) {
		throw std::invalid_argument("main directory not exists");
	}
	if (!std::filesystem::exists(network_conf_path) || !std::filesystem::is_regular_file(network_conf_path)) {
		throw std::invalid_argument("network config not exists");
	}
	if (!std::filesystem::exists(layer_conf_path) || !std::filesystem::is_directory(layer_conf_path)) {
		throw std::invalid_argument("layer config directory not exists");
	}
	if (!std::filesystem::exists(layer_bin_path) || !std::filesystem::is_directory(layer_bin_path)) {
		throw std::invalid_argument("layer bin directory not exists");
	}
	auto neural_network = load_network(network_conf_path);
	if (neural_network == nullptr) { throw std::invalid_argument("network type not exists"); }
	for (auto & item: std::filesystem::directory_iterator(layer_conf_path)) {
		if (!item.is_regular_file()) { break; }
		neural_network->add_layer(load_layer(item.path()));
	}
	return neural_network;
}

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


NeuralNetwork * NetWorkLoader::load_network(const std::filesystem::path & path) {
	const config::NeuralNetConfig conf = nlohmann::ordered_json::parse(std::ifstream(path));
	switch (conf.get_type()) {
		case "Debug": return new NeuralNetworkDebug{conf.get_name(), conf.get_input_shape(), conf.get_output_shape()};
		case "Test": return new NeuralNetworkTesting{conf.get_name(), conf.get_input_shape(), conf.get_output_shape()};
		default: return nullptr;
	}
}

layer::Layer * NetWorkLoader::load_layer(const std::filesystem::path & path) {
	nlohmann::ordered_json json = nlohmann::ordered_json::parse(std::ifstream(path));
	switch (json.at("type").get<std::string>()) {
		default: return new layer::DenseLayer{
				json.at("input_dim").get<Eigen::Index>(),
				json.at("output_dim").get<Eigen::Index>()
			};
	}
	return new layer::DenseLayer{1, 2};
}
