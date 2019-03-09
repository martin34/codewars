#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <iterator>
#include <algorithm>

#include "csv/src/csv_file.h"

using namespace ::testing;

TEST(CsvColumnReplacer, WhenVectorOfStringsChangeColumn)
{
  Lines csv{{"col0,col1,col2,col3"}, {"a,b,c,d"}, {"0,1,2,3"}};
  std::string column{"col1"};
  std::string replacement{"x"};

  auto actual = CreateCopyWithReplacedColumn(csv, column, replacement);

  Lines expect{{"col0,col1,col2,col3"}, {"a,x,c,d"}, {"0,x,2,3"}};
  EXPECT_THAT(actual, Eq(expect));
}
TEST(CsvColumnReplacer, WhenVectorOfStringsDifferentLenghtChangeColumn)
{
  Lines csv{{"col0,col1,col2,col3"}, {"a,b,c"}, {"0,1,2,3"}};
  std::string column{"col1"};
  std::string replacement{"x"};

  auto actual = CreateCopyWithReplacedColumn(csv, column, replacement);

  Lines expect{{"col0,col1,col2,col3"}, {"a,x,c"}, {"0,x,2,3"}};
  EXPECT_THAT(actual, Eq(expect));
}
TEST(CsvColumnReplacer, WhenVectorOfStringsOnlyHeadlineChangeColumn)
{
  Lines csv{{"col0,col1,col2,col3"}};
  std::string column{"col1"};
  std::string replacement{"x"};

  auto actual = CreateCopyWithReplacedColumn(csv, column, replacement);

  Lines expect{{"col0,col1,col2,col3"}};
  EXPECT_THAT(actual, Eq(expect));
}
TEST(CsvColumnReplacer, WhenVectorOfStringsNoColumnWithNameThenDoNothing)
{
  Lines csv{{"col0,col1,col2,col3"}, {"a,b,c,d"}, {"0,1,2,3"}};
  std::string column{"not_existing_name"};
  std::string replacement{"x"};

  auto actual = CreateCopyWithReplacedColumn(csv, column, replacement);

  Lines expect{{"col0,col1,col2,col3"}, {"a,b,c,d"}, {"0,1,2,3"}};
  EXPECT_THAT(actual, Eq(expect));
}
TEST(CsvColumnReplacer, WhenEmptyWithThenEmpty)
{
  Lines csv{};
  std::string column{"not_existing_name"};
  std::string replacement{"x"};

  auto actual = CreateCopyWithReplacedColumn(csv, column, replacement);

  Lines expect{};
  EXPECT_THAT(actual, Eq(expect));
}
TEST(CsvFile, OpenEmptyFileThenGetEmptyVector)
{
  auto empty_file_path = fs::absolute("csv/test/data/empty_file.csv");
  CsvFile empty_file(empty_file_path);
  auto lines = empty_file.GetLines();
  EXPECT_THAT(lines.empty(), Eq(true));
}

