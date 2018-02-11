/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
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
