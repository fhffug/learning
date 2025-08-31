//
// Created by 26326 on 25-8-6.
//

#ifndef HORSE_HPP
#define HORSE_HPP
#include "ChessPiece.hpp"

namespace chess::piece {
class Horse final : public ChessPiece {
public:
	Horse(const Point & point, bool color, ChessBoard & board);

	bool canMoveTo(const Point &) const override;

	const char * getName() const override;

	const bool canCrossTheRiver() const override;
};
}

#endif //HORSE_HPP
