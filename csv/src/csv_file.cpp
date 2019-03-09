#include "csv_file.h"

#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <optional>

CsvFileReader::CsvFileReader(fs::path const& file_path) : in_(file_path){}

bool CsvFileReader::Exists(){
  return in_.is_open();
}

bool CsvFileReader::Empty(){
  ReadFile();
  return lines_.empty();
}

Lines CsvFileReader::GetLines()
{
  ReadFile();
  return lines_;
}

void CsvFileReader::ReadFile()
{
  std::string tmp;
  while(std::getline(in_, tmp))
  {
    if(tmp.size() > 0)
    {
      lines_.push_back(tmp);
    }
  }
}

void WriteLines(fs::path const& output_file_path, Lines const& lines)
{
  std::ofstream output_file(output_file_path);
  for(auto const& line : lines)
  {
    output_file << line << std::endl;
  }
  output_file.close();
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
bool TableIsEmpty(Table const& table)
{
  return table.cbegin() == table.cend();
}
std::optional<Table> CreateTable(Lines const& in)
{
  Table table;
  std::transform(in.cbegin(), in.cend(), std::back_inserter(table), [](std::string const& line){
      return Split(line, ',');});
  if(TableIsEmpty(table))
    return {};
  return table;
}

bool ColumnNameNotInHeadline(Lines const& headline, Lines::const_iterator col_to_replace)
{
  return col_to_replace == headline.cend();
}
void ReplaceColumnWithNameInTable(Lines::const_iterator column_to_replace, std::string const& replacement, Lines const& headline, Table& table){
auto col_count = std::distance(headline.cbegin(), column_to_replace);
  for(auto it = table.begin() + 1; it != table.end(); ++it)
  {
    auto column_it = it->begin();
    std::advance(column_it, col_count);
    *column_it = replacement;
  }
}
Lines JoinTableRows(Table const& table)
{
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


Lines CreateCopyWithReplacedColumn(Lines const& in, std::string column_name, std::string replacement)
{
  std::optional<Table> table = CreateTable(in);
  if(!table)
  {
    return in;
  }
  auto const& headline = table.value().front();
  auto column_name_in_headline = std::find(headline.cbegin(), headline.cend(), column_name);
  if(ColumnNameNotInHeadline(headline, column_name_in_headline))
  {
    return in;
  }
  ReplaceColumnWithNameInTable(column_name_in_headline, replacement, headline, table.value());
  Lines output =  JoinTableRows(table.value());
  return output;
}

