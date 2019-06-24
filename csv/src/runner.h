#ifndef CSV_SRC_RUNNER_H_
#define CSV_SRC_RUNNER_H_

#include "csv/src/csv_file.h"
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<std::string> ConvertToStrings(int argc, char **argv);

class Runner {
public:
  Runner(std::vector<std::string> arguments, std::ostream &output_stream);

  void Do();

  struct ErrorStrings {
    static const std::string invalid_args;
    static const std::string no_input_file;
    static const std::string empty_input_file;
    static const std::string output_exits;
  };

private:
  std::vector<std::string> arguments_;
  std::ostream &output_stream_;

  std::optional<CsvFileReader> input_file_;
  std::optional<fs::path> output_file_path_;

  void Prepare();
};

#endif // CSV_SRC_RUNNER_H_
