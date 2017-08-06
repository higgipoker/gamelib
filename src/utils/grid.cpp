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
            sectors.push_back(Sector((j * sector_width) + x, (i * sector_height) + y, sector_width, sector_height, i, j));
            // sectors_reversed.push_back(cnt);
            cnt++;
        }
    }
}

// --------------------------------------------------
// GetSector
// --------------------------------------------------
int Grid::ColRowToSector(int col, int row) {
    return (row * cols) + col;
}

// --------------------------------------------------
// CoordinatesToSector
// --------------------------------------------------
int Grid::CoordinatesToSector(int cx, int cy) {
    cx -= x;
    cy -= y;

    if (cx < 0 || cy < 0)
        return -1;
    if (cx > cols * sector_width)
        return -1;
    if (cy > rows * sector_height)
        return -1;

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

int Grid::PointToSector(Point p) {
    return CoordinatesToSector(p.x, p.y);
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

int Grid::get_first_in_row(int sector) {
    return sectors[sector].row * cols;
}

int Grid::get_last_in_row(int sector) {
    return (sectors[sector].row * cols) + cols - 1;
}

int Grid::get_first_in_col(int sector) {
    return sectors[sector].col;
}

int Grid::get_last_in_col(int sector) {
    return (rows - 1) * cols + sectors[sector].col;
}

int Grid::OffsetSectorY(int sector, int rows) {
    int min = get_first_in_col(sector);
    int max = get_last_in_col(sector);

    int new_sector = sector + (cols * rows);

    if (new_sector < min)
        new_sector = min;
    else if (new_sector > max)
        new_sector = max;

    return new_sector;
}

} // namespace GameLib
