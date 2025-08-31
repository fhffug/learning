//
// Created by 26326 on 25-8-6.
//

#ifndef ROOK_HPP
#define ROOK_HPP
#include "ChessPiece.hpp"

namespace chess::piece {
class Rook final : public ChessPiece {
public:
	Rook(const Point & point, bool color, ChessBoard & board);

	bool canMoveTo(const Point &) const override;

	const char * getName() const override;

	const bool canCrossTheRiver() const override;
};
} // piece

#endif //ROOK_HPP
