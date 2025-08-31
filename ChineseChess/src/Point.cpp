//
// Created by 26326 on 25-8-6.
//

#include "Point.hpp"

namespace chess {
Point::Point(const int8_t row, const int8_t col)
	: row(row), col(col) {
}

bool Point::colorOfTheArea() const {
	if (col <= 4) {
		return Red;
	}
	return Black;
}

bool Point::isInNinePalaces() const {
	return row >= 3 && row <= 5 && (col <= 2 || col >= 7);
}

bool Point::operator==(const Point & point) const {
	return row == point.row && col == point.col;
}
} // chess
