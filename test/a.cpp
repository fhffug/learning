
#include <cstdint>
#include <iostream>
#include <nlohmann/json.hpp>

namespace test::config {
struct Base {
};

class Point : Base {
	int32_t x;
	int32_t y;

public:
	Point() = default;

	explicit Point(const nlohmann::json & json): x(json.at("x").get<int32_t>()), y(json.at("y").get<int32_t>()) {
	}

	explicit Point(int i, int i1): x(i), y(i1) {
	}

	void print() const {
		std::cout << x << " " << y << std::endl;
	}

	friend void to_json(nlohmann::json & j, const Point & p);

	friend void from_json(const nlohmann::json & j, Point & p);
};

void to_json(nlohmann::json & j, const Point & p) {
	j["x"] = p.x;
	j["y"] = p.y;
}

void from_json(const nlohmann::json & j, Point & p) {
	p.x = j.at("x").get<int32_t>();
	p.y = j.at("y").get<int32_t>();
}
}


int main() {
	test::config::Point p{1, 2};
	const nlohmann::json j = p;
	std::cout << j << std::endl;
	const auto p2 = j.get<test::config::Point>();

	p2.print();
}
