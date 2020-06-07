#pragma once

#include <memory>
#include <string>
#include <variant>

namespace variant {

class Context {
public:
  Context(bool ready, bool b, bool c) : ready_{ready}, b_{b}, c_{c} {}
  bool IsReady() const { return ready_; }
  bool IsButtonPressed() const { return b_; }
  bool IsErrorDetected() const { return c_; }

private:
  bool ready_{};
  bool b_{};
  bool c_{};
};

namespace variant {

class Init {};
class Ready {};
class Active {};
class Error {};

using State = std::variant<Init, Ready, Active, Error>;

State Transition(const Init &init, const Context &context) {
  if (context.IsReady()) {
    return State{Ready{}};
  }
  return State{init};
}
State Transition(const Ready &current, const Context &context) {
  if (context.IsButtonPressed()) {
    return State{Active{}};
  }
  return State{current};
}
State Transition(const Active &current, const Context &) {
  return State{current};
}
State Transition(const Error &current, const Context &) {
  return State{current};
}

class StateMachine {
public:
  explicit StateMachine(State state = State{Init{}}) : state_{state} {}
  State GetState() const { return state_; }
  void Update(const Context &context) {
    state_ = std::visit(
        [&context](const auto &value) { return Transition(value, context); },
        state_);
  }

private:
  State state_{Init{}};
};

} // namespace variant

namespace polymorphic {

class IState {
public:
  virtual std::shared_ptr<IState> Next(const Context &context) = 0;
  virtual std::string GetName() = 0;
  virtual ~IState() = default;
};
class Init : public IState {
public:
  std::shared_ptr<IState> Next(const Context &context) override;

  std::string GetName() override { return "Init"; }
};
class Ready : public IState {
public:
  std::shared_ptr<IState> Next(const Context &context) override;

  std::string GetName() override { return "Ready"; }
};
class Active : public IState {
public:
  std::shared_ptr<IState> Next(const Context &context) override;

  std::string GetName() override { return "Active"; }
};
class Error : public IState {
public:
  std::shared_ptr<IState> Next(const Context &context) override;

  std::string GetName() override { return "Error"; }
};

class StateMachine {
public:
  explicit StateMachine(
      std::shared_ptr<IState> initial_state = std::make_shared<Init>())
      : state_{initial_state} {}
  std::shared_ptr<IState> GetState() { return state_; }
  void Update(const Context &context) { state_ = state_->Next(context); }

private:
  std::shared_ptr<IState> state_{std::make_shared<Init>()};
};

} // namespace polymorphic
} // namespace variant