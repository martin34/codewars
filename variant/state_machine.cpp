#include "state_machine.h"

namespace variant {
std::shared_ptr<IState> Init::Next(const Context &context) {
  if (context.IsErrorDetected()) {
    return std::make_shared<Error>();
  }
  if (context.IsReady()) {
    return std::make_shared<Ready>();
  }
  return std::make_shared<Init>(*this);
}
std::shared_ptr<IState> Ready::Next(const Context &context) {
  if (context.IsErrorDetected()) {
    return std::make_shared<Error>();
  }
  if (!context.IsReady()) {
    return std::make_shared<Init>();
  }
  if (context.IsButtonPressed()) {
    return std::make_shared<Active>();
  }
  return std::make_shared<Ready>(*this);
}
std::shared_ptr<IState> Active::Next(const Context &context) {
  if (context.IsErrorDetected()) {
    return std::make_shared<Error>();
  }
  return std::make_shared<Active>(*this);
}
std::shared_ptr<IState> Error::Next(const Context &context) {
  if (!context.IsErrorDetected()) {
    return std::make_shared<Init>();
  }
  return std::make_shared<Error>(*this);
}
} // namespace variant