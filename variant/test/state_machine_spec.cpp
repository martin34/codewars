#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "variant/state_machine.h"

namespace {

namespace b {
using variant::Context;
using namespace testing;
using namespace variant::variant;

// Init
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
TEST(StateMachine, InitWhenButtonPressed) {
  StateMachine unit{};
  Context c{false, true, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Init>(state), Eq(true));
}
TEST(StateMachine, WhenInitStateAndError) {
  StateMachine unit{Init{}};
  Context c{false, true, true};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Error>(state), Eq(true));
}
// Ready
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
TEST(StateMachine, WhenReadyStateAndNoReadyCondition) {
  StateMachine unit{Ready{}};
  Context c{false, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Init>(state), Eq(true));
}
TEST(StateMachine, WhenReadyStateNoReadyConditionAndButtonPressed) {
  StateMachine unit{Ready{}};
  Context c{false, true, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Init>(state), Eq(true));
}
TEST(StateMachine, WhenReadyStateAndError) {
  StateMachine unit{Ready{}};
  Context c{false, true, true};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Error>(state), Eq(true));
}
// Active
TEST(StateMachine, WhenActiveStateAndError) {
  StateMachine unit{Active{}};
  Context c{false, true, true};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Error>(state), Eq(true));
}
TEST(StateMachine, WhenActiveAndButtonPressed) {
  StateMachine unit{Active{}};
  Context c{false, true, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Ready>(state), Eq(true));
}
// Error
TEST(StateMachine, WhenErrorStateNoError) {
  StateMachine unit{Error{}};
  Context c{false, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Error>(state), Eq(true));
}
TEST(StateMachine, WhenErrorStateNoErrorAndButtonPressed) {
  StateMachine unit{Error{}};
  Context c{false, true, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(std::holds_alternative<Init>(state), Eq(true));
}
} // namespace b

namespace a {

using namespace testing;
using variant::Context;
using namespace variant::polymorphic;

// Init
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
TEST(StateMachine, InitWhenButtonPressed) {
  StateMachine unit{};
  Context c{false, true, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Init"));
}
TEST(StateMachine, WhenInitStateAndError) {
  StateMachine unit{std::make_shared<Init>()};
  Context c{false, true, true};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Error"));
}
// Ready
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
  Context c{false, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Init"));
}
TEST(StateMachine, WhenReadyStateNoReadyConditionAndButtonPressed) {
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
// Active
TEST(StateMachine, WhenActiveStateAndError) {
  StateMachine unit{std::make_shared<Active>()};
  Context c{false, true, true};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Error"));
}
TEST(StateMachine, WhenActiveAndButtonPressed) {
  StateMachine unit{std::make_shared<Active>()};
  Context c{false, true, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Ready"));
}
// Error
TEST(StateMachine, WhenErrorStateNoError) {
  StateMachine unit{std::make_shared<Error>()};
  Context c{false, false, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Error"));
}
TEST(StateMachine, WhenErrorStateNoErrorAndButtonPressed) {
  StateMachine unit{std::make_shared<Error>()};
  Context c{false, true, false};
  unit.Update(c);
  auto state = unit.GetState();
  EXPECT_THAT(state->GetName(), Eq("Init"));
}
} // namespace a
} // namespace
