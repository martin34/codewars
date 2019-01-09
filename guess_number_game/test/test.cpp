#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <stdexcept>

#include "guess_number_game/src/guesser.h"

using namespace ::testing;

TEST(Guesser, WhenRightGuess_ThenReturnTrue)
{
    int number_to_guess = 2;
    int number_of_lives = 1;
    Guesser guesser{number_to_guess, number_of_lives};
    auto res = guesser.guess(number_to_guess);
    EXPECT_THAT(res, Eq(true));
}
TEST(Guesser, WhenWrongGuessAndLiveLeft_ThenReturnFalse)
{
    int number_to_guess = 2;
    int number_of_lives = 1;
    Guesser guesser{number_to_guess, number_of_lives};
    auto res = guesser.guess(number_to_guess + 1);
    EXPECT_THAT(res, Eq(false));
}
TEST(Guesser, WhenWrongGuessAndNoLiveLeft_ThenThrowError)
{
    int number_to_guess = 2;
    int number_of_lives = 0;
    Guesser guesser{number_to_guess, number_of_lives};
    EXPECT_THROW(guesser.guess(number_to_guess + 1), std::runtime_error);
}
