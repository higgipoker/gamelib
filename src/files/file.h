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
 * @file file.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace GameLib {

/**
 * @brief The File class
 */
class File {
  public:
    /**
     * @brief File
     * @param f
     */
    explicit File(const std::string &f);

    /**
      */
    ~File();

    /**
     * @brief WriteLine
     * @param line
     */
    void WriteLine(const std::string &line);

    /**
     * @brief WriteLine
     * @param line
     */
    void WriteLine(int line);

    /**
     * @brief Close
     */
    void Close();

    /**
     * @brief GetLines
     * @param _ignore
     * @return
     */
    std::vector<std::string> GetLines(const std::string &_ignore = "");

  protected:
    std::string file_name;
    std::ofstream out_file;
    std::ifstream in_file;

    std::vector<std::string> lines;

    bool read;
    bool write;

    /**
     * @brief open_for_write
     */
    void open_for_write();

    /**
     * @brief open_for_read
     */
    void open_for_read();
};

} // namespace GameLib
