#include "state_machine.h"

namespace variant {

namespace variant {
State Transition(const Init &init, const Context &context) {
  if (context.IsErrorDetected()) {
    return State{Error{}};
  }
  if (context.IsReady()) {
    return State{Ready{}};
  }
  return State{init};
}
State Transition(const Ready &current, const Context &context) {
  if (context.IsErrorDetected()) {
    return State{Error{}};
  }
  if (!context.IsReady()) {
    return State{Init{}};
  }
  if (context.IsButtonPressed()) {
    return State{Active{}};
  }
  return State{current};
}
State Transition(const Active &current, const Context &context) {
  if (context.IsErrorDetected()) {
    return State{Error{}};
  }
  if (context.IsButtonPressed()) {
    return State{Ready{}};
  }
  return State{current};
}
State Transition(const Error &current, const Context &context) {
  if (!context.IsErrorDetected() && context.IsButtonPressed()) {
    return State{Init{}};
  }
  return State{current};
}
} // namespace variant
namespace polymorphic {
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
  if (context.IsButtonPressed()) {
    return std::make_shared<Ready>();
  }
  return std::make_shared<Active>(*this);
}
std::shared_ptr<IState> Error::Next(const Context &context) {
  if (!context.IsErrorDetected() && context.IsButtonPressed()) {
    return std::make_shared<Init>();
  }
  return std::make_shared<Error>(*this);
}
} // namespace polymorphic
} // namespace variant