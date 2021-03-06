#pragma once

struct FieldPosition {
    int row = 0, col = 0;
    bool operator<(const FieldPosition &other) const {
        return (row < other.row) ? true : (row > other.row ? false : col < other.col);
    }
    bool operator==(const FieldPosition &other) const {
        return row == other.row && col == other.col;
    }
    bool operator!=(const FieldPosition &other) const {
        return !(*this == other);
    }
};