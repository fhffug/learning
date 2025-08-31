//
// Created by 26326 on 25-8-6.
//

#include "pieces/Cannon.hpp"

namespace chess::piece {
Cannon::Cannon(const Point & point, const bool color, ChessBoard & board)
	: ChessPiece(point, color, board) {
}

const char * Cannon::getName() const {
	return "炮";
}

const bool Cannon::canCrossTheRiver() const {
	return true;
}

bool Cannon::canMoveTo(const Point & point) const {
	if (board.getChess(point) == nullptr) {
		if (point.row == pt.row) {
			if (point.col < pt.col) {
				for (int8_t i = point.col + 1; i < pt.col; i++) {
					if (board.getChess({point.row, i})) {
						return false;
					}
				}
			} else {
				for (int8_t i = pt.col + 1; i < point.col; i++) {
					if (board.getChess({point.row, i})) {
						return false;
					}
				}
			}
		} else if (point.col == pt.col) {
			if (point.row < pt.row) {
				for (int8_t i = point.row + 1; i < pt.row; i++) {
					if (board.getChess({i, point.col})) {
						return false;
					}
				}
			} else {
				for (int8_t i = pt.row + 1; i < point.row; i++) {
					if (board.getChess({i, point.col})) {
						return false;
					}
				}
			}
		}
		return true;
	}
	if (board.getChess(point)->color == this->color) {
		uint16_t count = 0;
		if (point.row == pt.row) {
			if (point.col < pt.col) {
				for (int8_t i = point.col + 1; i < pt.col; i++) {
					if (board.getChess({point.row, i})) {
						count++;
					}
				}
			} else {
				for (int8_t i = pt.col + 1; i < point.col; i++) {
					if (board.getChess({point.row, i})) {
						count++;
					}
				}
			}
		} else if (point.col == pt.col) {
			if (point.row < pt.row) {
				for (int8_t i = point.row + 1; i < pt.row; i++) {
					if (board.getChess({i, point.col})) {
						count++;
					}
				}
			} else {
				for (int8_t i = pt.row + 1; i < point.row; i++) {
					if (board.getChess({i, point.col})) {
						count++;
					}
				}
			}
		}
		return count == 1;
	}
	return false;
}
}
