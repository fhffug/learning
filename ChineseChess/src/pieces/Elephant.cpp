//
// Created by 26326 on 25-8-6.
//

#include "pieces/Elephant.hpp"

namespace chess::piece {
Elephant::Elephant(const Point & point, const bool color, ChessBoard & board) : ChessPiece(point, color, board) {
}

const char * Elephant::getName() const {
    return "象";
}

const bool Elephant::canCrossTheRiver() const {
    return false;
}

bool Elephant::canMoveTo(const Point & point) const {
    static const Point s[4] = {
        {2, 2}, {2, -2},
        {-2, 2}, {-2, -2},
    }, u[4] = {
        {1, 1}, {1, -1},
        {-1, 1}, {-1, -1}
    };
    if (board.getChess(point) == nullptr || board.getChess(point)->color != this->color) {
        if (color == point.colorOfTheArea()) {
            // 在我方范围
            for (auto i = 0; i < 4; ++i) {
                if (point == Point(pt.row + s[i].row, pt.col + s[i].col) &&
                    board.getChess(Point(pt.row + u[i].row, pt.col + u[i].col)) == nullptr) {
                    return true;
                }
            }
        }
    }
    return false;
}
}
