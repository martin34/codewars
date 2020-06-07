#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "variant/state_machine.h"

namespace {
namespace a {

using namespace testing;
using variant::Context;
using namespace variant::polymorphic;

TEST(StateMachine, InitialState) {
  StateMachine unit{};
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Init"));
}
TEST(StateMachine, WhenNoTransition) {
  StateMachine unit{};
  Context c{false, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Init"));
}
TEST(StateMachine, InitialToReady) {
  StateMachine unit{};
  Context c{true, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Ready"));
}
TEST(StateMachine, ReadyAndStayInReady) {
  StateMachine unit{std::make_shared<Ready>()};
  Context c{true, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Ready"));
}
TEST(StateMachine, WhenReadyAndActiveConditionsMet) {
  StateMachine unit{std::make_shared<Ready>()};
  Context c{true, true, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Active"));
}
TEST(StateMachine, WhenReadyStateAndNoReadyCondition) {
  StateMachine unit{std::make_shared<Ready>()};
  Context c{false, true, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Init"));
}
TEST(StateMachine, WhenReadyStateAndError) {
  StateMachine unit{std::make_shared<Ready>()};
  Context c{false, true, true};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Error"));
}
TEST(StateMachine, WhenActiveStateAndError) {
  StateMachine unit{std::make_shared<Active>()};
  Context c{false, true, true};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Error"));
}
TEST(StateMachine, WhenInitStateAndError) {
  StateMachine unit{std::make_shared<Init>()};
  Context c{false, true, true};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Error"));
}
TEST(StateMachine, WhenErrorStateAndNoError) {
  StateMachine unit{std::make_shared<Error>()};
  Context c{false, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Init"));
}
} // namespace a
} // namespace

namespace {
namespace b {
using variant::Context;
using namespace testing;
using namespace variant::variant;

TEST(StateMachine, InitialState) {
  StateMachine unit{};
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Init>(state), Eq(true));
}
TEST(StateMachine, WhenNoTransition) {
  StateMachine unit{};
  Context c{false, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Init>(state), Eq(true));
}
TEST(StateMachine, InitialToReady) {
  StateMachine unit{};
  Context c{true, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Ready>(state), Eq(true));
}
TEST(StateMachine, ReadyAndStayInReady) {
  StateMachine unit{Ready{}};
  Context c{true, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Ready>(state), Eq(true));
}
TEST(StateMachine, WhenReadyAndActiveConditionsMet) {
  StateMachine unit{Ready{}};
  Context c{true, true, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Active>(state), Eq(true));
}
} // namespace b
} // namespace