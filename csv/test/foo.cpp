#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <array>
#include <string>
#include <iterator>
#include <algorithm>

#include "csv/src/input.h"
#include "csv/src/csv_file.h"

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

  Lines actual = ConvertToStrings(argc, &*argv.begin());
  Lines expect(arguments.begin(), arguments.end());
  EXPECT_THAT(actual, Eq(expect));
}

TEST(RunnerSpec, WhenNoArgumentsThenReturnAndErrorMessage)
{
  Lines arguments;
  std::ostringstream output_stream;
  Runner unit{arguments, output_stream};
  unit.Do();
  EXPECT_THAT(output_stream.str(), Eq(std::string{"Not enough input arguments"}));
}
TEST(RunnerSpec, WhenNoInputFileThenReturnAndErrorMessage)
{
  Lines arguments{"executable name", "data/no_file.csv", "foo_column", "replacement", "csv/test/data/output.csv"};
  std::ostringstream output_stream;
  Runner unit{arguments, output_stream};
  unit.Do();
  EXPECT_THAT(output_stream.str(), Eq(std::string{"Input file missing"}));
}
TEST(RunnerSpec, WhenEmptyFileThenReturnAndErrorMessage)
{
  Lines arguments{"executable name", "csv/test/data/empty_file.csv", "foo_column", "replacement", "csv/test/data/output.csv"};
  std::ostringstream output_stream;
  Runner unit{arguments, output_stream};
  unit.Do();
  EXPECT_THAT(output_stream.str(), Eq(std::string{"Input file is empty"}));
}
TEST(CsvFile, OpenEmptyFileThenGetEmptyVector)
{
  auto empty_file_path = fs::absolute("csv/test/data/empty_file.csv");
  CsvFile empty_file(empty_file_path);
  auto lines = empty_file.GetLines();
  EXPECT_THAT(lines.empty(), Eq(true));
}
TEST(RunnerSpec, WhenValidFileThenExpectValidOutput)
{
  Lines arguments{"executable name", "csv/test/data/short_file.csv", "column_1", "replacement", "csv/test/data/short_output_file.csv"};
  std::ostringstream output_stream;
  Runner unit{arguments, output_stream};
  unit.Do();
  EXPECT_THAT(output_stream.str(), Eq(std::string{""}));
  auto full_output_path = fs::absolute("data/short_output_file.csv");
  CsvFile output(full_output_path);
  ASSERT_THAT(output.Exists(), Eq(true));
  auto lines = output.GetLines();
  EXPECT_THAT(lines, Eq(Lines{{"column_0,column_1,column_2,column_3"},{"w,replacement,y,z"},{"11,replacement,12,14"}}));
}

