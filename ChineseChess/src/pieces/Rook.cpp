//
// Created by 26326 on 25-8-6.
//

#include "pieces/Rook.hpp"

namespace chess::piece {
Rook::Rook(const Point & point, const bool color, ChessBoard & board)
	: ChessPiece(point, color, board) {
}

const char * Rook::getName() const {
	return "车";
}

const bool Rook::canCrossTheRiver() const {
	return true;
}

bool Rook::canMoveTo(const Point & point) const {
	if (board.getChess(point) == nullptr || board.getChess(point)->color != this->color) {
		if (pt.row == point.row) {
			if (point.col < pt.col) {
				for (int8_t i = point.col + 1; i < pt.col; i++) {
					if (board.getChess({point.row, i})) {
						// 判断中间是否有棋子
						return false;
					}
				}
			} else {
				for (int8_t i = pt.col + 1; i < point.col; i++) {
					if (board.getChess({point.row, i})) {
						// 判断中间是否有棋子
						return false;
					}
				}
			}
			return true;
		}
		if (pt.col == point.col) {
			if (point.row < pt.row) {
				for (int8_t i = point.row + 1; i < pt.row; i++) {
					if (board.getChess({i, point.col})) {
						// 判断中间是否有棋子
						return false;
					}
				}
			} else {
				for (int8_t i = pt.row + 1; i < point.row; i++) {
					if (board.getChess({i, point.col})) {
						// 判断中间是否有棋子
						return false;
					}
				}
			}
			return true;
		}
	}
	return false;
}
} // piece
