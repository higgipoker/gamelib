/****************************************************************************
 * Copyright (C) 2018 by Paul Higgins
 *
 * This file is part of GameLib.
 *
 *   GameLib is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   GameLib is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with GameLib. If not, see <http://www.gnu.org/licenses/>
 ****************************************************************************/
/**
 * @file file.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "file.h"
#include <iostream>
#include <sstream>

namespace GameLib {

// ------------------------------------------------------------
// File
// ------------------------------------------------------------
File::File(const std::string &f) : file_name(f) {
    read = write = false;
}

// ------------------------------------------------------------
// ~File
// ------------------------------------------------------------
File::~File() {
    Close();
}

// ------------------------------------------------------------
// Close
// ------------------------------------------------------------
void File::Close() {
    if (read) {
        in_file.close();
    }
    if (write) {
        out_file.close();
    }
}

// ------------------------------------------------------------
// WriteLine
// ------------------------------------------------------------
void File::WriteLine(const std::string &line) {
    open_for_write();

    if (out_file.is_open()) {
        out_file << line.c_str() << "\n";
    } else {
        std::cout << "Unable to opne file: " << file_name.c_str();
    }
}

// ------------------------------------------------------------
// WriteLine
// ------------------------------------------------------------
void File::WriteLine(int line) {
    std::ostringstream str;
    str << line;

    WriteLine(str.str());
}

// ------------------------------------------------------------
// open_for_write
// ------------------------------------------------------------
void File::open_for_write() {
    if (write) {
        return;
    }

    if (read) {
        in_file.close();
        read = false;
    }

    out_file.open(file_name.c_str(), std::ios::out);
    write = true;
}

// ------------------------------------------------------------
// open_for_read
// ------------------------------------------------------------
void File::open_for_read() {
    if (read) {
        return;
    }

    if (write) {
        out_file.close();
        write = false;
    }

    in_file.open(file_name.c_str(), std::ios::in);
    read = true;
}

// ------------------------------------------------------------
// GetLines
// ------------------------------------------------------------
std::vector<std::string> File::GetLines(const std::string &_ignore) {
    open_for_read();

    std::string line;
    while (getline(in_file, line)) {
        if (_ignore.length()) {
            std::size_t found = line.find(_ignore);
            if (found == std::string::npos)
                lines.push_back(line);
        } else {
            lines.push_back(line);
        }
    }

    return lines;
}
} // namespace GameLib
