//
// Created by 26326 on 25-8-24.
//

#ifndef LAYERDATA_HPP
#define LAYERDATA_HPP

#include "IData.hpp"


namespace ml::data {
class DEEPLEARNING_EXPORT LayerData : public IData {
public:
	struct DEEPLEARNING_EXPORT Item {
		std::string name;
		Eigen::Index rows{};
		Eigen::Index cols{};
		char * data{};

		Item(std::string name, const Eigen::Index rows, const Eigen::Index cols, char * data)
			: name(std::move(name)), rows(rows), cols(cols), data(data) {
		}

		Item() = default;
	};

	[[nodiscard]] virtual std::vector<Item> items() const = 0;
};
}

#endif //LAYERDATA_HPP
