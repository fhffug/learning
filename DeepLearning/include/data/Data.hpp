//
// Created by 26326 on 25-8-24.
//

#ifndef DATA_HPP
#define DATA_HPP

#include "lib_export.h"

namespace ml::data {
class DEEPLEARNING_EXPORT Data {
protected:
	std::map<std::string, Eigen::MatrixXd> data;

public:
	Data();

	Eigen::MatrixXd at(const std::string & key);

	[[nodiscard]] Eigen::MatrixXd at(const std::string & key) const;

	Eigen::MatrixXd operator[](const std::string & key);

	Eigen::MatrixXd operator[](const std::string & key) const;
};
}

#endif //DATA_HPP
