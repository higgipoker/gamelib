#pragma once
#include "../math/shapes.h"
#include <vector>

namespace GameLib {

/** @ brief struct to represent one sector */
struct Sector {
    Sector() {
        x = y = row = col = 0;
    }

    Sector(int _x, int _y, int _w, int _h, int _row, int _col) {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
        row = _row;
        col = _col;
    }

    int x;
    int y;
    int w;
    int h;
    int row;
    int col;
};

class Grid {
  public:
    Grid(int startx, int starty, int w, int h, int c, int r);

    int ColRowToSector(int col, int row);
    int CoordinatesToSector(int x, int y);
    int PointToSector(Point p);
    Point GetSectorCenter(int sector);
    int OffsetSectorY(int sector, int rows);

  private:
    int x, y, width, height, cols, rows;
    int sector_width, sector_height;
    std::vector<Sector> sectors;
    int center_column, center_row;

    int get_first_in_row(int sector);
    int get_last_in_row(int sector);
    int get_first_in_col(int sector);
    int get_last_in_col(int sector);
};
} // namespace GameLib
