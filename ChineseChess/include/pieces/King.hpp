//
// Created by 26326 on 25-8-6.
//

#ifndef KING_HPP
#define KING_HPP
#include "ChessPiece.hpp"

namespace chess::piece {
class King final : public ChessPiece {
public:
	King(const Point & point, bool color, ChessBoard & board);

	bool canMoveTo(const Point &) const override;

	const char * getName() const override;

	const bool canCrossTheRiver() const override;
};
}

#endif //KING_HPP
