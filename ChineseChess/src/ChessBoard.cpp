//
// Created by 26326 on 25-8-6.
//

#include "ChessBoard.hpp"

#include <algorithm>
#include <cstring>

#include "pieces/King.hpp"
#include "pieces/Rook.hpp"

namespace chess {
const std::list<piece::ChessPiece *> & ChessBoard::getRedPieces() const {
	return red;
}

const std::list<piece::ChessPiece *> & ChessBoard::getBlackPieces() const {
	return black;
}

piece::ChessPiece *& ChessBoard::getChess(const Point & point) {
	return board[point.row][point.col];
}


piece::ChessPiece * const & ChessBoard::getChess(const Point & point) const {
	return board[point.row][point.col];
}

void ChessBoard::removeChess(const Point & point) {
	if (getChess(point) == nullptr) {
		return;
	}
	if (getChess(point)->color == Red) {
		black.remove(getChess(point));
	} else {
		red.remove(getChess(point));
	}
	delete getChess(point);
	getChess(point) = nullptr;
}

bool ChessBoard::kingsFaceToFace() const {
	const auto r = std::ranges::find_if(red, [](piece::ChessPiece * p) {
		return dynamic_cast<piece::King *>(p) != nullptr;
	});
	const auto b = std::ranges::find_if(black, [](piece::ChessPiece * p) {
		return dynamic_cast<piece::King *>(p) != nullptr;
	});
	if (r != red.end() && b != black.end()) {
		if ((*r)->getPoint().row == (*b)->getPoint().row) {
			for (auto i = static_cast<int8_t>((*r)->getPoint().col + 1); i < (*b)->getPoint().col; ++i) {
				if (getChess(Point((*r)->getPoint().row, i))) {
					return false;
				}
			}
		}
	}
	return true;
}


ChessBoard::~ChessBoard() {
	for (const auto piece: red) {
		delete piece;
	}
	for (const auto piece: black) {
		delete piece;
	}
}

ChessBoard::ChessBoard() {
	memset(board, 0, sizeof(board));
	new piece::Rook(Point(0, 0), true, *this);
}
} // chess
