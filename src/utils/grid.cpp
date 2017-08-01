#include "grid.h"
namespace GameLib {

// --------------------------------------------------
// Constructor
// --------------------------------------------------
Grid::Grid(int startx, int starty, int w, int h, int c, int r) {
  x = startx;
  y = starty;
  cols = c;
  rows = r;
  width = w;
  height = h;

  center_column = cols / 2;
  center_row = rows / 2;

  sectors.clear();
  // sectors_reversed.clear();
  sector_width = width / cols;
  sector_height = height / rows;

  int cnt = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      sectors.push_back(Sector((j * sector_width) + x, (i * sector_height) + y,
                               sector_width, sector_height, i, j));
      // sectors_reversed.push_back(cnt);
      cnt++;
    }
  }
}

// --------------------------------------------------
// GetSector
// --------------------------------------------------
int Grid::ColRowToSector(int col, int row) { return (row * cols) + col; }

// --------------------------------------------------
// CoordinatesToSector
// --------------------------------------------------
int Grid::CoordinatesToSector(int cx, int cy) {
  cx -= x;
  cy -= y;

  int sector = 0;

  int col = cx / sector_width;
  int row = cy / sector_height;

  sector = (col + (cols * row));

  // coords not in grid
  if (sector < 0 || sector >= (int)sectors.size()) {
    sector = -1;
  }

  return sector;
}

//  --------------------------------------------------
//  GetSectorCenter
//  --------------------------------------------------
Point Grid::GetSectorCenter(int sector) {
  GameLib::Point center;

  if (sector < (int)sectors.size()) {
    center.x = sectors[sector].x + (sector_width / 2);
    center.y = sectors[sector].y + (sector_height / 2);
  }

  return center;
}

}  // namespace GameLib
