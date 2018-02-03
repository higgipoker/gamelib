#include "grid.h"
namespace GameLib {

// --------------------------------------------------
// Constructor
// --------------------------------------------------
Grid::Grid (unsigned int startx, unsigned int starty, unsigned int w, unsigned int h, unsigned int c, unsigned int r) {
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

    unsigned int cnt = 0;
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            sectors.push_back (Sector ( (j * sector_width) + x, (i * sector_height) + y, sector_width, sector_height, i, j));
            // sectors_reversed.push_back(cnt);
            cnt++;
        }
    }
}

// --------------------------------------------------
// NumberSectors
// --------------------------------------------------
unsigned int Grid::NumberSectors() {
    return cols * rows;
}

// --------------------------------------------------
// GetSector
// --------------------------------------------------
unsigned int Grid::ColRowToSector (unsigned int col, unsigned int row) {
    return (row * cols) + col;
}

// --------------------------------------------------
// CoordinatesToSector
// --------------------------------------------------
unsigned int Grid::CoordinatesToSector (unsigned int cx, unsigned int cy) {
    cx -= x;
    cy -= y;

    if (cx > cols * sector_width)
        return 0;
    if (cy > rows * sector_height)
        return 0;

    unsigned int sector = 0;

    unsigned int col = cx / sector_width;
    unsigned int row = cy / sector_height;

    sector = (col + (cols * row));

    return sector;
}

//  --------------------------------------------------
//  PointToSector
//  --------------------------------------------------
unsigned int Grid::PointToSector (Point p) {
    return CoordinatesToSector (static_cast<unsigned int> (p.x), static_cast<unsigned int> (p.y));
}

//  --------------------------------------------------
//  GetSectorCenter
//  --------------------------------------------------
Point Grid::GetSectorCenter (unsigned int sector) {
    GameLib::Point center;

    if (sector < sectors.size()) {
        center.x = sectors[sector].x + (sector_width / 2);
        center.y = sectors[sector].y + (sector_height / 2);
    }

    return center;
}

unsigned int Grid::get_first_in_row (unsigned int sector) {
    return sectors[sector].row * cols;
}

unsigned int Grid::get_last_in_row (unsigned int sector) {
    return (sectors[sector].row * cols) + cols - 1;
}

unsigned int Grid::get_first_in_col (unsigned int sector) {
    return sectors[sector].col;
}

unsigned int Grid::get_last_in_col (unsigned int sector) {
    return (rows - 1) * cols + sectors[sector].col;
}

unsigned int Grid::OffsetSectorY (unsigned int sector, unsigned int rows) {
    unsigned int min = get_first_in_col (sector);
    unsigned int max = get_last_in_col (sector);

    unsigned int new_sector = sector + (cols * rows);

    if (new_sector < min)
        new_sector = min;
    else if (new_sector > max)
        new_sector = max;

    return new_sector;
}

} // namespace GameLib
