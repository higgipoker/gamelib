#pragma once
#include "../math/shapes.h"
#include <vector>

namespace GameLib {

/** @ brief struct to represent one sector */
struct Sector {
    Sector() {
        x = y = w = h = row = col = 0;
    }

    Sector (unsigned int _x, unsigned int _y, unsigned int _w, unsigned int _h, unsigned int _row, unsigned int _col) {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
        row = _row;
        col = _col;
    }

    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
    unsigned int row;
    unsigned int col;
};

class Grid {
public:
    Grid (unsigned int startx, unsigned int starty, unsigned int w, unsigned int h, unsigned int c, unsigned int r);

    unsigned int ColRowToSector (unsigned int col, unsigned int row);
    unsigned int CoordinatesToSector (unsigned int x, unsigned int y);
    unsigned int PointToSector (Point p);
    Point GetSectorCenter (unsigned int sector);
    unsigned int OffsetSectorY (unsigned int sector, unsigned int rows);
    unsigned int NumberSectors();

private:
    unsigned int x, y, width, height, cols, rows;
    unsigned int sector_width, sector_height;
    std::vector<Sector> sectors;
    unsigned int center_column, center_row;

    unsigned int get_first_in_row (unsigned int sector);
    unsigned int get_last_in_row (unsigned int sector);
    unsigned int get_first_in_col (unsigned int sector);
    unsigned int get_last_in_col (unsigned int sector);
};
} // namespace GameLib
