#include "runner.h"

const std::string Runner::ErrorStrings::invalid_args{
    "Not enough input arguments"};
const std::string Runner::ErrorStrings::no_input_file{"Input file missing"};
const std::string Runner::ErrorStrings::empty_input_file{"Input file is empty"};
const std::string Runner::ErrorStrings::output_exits{
    "Output file already existing"};

std::vector<std::string> ConvertToStrings(int argc, char **argv) {
  std::vector<std::string> strings;
  for (int i = 0; i < argc; ++i) {
    strings.push_back(argv[i]);
  }
  return strings;
}

Runner::Runner(std::vector<std::string> arguments, std::ostream &output_stream)
    : arguments_(arguments), output_stream_(output_stream) {}

void Runner::Do() {
  Prepare();
  if (input_file_ && output_file_path_) {
    auto lines = input_file_.value().GetLines();
    auto new_lines =
        CreateCopyWithReplacedColumn(lines, arguments_[2], arguments_[3]);
    WriteLines(output_file_path_.value(), new_lines);
  }
}

bool ArgumentsValid(std::vector<std::string> const &arguments);

void Runner::Prepare() {
  if (!ArgumentsValid(arguments_)) {
    output_stream_ << ErrorStrings::invalid_args;
    return;
  }
  auto input_file_path = fs::absolute(fs::path{arguments_[1]});
  CsvFileReader csv{input_file_path};
  if (!csv.Exists()) {
    output_stream_ << ErrorStrings::no_input_file;
    return;
  }
  if (csv.Empty()) {
    output_stream_ << ErrorStrings::empty_input_file;
    return;
  }
  input_file_ = std::move(csv);
  auto output_file_path = fs::absolute(fs::path{arguments_[4]});
  if (fs::exists(output_file_path)) {
    output_stream_ << ErrorStrings::output_exits;
    return;
  }
  output_file_path_ = output_file_path;
}

bool ArgumentsValid(std::vector<std::string> const &arguments) {
  return arguments.size() == 5;
}
