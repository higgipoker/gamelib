#include "file.h"
#include <iostream>
#include <sstream>

namespace GameLib {

File::File(const std::string &f) : file_name(f) {
  read = write = false;
}

File::~File() { Close(); }

void File::Close() {
  if (read) {
    in_file.close();
  }
  if (write) {
    out_file.close();
  }
}

void File::WriteLine(const std::string &line) {
  open_for_write();

  if (out_file.is_open()) {
    out_file << line.c_str() << "\n";
  } else {
    std::cout << "Unable to opne file: " << file_name.c_str();
  }
}

void File::WriteLine(int line) {
  std::ostringstream str;
  str << line;

  WriteLine(str.str());
}

void File::open_for_write() {
  if (write) {
    return;
  }

  if (read) {
    in_file.close();
  }

  out_file.open(file_name.c_str(), std::ios::out);
  write = true;
}

void File::open_for_read() {
  if (read) {
    return;
  }

  if (write) {
    out_file.close();
  }

  in_file.open(file_name.c_str(), std::ios::in);
  read = true;
}

std::vector<std::string> File::GetLines(const std::string &_ignore) {
  open_for_read();

  // temp
  std::string line;
  while (getline(in_file, line)) {
    if (_ignore.length()) {
      std::size_t found = line.find(_ignore);
      if (found == std::string::npos) lines.push_back(line);
    }else{
        lines.push_back(line);
    }
  }

  return lines;
}
}  // namespace GameLib
