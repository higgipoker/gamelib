#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace GameLib {

class File {
  public:
    File(const std::string &f);
    ~File();

    void WriteLine(const std::string &line);
    void WriteLine(int line);
    void Close();
    std::vector<std::string> GetLines(const std::string &_ignore = "");

  protected:
    std::string file_name;
    std::ofstream out_file;
    std::ifstream in_file;

    bool read;
    bool write;

    void open_for_write();
    void open_for_read();

    std::vector<std::string> lines;
};

} // namespace GameLib
