#include <iostream>

#include "NeuralNetworkDebug.hpp"
#include "NeuralNetworkTesting.hpp"
#include "function/activation.hpp"
#include "layer/DenseLayer.hpp"
#include "persistence/savers/NetWorkSaver.hpp"
#pragma omp simd

int tag(double x, double y);

void test_network();

int main(int argc, char ** argv) {
	try {
		test_network();
	} catch (std::exception & e) {
		std::cout << "error:\n" << e.what() << std::endl;
	} catch (...) {
		std::cout << "error" << std::endl;
	}
	return 0;
}


void test_network() {
	using namespace ml;
	const NetWorkSaver saver{"E:/model"};
	Eigen::setNbThreads(16);
	Eigen::MatrixXd input = Eigen::MatrixXd::Random(100, 2);
	Eigen::MatrixXd label(100, 1);
	for (auto i = 0; i < 100; ++i) {
		label(i, 0) = tag(input(i, 0), input(i, 1));
	}
	const std::unique_ptr<NeuralNetwork> net = std::make_unique<NeuralNetworkTesting>();
	// 使用合适的网络结构
	net->add_layer(std::make_unique<layer::DenseLayer>(2, 16));
	net->add_layer(std::make_unique<layer::DenseLayer>(16, 8));
	net->add_layer(std::make_unique<layer::DenseLayer>(8, 1));
	for (auto i = 0; i < 10000; ++i) {
		net->train(input, label);
		// std::cout << "loss: " << net->backward(input).squaredNorm() << std::endl;
		std::cout << "epoch: " << i << std::endl;
		// saver.save(net);
	}
	const Eigen::MatrixXd test = Eigen::MatrixXd::Random(10, 2);
	std::cout << "input:\n" << test << '\n' << std::endl;
	const auto & result = net->forward(test);
	std::cout << "result:\n" << result << std::endl;

	// 验证结果
	std::cout << "\nValidation:" << std::endl;
	for (int i = 0; i < test.rows(); ++i) {
		const double x = test(i, 0);
		const double y = test(i, 1);
		const double dist_sq = x * x + y * y;
		const int expected = (dist_sq < 1) ? 0 : 1;
		const double predicted = result(i, 0);
		std::cout << "(" << x << ", " << y << ") -> distance^2: " << dist_sq
				<< ", expected: " << expected << ", predicted: " << predicted;
		if ((expected == 0 && predicted < 0.5) || (expected == 1 && predicted > 0.5)) {
			std::cout << " [CORRECT]" << std::endl;
		} else {
			std::cout << " [INCORRECT]" << std::endl;
		}
	}
}

int tag(const double x, const double y) {
	if (x * x + y * y < 1) {
		return 0;
	}
	return 1;
}
