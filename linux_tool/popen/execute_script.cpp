#include <iostream>
#include <stdio.h>

int main() {
  auto script_input_stream = popen("./script.sh", "w");
  if (script_input_stream == nullptr) {
    std::cerr << __PRETTY_FUNCTION__ << " Error during popen" << '\n';
  }

  std::string output{"bar"};
  for (const auto c : output) {
    fputc(c, script_input_stream);
  }
  fputc('\n', script_input_stream);

  pclose(script_input_stream);
}
