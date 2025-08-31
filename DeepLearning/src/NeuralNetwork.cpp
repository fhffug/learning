//
// Created by 26326 on 25-8-29.
//

#include "NeuralNetwork.hpp"

using namespace ml;

NeuralNetwork::NeuralNetwork(std::string name, const std::vector<int32_t> & input_shape,
                             const std::vector<int32_t> & output_shape) : name(std::move(name)),
                                                                          input_shape(input_shape),
                                                                          output_shape(output_shape) {
}
