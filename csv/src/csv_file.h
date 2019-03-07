
#ifndef CSV_SRC_CSV_FILE_H_
#define CSV_SRC_CSV_FILE_H_

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

using Lines = std::vector<std::string>;
using Table = std::vector<Lines>;

class CsvFile
{
  public:
    CsvFile(fs::path const& file_path);
    bool Exists();
    bool Empty();
    Lines GetLines();

  private:
    std::ifstream in_;
};

Lines Split(const std::string& str, char delim = ' ');
Lines CreateCopyWithReplacedColumn(Lines const& in, std::string column, std::string replacement);
void WriteLines(fs::path const& output_file_path, Lines const& lines);

#endif // CSV_SRC_CSV_FILE_H_
