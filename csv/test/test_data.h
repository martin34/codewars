#ifndef CSV_TEST_TEST_DATA_H_
#define CSV_TEST_TEST_DATA_H_

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

inline std::string GetEmptyCsvFileReaderPathRelative()
{
  return "csv/test/data/empty_file.csv";
}
inline fs::path GetEmptyCsvFileReaderPath(){
  return fs::absolute(GetEmptyCsvFileReaderPathRelative());
}
inline std::string GetShortCsvFileReaderPathRelative(){
  return "csv/test/data/short_file.csv";
}
inline fs::path GetShortCsvFileReaderPath(){
  return fs::absolute(GetShortCsvFileReaderPathRelative());
}
inline std::vector<std::string> GetShortCsvContnet(){
  return {{"column_0,column_1,column_2,column_3"}, {"w,x,y,z"}, {"11,12,12,14"}};
}
#endif // CSV_TEST_TEST_DATA_H_
