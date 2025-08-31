//
// Created by 26326 on 25-8-6.
//

#ifndef ADVISER_HPP
#define ADVISER_HPP
#include "ChessPiece.hpp"

namespace chess::piece {
class Adviser final : public ChessPiece {
public:
	Adviser(const Point & point, bool color, ChessBoard & board);

	bool canMoveTo(const Point &) const override;

	const char * getName() const override;

	const bool canCrossTheRiver() const override;
};
}

#endif //ADVISER_HPP
