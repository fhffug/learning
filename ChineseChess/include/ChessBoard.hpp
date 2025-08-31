//
// Created by 26326 on 25-8-6.
//

#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP
#include <cstdint>
#include <list>

#include "Point.hpp"

namespace chess::piece {
class ChessPiece;
}

namespace chess {
constexpr uint8_t BOARD_ROW = 10;
constexpr uint8_t BOARD_COL = 9;

class ChessBoard {
public:
	ChessBoard();

	~ChessBoard();

private:
	friend class piece::ChessPiece;
	piece::ChessPiece * board[BOARD_ROW][BOARD_COL]{};
	std::list<piece::ChessPiece *> red;
	std::list<piece::ChessPiece *> black;

public:

	const std::list<piece::ChessPiece *> & getRedPieces() const;

	const std::list<piece::ChessPiece *> & getBlackPieces() const;

	piece::ChessPiece *& getChess(const Point &);

	piece::ChessPiece * const & getChess(const Point &) const;

	void removeChess(const Point &);

	bool kingsFaceToFace() const;
};
} // chess

#endif //CHESSBOARD_HPP
