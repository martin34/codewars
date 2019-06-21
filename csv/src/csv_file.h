
#ifndef CSV_SRC_CSV_FILE_H_
#define CSV_SRC_CSV_FILE_H_

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

using Lines = std::vector<std::string>;
using Table = std::vector<Lines>;

class CsvFileReader {
public:
  CsvFileReader(fs::path const &file_path);
  bool Exists();
  bool Empty();
  Lines GetLines();

private:
  std::ifstream in_;
  std::vector<std::string> lines_;

  void ReadFile();
};

void WriteLines(fs::path const &output_file_path, Lines const &lines);
Lines Split(const std::string &str, char delim = ' ');
Lines CreateCopyWithReplacedColumn(Lines const &in, std::string column,
                                   std::string replacement);

#endif // CSV_SRC_CSV_FILE_H_
