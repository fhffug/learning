//
// Created by 26326 on 25-8-6.
//

#include "pieces/ChessPiece.hpp"


namespace chess::piece {
ChessPiece::ChessPiece(const Point & point, bool color, ChessBoard & board)
	: color(color), pt(point), board(board) {
}

const Point & ChessPiece::getPoint() const {
	return pt;
}

bool ChessPiece::moveTo(const Point & point) {
	if (canMoveTo(point)) {
		board.getChess(pt) = nullptr;
		pt.row = point.row;
		pt.col = point.col;

		board.removeChess(point);
		board.getChess(point) = this;

		return true;
	}
	return false;
}
}
