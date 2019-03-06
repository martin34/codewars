#include "input.h"
#include "csv_file.h"
#include  <filesystem>

namespace fs = std::filesystem;

std::vector<std::string> ConvertToStrings(int argc, char** argv)
{
  std::vector<std::string> strings;
  for(int i = 0; i < argc; ++i)
  {
    strings.push_back(argv[i]);
  }
  return strings;
}
bool ArgumentsValid(std::vector<std::string> const& arguments)
{
  return arguments.size() != 5;
}

Runner::Runner(std::vector<std::string> arguments, std::ostream & output_stream) : arguments_(arguments), output_stream_(output_stream){
}
void Runner::Do(){
  if(ArgumentsValid(arguments_))
  {
    output_stream_ << std::string{"Not enough input arguments"};
    return;
  }
  auto input_file_path = fs::absolute(fs::path{arguments_[1]});
  CsvFile csv{input_file_path};
  if(!csv.Exists())
  {
    output_stream_ << std::string{"Input file missing"};
    return;
  }
  if(csv.Empty())
  {
    output_stream_ << std::string{"Input file is empty"};
    return;
  }
}
