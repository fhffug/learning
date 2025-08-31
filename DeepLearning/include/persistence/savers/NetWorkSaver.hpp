//
// Created by 26326 on 2025/8/30.
//

#ifndef AICPP_NETWORKSAVER_HPP
#define AICPP_NETWORKSAVER_HPP
#include "ISaver.hpp"
#include "NeuralNetwork.hpp"

namespace ml {
class DEEPLEARNING_EXPORT NetWorkSaver final : public ISaver<NeuralNetwork> {
public:
	explicit NetWorkSaver(std::filesystem::path path)
		: ISaver(std::move(path)) {
	}

private:
	void save_config(const nlohmann::ordered_json & json, std::filesystem::path path) const;

public:
	void save(const NeuralNetwork & net) const override;

	void save(const std::shared_ptr<NeuralNetwork> & net) const override;

	void save(const std::unique_ptr<NeuralNetwork> & net) const override;

	void save(const NeuralNetwork * net) const override;
};
} // ml

#endif //AICPP_NETWORKSAVER_HPP
