//
// Created by 26326 on 25-8-6.
//

#ifndef CANNON_HPP
#define CANNON_HPP
#include "ChessPiece.hpp"

namespace chess::piece {
class Cannon final : public ChessPiece {
public:
	Cannon(const Point & point, bool color, ChessBoard & board);

	const char * getName() const override;

	const bool canCrossTheRiver() const override;

	bool canMoveTo(const Point &) const override;
};
}

#endif //CANNON_HPP
