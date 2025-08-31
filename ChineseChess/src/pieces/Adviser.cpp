//
// Created by 26326 on 25-8-6.
//

#include "pieces/Adviser.hpp"

namespace chess::piece {
Adviser::Adviser(const Point & point, const bool color, ChessBoard & board) : ChessPiece(point, color, board) {
}

const char * Adviser::getName() const {
    return "士";
}

const bool Adviser::canCrossTheRiver() const {
    return false;
}

bool Adviser::canMoveTo(const Point & point) const {
    static const Point s[4] = {
        {1, 1}, {1, -1},
        {-1, 1}, {-1, -1}
    };
    if (board.getChess(point) == nullptr || board.getChess(point)->color != this->color) {
        if (color == point.colorOfTheArea() && point.isInNinePalaces()) {
            for (const auto i: s) {
                if (point == Point(pt.row + i.row, pt.col + i.col)) {
                    return true;
                }
            }
        }
    }
    return false;
}
}
