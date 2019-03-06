#include "csv_file.h"


CsvFile::CsvFile(fs::path const& file_path) : in_(file_path){}

bool CsvFile::Exists(){
  return in_.is_open();
}

bool CsvFile::Empty(){
  std::vector<std::string> lines;
  std::string tmp;
  while(std::getline(in_, tmp))
  {
    if(tmp.size() > 0)
    {
      lines.push_back(tmp);
    }
  }
  return lines.empty();
}


