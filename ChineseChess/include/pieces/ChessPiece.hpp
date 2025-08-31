//
// Created by 26326 on 25-8-6.
//

#ifndef CHESSPIECE_HPP
#define CHESSPIECE_HPP
#include "ChessBoard.hpp"
#include "Point.hpp"

namespace chess::piece {
class ChessPiece {
public:
	/// 红 1：黑 0
	const bool color;

protected:
	Point pt;
	ChessBoard & board;

public:
	virtual ~ChessPiece() = default;

	ChessPiece(const Point & point, bool color, ChessBoard & board);

	const Point & getPoint() const;

	/// 判断能否移动到指定地点（但不移动）
	virtual bool canMoveTo(const Point &) const = 0;

	/// 获取棋子名称
	virtual const char * getName() const = 0;

	/// 棋子能否过河
	virtual const bool canCrossTheRiver() const = 0;

	bool moveTo(const Point &);
};
}

#endif //CHESSPIECE_HPP
