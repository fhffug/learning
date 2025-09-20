//
// Created by 26326 on 2025/8/30.
//

#ifndef AICPP_NETWORKSAVER_HPP
#define AICPP_NETWORKSAVER_HPP
#include "ISaver.hpp"
#include "NeuralNetwork.hpp"

namespace ml::saver {
class DEEPLEARNING_EXPORT NetWorkSaver final : public ISaver<NeuralNetwork> {
public:
	using ISaver::ISaver;
	const std::filesystem::path layer_conf_path = m_path / "layers_config";
	const std::filesystem::path layer_bin_path = m_path / "layers_bin";
	const std::filesystem::path network_conf_path = m_path / "network_config.json";

	[[nodiscard]] bool save_network_config(const nlohmann::ordered_json & json) const;

	[[nodiscard]] bool save_layer_config(const nlohmann::ordered_json & json, size_t index) const;

	[[nodiscard]] bool save_layer_bin(const data::LayerData * bin, size_t index) const;

	void save(const NeuralNetwork * net) const override;
};
} // ml

#endif //AICPP_NETWORKSAVER_HPP
