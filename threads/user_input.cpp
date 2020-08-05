#include <chrono>
#include <iostream>
#include <thread>

#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std::chrono_literals;

enum class Actions { End, Unknown };
std::string to_string(Actions action) {
  switch (action) {
  case Actions::End:
    return std::string{"End"};

  default:
    return std::string{"Unkown"};
  }
}
Actions from_string(std::string const &action) {
  if (action == to_string(Actions::End)) {
    return Actions::End;
  }
  return Actions::Unknown;
}

int main(int argc, char **argv) {
  po::options_description desc("Allowed options");
  desc.add_options()("help", "produce help message")(
      "stdin2stdout", "Get line from stdin and pass it to stdout");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  std::atomic<Actions> shared_line{Actions::Unknown};
  std::thread user_input_thread{[&shared_line]() {
    while (shared_line != Actions::End) {
      std::string line{};
      std::getline(std::cin, line);
      std::cout << line << '\n';
      shared_line.store(from_string(line));
    }
  }};

  // std::cout << "Continue" << '\n';
  if (vm.count("stdin2stdout")) {
    while (true) {
      // std::cout << "Step" << '\n';
      // std::cout << to_string(shared_line.load()) << '\n';
      if (shared_line == Actions::End) {
        user_input_thread.join();
        return 0;
      }
      std::this_thread::sleep_for(100ms);
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