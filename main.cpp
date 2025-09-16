#include <iostream>

#include "NeuralNetworkTesting.hpp"
#include "function/activation.hpp"
#include "layer/DenseLayer.hpp"

#include "persistence/loaders/NetWorkLoader.hpp"
#include "persistence/savers/NetWorkSaver.hpp"
#pragma omp simd

namespace color {
constexpr std::string RESET = R"([0m)";
constexpr std::string RED = R"([31m)";
constexpr std::string GREEN = R"([32m)";
constexpr std::string YELLOW = R"([33m)";
constexpr std::string BLUE = R"([34m)";
constexpr std::string MAGENTA = R"([35m)";
constexpr std::string CYAN = R"([36m)";
constexpr std::string WHITE = R"([37m)";
}

int tag(double x, double y);

void test_network();

void test_saver() {
	using namespace ml;
	saver::NetWorkSaver saver{"E:\\models"};
	std::vector<std::unique_ptr<layer::Layer>> layers;
	layers.push_back(std::make_unique<layer::DenseLayer>(4, 16));
	layers.push_back(std::make_unique<layer::DenseLayer>(16, 8));
	layers.push_back(std::make_unique<layer::DenseLayer>(8, 2));
	saver.save_layers(layers);
}

void test_loader() {
	using namespace ml;
	loader::NetWorkLoader loader{"E:/model"};
	loader.test();
}

int main(int argc, char ** argv) {
	try {
		// test_network();
		test_saver();
		test_loader();
	} catch (std::exception & e) {
		std::cout << "error:\n" << e.what() << std::endl;
	} catch (...) {
		std::cout << "error" << std::endl;
	}
	return 0;
}

void test_network() {
	using namespace ml;
	const saver::NetWorkSaver saver{"E:/model"};
	Eigen::setNbThreads(16);
	Eigen::MatrixXd input = Eigen::MatrixXd::Random(10, 2);
	Eigen::MatrixXd label(10, 1);
	for (auto i = 0; i < 10; ++i) {
		label(i, 0) = tag(input(i, 0), input(i, 1));
	}
	const std::unique_ptr<NeuralNetwork> net = std::make_unique<NeuralNetworkTesting>();
	// 使用合适的网络结构
	net->add_layer(std::make_unique<layer::DenseLayer>(2, 16));
	net->add_layer(std::make_unique<layer::DenseLayer>(16, 8));
	net->add_layer(std::make_unique<layer::DenseLayer>(8, 1));
	for (auto i = 0; i < 100; ++i) {
		net->train(input, label);
		std::cout << "epoch: " << i << std::endl;
	}
	Eigen::MatrixXd test = Eigen::MatrixXd::Random(10, 2);
	std::cout << "input:\n" << test << '\n' << std::endl;
	const auto result = net->forward(test);
	std::cout << "result:\n" << result << std::endl;

	// 验证结果
	using namespace color;
	std::cout << "\nValidation:" << std::endl;
	for (int i = 0; i < test.rows(); ++i) {
		const double x = test(i, 0);
		const double y = test(i, 1);
		const double dist_sq = x * x + y * y;
		const int expected = dist_sq < 1 ? 0 : 1;
		const double predicted = result(i, 0);
		std::cout << BLUE << "(" << x << ", " << y << ") " << "->" << YELLOW << " distance^2: " << dist_sq
				<< CYAN << ", expected: " << expected << ", predicted: " << predicted;
		if ((expected == 0 && predicted < 0.5) || (expected == 1 && predicted > 0.5)) {
			std::cout << GREEN << " [CORRECT]" << std::endl;
		} else {
			std::cout << RED << " [INCORRECT]" << std::endl;
		}
	}
}

int tag(const double x, const double y) {
	if (x * x + y * y < 1) {
		return 0;
	}
	return 1;
}
