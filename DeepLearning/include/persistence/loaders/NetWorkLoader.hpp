//
// Created by 26326 on 2025/8/30.
//

#ifndef AICPP_NETWORKLOADER_HPP
#define AICPP_NETWORKLOADER_HPP
#include "ILoader.hpp"
#include "NeuralNetwork.hpp"

namespace ml {
class DEEPLEARNING_EXPORT NetWorkLoader final : public ILoader<NeuralNetwork> {
public:
	explicit NetWorkLoader(const std::filesystem::path & path) : ILoader(path) {
	}

	NeuralNetwork * load() override;

	std::shared_ptr<NeuralNetwork> load_shared() override;

	std::unique_ptr<NeuralNetwork> load_unique() override;
};
} // ml

#endif //AICPP_NETWORKLOADER_HPP
