//
// Created by 26326 on 25-8-24.
//

#ifndef DATA_HPP
#define DATA_HPP

#include "lib_export.h"

namespace ml::data {
class DEEPLEARNING_EXPORT IData {
public:
	virtual ~IData() = default;
};
}

#endif //DATA_HPP
