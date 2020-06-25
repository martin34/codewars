#include <iostream>
#include <thread>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char **argv) {
  po::options_description desc("Allowed options");
  desc.add_options()("help", "produce help message")(
      "stdin2stdout", "Get line from stdin and pass it to stdout");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("stdin2stdout")) {
    while (true) {
      std::string line;
      std::thread user_input_thread{
          [&line]() { std::getline(std::cin, line); }};
      user_input_thread.join();
      std::cout << line << '\n';
    }
  } else {
    std::cout << "Foo" << '\n';
  }
  while (true) {
    // Wait for terminate
    std::string line;
    std::getline(std::cin, line);
  }
  return 0;
}