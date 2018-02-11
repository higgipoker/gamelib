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
