//
// Created by 26326 on 2025/8/30.
//

#ifndef AICPP_NETWORKSAVER_HPP
#define AICPP_NETWORKSAVER_HPP
#include "ISaver.hpp"
#include "NeuralNetwork.hpp"

namespace ml::saver {
static const std::filesystem::path layer_conf_path = "layers_config";
static const std::filesystem::path layer_bin_path = "layers_bin";

class DEEPLEARNING_EXPORT NetWorkSaver final : public ISaver<NeuralNetwork> {
public:
	explicit NetWorkSaver(std::filesystem::path path)
		: ISaver(std::move(path)) {
	}

	[[nodiscard]] bool save_config(const nlohmann::ordered_json & json, const std::filesystem::path & path) const;

	[[nodiscard]] bool save_bin(const data::LayerData & bin, const std::filesystem::path & path) const;

	void save_layers(const std::vector<std::unique_ptr<layer::Layer>> & layers) const;

	void save(const NeuralNetwork & net) const override;

	void save(const std::shared_ptr<NeuralNetwork> & net) const override;

	void save(const std::unique_ptr<NeuralNetwork> & net) const override;

	void save(const NeuralNetwork * net) const override;
};
} // ml

#endif //AICPP_NETWORKSAVER_HPP
