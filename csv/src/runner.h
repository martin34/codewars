#ifndef CSV_SRC_RUNNER_H_
#define CSV_SRC_RUNNER_H_

#include <string>
#include <vector>

std::vector<std::string> ConvertToStrings(int argc, char** argv);


class Runner{
  public: 
    Runner(std::vector<std::string> arguments, std::ostream & output_stream);
    void Do();

    struct ErrorStrings{
      static const std::string invalid_args;
      static const std::string no_input_file;
      static const std::string empty_input_file;
      static const std::string output_exits;
    };
  private:
    std::vector<std::string> arguments_;
    std::ostream & output_stream_;

};

#endif // CSV_SRC_RUNNER_H_
