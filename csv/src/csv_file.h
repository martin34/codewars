
#ifndef CSV_SRC_CSV_FILE_H_
#define CSV_SRC_CSV_FILE_H_

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class CsvFile
{
  public:
    CsvFile(fs::path const& file_path);
    bool Exists();
    bool Empty();

  private:
    std::ifstream in_;
};

#endif // CSV_SRC_CSV_FILE_H_
