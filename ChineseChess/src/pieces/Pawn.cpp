//
// Created by 26326 on 25-8-6.
//

#include "pieces/Pawn.hpp"

namespace chess::piece {
Pawn::Pawn(const Point & point, const bool color, ChessBoard & board) : ChessPiece(point, color, board) {
}

const char * Pawn::getName() const {
	return "兵";
}

const bool Pawn::canCrossTheRiver() const {
	return true;
}

bool Pawn::canMoveTo(const Point & point) const {
	if (board.getChess(point) == nullptr || board.getChess(point)->color != color) {
		static const Point red_s[3] = {{0, -1}, {-1, 0}, {1, 0}};
		static const Point black_s[3] = {{0, 1}, {1, 0}, {-1, 0}};
		if (color == point.colorOfTheArea()) {
			// 没过河
			return point == Point(pt.row, pt.col + color ? red_s[0].col : black_s[0].col);
		}
		for (const auto & i: color ? red_s : black_s) {
			if (point == Point(pt.row + i.row, pt.col + i.col)) {
				return true;
			}
		}
	}
	return false;
}
}
