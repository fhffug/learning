//
// Created by 26326 on 25-8-18.
//
#include "layer/Layer.hpp"

ml::layer::Layer * ml::layer::load_layer(const std::string & path) {
	return nullptr;
}

ml::layer::Layer::Layer(const int32_t input_dim, const int32_t output_dim)
	: m_input_dim(input_dim), m_output_dim(output_dim) {
}

int32_t ml::layer::Layer::get_input_dim() const {
	return this->m_input_dim;
}

int32_t ml::layer::Layer::get_output_dim() const {
	return this->m_output_dim;
}
