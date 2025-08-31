//
// Created by 26326 on 25-8-24.
//

#include "data/Data.hpp"

using namespace ml::data;

Data::Data() = default;

Eigen::MatrixXd Data::at(const std::string & key) {
	return data[key];
}

Eigen::MatrixXd Data::at(const std::string & key) const {
	return data.at(key);
}

Eigen::MatrixXd Data::operator[](const std::string & key) {
	return data[key];
}

Eigen::MatrixXd Data::operator[](const std::string & key) const {
	return data.at(key);
}
