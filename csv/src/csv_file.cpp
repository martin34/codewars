#include "csv_file.h"

#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>

CsvFile::CsvFile(fs::path const& file_path) : in_(file_path){}

bool CsvFile::Exists(){
  return in_.is_open();
}

bool CsvFile::Empty(){
  std::vector<std::string> lines;
  std::string tmp;
  while(std::getline(in_, tmp))
  {
    if(tmp.size() > 0)
    {
      lines.push_back(tmp);
    }
  }
  return lines.empty();
}

Lines CsvFile::GetLines()
{
  std::vector<std::string> lines;
  std::string tmp;
  while(std::getline(in_, tmp))
  {
    if(tmp.size() > 0)
    {
      lines.push_back(tmp);
    }
  }
  return lines;
}

Lines Split(const std::string& str, char delim)
{
  std::stringstream ss(str);
  std::string token;
  Lines output;
  while (std::getline(ss, token, delim)) {
    output.push_back(token);
  }
  return output;
}

Lines CreateCopyWithReplacedColumn(Lines const& in, std::string column, std::string replacement)
{
  Table table;
  std::transform(in.cbegin(), in.cend(), std::back_inserter(table), [](std::string const& line){
      return Split(line, ',');});

  if(table.cbegin() == table.cend())
  {
    return in;
  }
  auto const& headline = table.front();
  std::cerr << "Got lines " << headline.front() << std::endl;
  auto col_to_replace = std::find(headline.cbegin(), headline.cend(), column);
  if(col_to_replace == headline.cend())
  {
    return in;
  }
  auto col_count = std::distance(headline.cbegin(), col_to_replace);
  for(auto it = table.begin() + 1; it != table.end(); ++it)
  {
    auto column_it = it->begin();
    std::advance(column_it, col_count);
    *column_it = replacement;
  }

  Lines output;
  std::transform(table.cbegin(), table.cend(), std::back_inserter(output), [](auto const& line){
      std::stringstream ss;
      for(auto col : line)
      {
      ss << col << ',';
      }
      auto new_line = ss.str();
      new_line.pop_back();
      return new_line;});

  return output;
}

void WriteLines(fs::path const& output_file_path, Lines const& lines)
{
  std::ofstream output_file("/home/martin/Desktop/abc.csv");
  for(auto const& line : lines)
  {
    output_file << line << std::endl;
  }
  output_file.close();
}
