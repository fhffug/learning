//
// Created by 26326 on 25-8-6.
//

#ifndef ELEPHANT_HPP
#define ELEPHANT_HPP
#include "ChessPiece.hpp"

namespace chess::piece {
class Elephant final : public ChessPiece {
public:
	Elephant(const Point & point, bool color, ChessBoard & board);

	bool canMoveTo(const Point &) const override;

	const char * getName() const override;

	const bool canCrossTheRiver() const override;
};
}

#endif //ELEPHANT_HPP
