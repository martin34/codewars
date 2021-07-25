#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main(int, char **) { std::this_thread::sleep_for(10s); }
