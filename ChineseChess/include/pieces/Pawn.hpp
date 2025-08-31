//
// Created by 26326 on 25-8-6.
//

#ifndef PAWN_HPP
#define PAWN_HPP
#include "ChessPiece.hpp"

namespace chess::piece {
class Pawn final : public ChessPiece {
public:
	Pawn(const Point & point, bool color, ChessBoard & board);

	bool canMoveTo(const Point &) const override;

	const char * getName() const override;

	const bool canCrossTheRiver() const override;
};
}

#endif //PAWN_HPP
