//
// Created by 26326 on 25-8-6.
//

#ifndef POINT_HPP
#define POINT_HPP
#include <cstdint>

namespace chess {
static constexpr bool Red = true, Black = false;

class Point {
public:
	int8_t row;
	int8_t col;

	Point(int8_t row, int8_t col);

	bool colorOfTheArea() const;

	bool isInNinePalaces() const;

	bool operator==(const Point & point) const;
};
} // chess

#endif //POINT_HPP
