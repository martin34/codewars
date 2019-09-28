#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <iterator>
#include <string>

#include "csv/csv_file.h"
#include "test_data.h"

using namespace ::testing;

TEST(CreateCopyWithReplacedColumnSpec, WhenVectorOfStringsChangeColumn) {
  Lines csv{{"col0,col1,col2,col3"}, {"a,b,c,d"}, {"0,1,2,3"}};
  std::string column{"col1"};
  std::string replacement{"x"};

  auto actual = CreateCopyWithReplacedColumn(csv, column, replacement);

  Lines expect{{"col0,col1,col2,col3"}, {"a,x,c,d"}, {"0,x,2,3"}};
  EXPECT_THAT(actual, Eq(expect));
}
TEST(CreateCopyWithReplacedColumnSpec,
     WhenVectorOfStringsDifferentLenghtChangeColumn) {
  Lines csv{{"col0,col1,col2,col3"}, {"a,b,c"}, {"0,1,2,3"}};
  std::string column{"col1"};
  std::string replacement{"x"};

  auto actual = CreateCopyWithReplacedColumn(csv, column, replacement);

  Lines expect{{"col0,col1,col2,col3"}, {"a,x,c"}, {"0,x,2,3"}};
  EXPECT_THAT(actual, Eq(expect));
}
TEST(CreateCopyWithReplacedColumnSpec,
     WhenVectorOfStringsOnlyHeadlineChangeColumn) {
  Lines csv{{"col0,col1,col2,col3"}};
  std::string column{"col1"};
  std::string replacement{"x"};

  auto actual = CreateCopyWithReplacedColumn(csv, column, replacement);

  Lines expect{{"col0,col1,col2,col3"}};
  EXPECT_THAT(actual, Eq(expect));
}
TEST(CreateCopyWithReplacedColumnSpec,
     WhenVectorOfStringsNoColumnWithNameThenDoNothing) {
  Lines csv{{"col0,col1,col2,col3"}, {"a,b,c,d"}, {"0,1,2,3"}};
  std::string column{"not_existing_name"};
  std::string replacement{"x"};

  auto actual = CreateCopyWithReplacedColumn(csv, column, replacement);

  Lines expect{{"col0,col1,col2,col3"}, {"a,b,c,d"}, {"0,1,2,3"}};
  EXPECT_THAT(actual, Eq(expect));
}
TEST(CreateCopyWithReplacedColumnSpec, WhenEmptyWithThenEmpty) {
  Lines csv{};
  std::string column{"not_existing_name"};
  std::string replacement{"x"};

  auto actual = CreateCopyWithReplacedColumn(csv, column, replacement);

  Lines expect{};
  EXPECT_THAT(actual, Eq(expect));
}
TEST(CsvFileReader, OpenEmptyFileThenGetEmptyVector) {
  auto empty_file_path = GetEmptyCsvFilePath();
  CsvFileReader empty_file(empty_file_path);
  auto lines = empty_file.GetLines();
  EXPECT_THAT(lines.empty(), Eq(true));
}
TEST(CsvFileReader, ReadFileThenExpectContent) {
  auto empty_file_path = GetShortCsvFilePath();
  CsvFileReader file(empty_file_path);
  auto lines = file.GetLines();
  Lines expected = GetShortCsvContnet();
  EXPECT_THAT(lines, Eq(expected));
}
TEST(CsvFileReader, CheckIfExistsAndReadFileThenExpectContent) {
  auto empty_file_path = GetShortCsvFilePath();
  CsvFileReader file(empty_file_path);
  EXPECT_THAT(file.Exists(), Eq(true));
  auto lines = file.GetLines();
  Lines expected = GetShortCsvContnet();
  EXPECT_THAT(lines, Eq(expected));
}
