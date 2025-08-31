//
// Created by 26326 on 25-8-6.
//

#include "pieces/Horse.hpp"

namespace chess::piece {
Horse::Horse(const Point & point, const bool color, ChessBoard & board): ChessPiece(point, color, board) {
}

const char * Horse::getName() const {
	return "马";
}

const bool Horse::canCrossTheRiver() const {
	return true;
}

bool Horse::canMoveTo(const Point & point) const {
	static const Point s[8] = {
		{2, 1}, {2, -1},
		{-2, 1}, {-2, -1},
		{1, 2}, {1, -2},
		{-1, 2}, {-1, -2}
	}, u[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	if (board.getChess(point) == nullptr || board.getChess(point)->color != this->color) {
		for (auto i{0}; i < 8; i++) {
			if (point == Point(pt.row + s[i].row, pt.col + s[i].col) &&
			    board.getChess(Point(pt.row + u[i / 2].row, pt.col + u[i / 2].col)) == nullptr) {
				return true;
			}
		}
	}
	return false;
}
}

