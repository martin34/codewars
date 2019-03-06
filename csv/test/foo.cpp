#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <array>
#include <string>
#include <iterator>
#include <algorithm>

#include "csv/src/input.h"

using namespace ::testing;

// https://www.fluentcpp.com/2017/09/25/expressive-cpp17-coding-challenge/

TEST(CommandLineInterface, ConvertToStrings)
{
  std::array<std::string, 5> arguments;
  arguments[0] = "executable name";
  arguments[1] = "data/foo.csv";
  arguments[2] = "foo column";
  arguments[3] = "replacement";
  arguments[4] = "data/foo_output.csv";

  std::array<std::vector<char>, 5> argv__;
  std::transform(arguments.begin(), arguments.end(), argv__.begin(), [](std::string const& v){
      std::vector<char> chars(v.begin(), v.end());
      chars.push_back('\0');
      return chars;});
  std::array<char*, 5> argv;
  std::transform(argv__.begin(), argv__.end(), argv.begin(), [](std::vector<char>& v){return &*v.begin();});
  int argc{5};

  std::vector<std::string> actual = ConvertToStrings(argc, &*argv.begin());
  std::vector<std::string> expect(arguments.begin(), arguments.end());
  EXPECT_THAT(actual, Eq(expect));
}

TEST(CsvColumnReplacer, WhenNoArgumentsThenReturnAndErrorMessage)
{
  std::vector<std::string> arguments;
  std::ostringstream output_stream;
  Runner unit{arguments, output_stream};
  unit.Do();
  EXPECT_THAT(output_stream.str(), Eq(std::string{"Not enough input arguments"}));
}
TEST(CsvColumnReplacer, WhenNoInputFileThenReturnAndErrorMessage)
{
  std::vector<std::string> arguments{"executable name", "data/no_file.csv", "foo_column", "replacement", "data/output.csv"};
  std::ostringstream output_stream;
  Runner unit{arguments, output_stream};
  unit.Do();
  EXPECT_THAT(output_stream.str(), Eq(std::string{"Input file missing"}));
}
TEST(CsvColumnReplacer, WhenEmptyFileThenReturnAndErrorMessage)
{
  std::vector<std::string> arguments{"executable name", "csv/test/data/empty_file.csv", "foo_column", "replacement", "data/output.csv"};
  std::ostringstream output_stream;
  Runner unit{arguments, output_stream};
  unit.Do();
  EXPECT_THAT(output_stream.str(), Eq(std::string{"Input file is empty"}));
}
using Csv = std::vector<std::string>;

std::vector<std::string> Split(const std::string& str, char delim = ' ')
{
    std::stringstream ss(str);
    std::string token;
    std::vector<std::string> output;
    while (std::getline(ss, token, delim)) {
        output.push_back(token);
    }
    return output;
}
Csv ChangeColumnOf(Csv const& in, std::string column, std::string replacement)
{
  std::vector<std::vector<std::string>> table;
  std::transform(in.cbegin(), in.cend(), std::back_inserter(table), [](std::string const& line){
      return Split(line, ',');});
  auto const& headline = table.front();
  for(auto v : headline)
  {
    std::cerr << v << ";";
  }
  std::cerr << std::endl;
  auto col_count = std::distance(headline.cbegin(), std::find(headline.cbegin(), headline.cend(), column));
  std::cerr << "col count: " << col_count << std::endl;
  for(auto it = table.begin() + 1; it != table.end(); ++it)
  {
    auto column_it = it->begin();
    std::advance(column_it, col_count);
    *column_it = replacement;
  }
  
  Csv output;
  std::transform(table.cbegin(), table.cend(), std::back_inserter(output), [](auto const& line){
      std::stringstream ss;
      for(auto col : line)
      {
        ss << col << ',';
      }
      return ss.str();});

  return output;
}
TEST(CsvColumnReplacer, WhenVectorOfStringsChangeColumn)
{
  Csv csv{{"col0,col1,col2,col3"}, {"a,b,c,d"}, {"0,1,2,3"}};
  std::string column{"col1"};
  std::string replacement{"x"};

  auto actual = ChangeColumnOf(csv, column, replacement);
  
  std::vector<std::string> expect{{"col0,col1,col2,col3"}, {"a,x,c,d"}, {"0,x,2,3"}};
  EXPECT_THAT(actual, Eq(expect));
}
