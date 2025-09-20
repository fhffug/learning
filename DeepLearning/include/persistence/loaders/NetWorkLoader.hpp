//
// Created by 26326 on 2025/8/30.
//

#ifndef AICPP_NETWORKLOADER_HPP
#define AICPP_NETWORKLOADER_HPP
#include "ILoader.hpp"
#include "NeuralNetwork.hpp"

namespace ml::loader {
class DEEPLEARNING_EXPORT NetWorkLoader final : public ILoader<NeuralNetwork> {
public:
	using ILoader::ILoader;
	const std::filesystem::path layer_conf_path = m_path / "layers_config";
	const std::filesystem::path layer_bin_path = m_path / "layers_bin";
	const std::filesystem::path network_conf_path = m_path / "network_config.json";

	NeuralNetwork * load() override;

	static bool test();

	static NeuralNetwork * load_network(const std::filesystem::path & path);

	static layer::Layer * load_layer(const std::filesystem::path & path);
};
} // ml

#endif //AICPP_NETWORKLOADER_HPP
