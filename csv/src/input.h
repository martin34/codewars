#ifndef CSV_SRC_INPUT_H_
#define CSV_SRC_INPUT_H_

#include <string>
#include <vector>

std::vector<std::string> ConvertToStrings(int argc, char** argv);

class Runner{
  public: 
    Runner(std::vector<std::string> arguments, std::ostream & output_stream);
    void Do();

  private:
    std::vector<std::string> arguments_;
    std::ostream & output_stream_;

};

#endif // CSV_SRC_INPUT_H_
