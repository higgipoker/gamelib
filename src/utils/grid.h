#pragma once
#include <vector>
#include "../math/shapes.h"

namespace GameLib {

/** @ brief struct to represent one sector */
struct Sector {
  Sector() { x = y = row = col = 0; }

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
  /**
 * @brief constructor
 */
  Grid(int startx, int starty, int w, int h, int c, int r);

  /**
    \brief get the sector number form col + row
    */
  int ColRowToSector(int col, int row);

  /**
    \brief get sector number from coordinates
    */
  int CoordinatesToSector(int x, int y);

  /**
  *  @brief  get center point of sector
  */
  Point GetSectorCenter(int sector);

 private:
  int x, y, width, height, cols, rows;
  int sector_width, sector_height;
  std::vector<Sector> sectors;
  int center_column, center_row;
};
}  // namespace GameLib
