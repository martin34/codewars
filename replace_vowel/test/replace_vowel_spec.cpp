#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>
#include <iostream>

#include "replace_vowel/src/replace_vowel.h"

using namespace ::testing;

TEST(ReplaceVowelSpec, NoVowelInWordThanChangeNothing)
{
	std::string input{"cdf"};
	auto output = replace(input);
	EXPECT_THAT(output, Eq(input));
}
TEST(ReplaceVowelSpec, WhenaInWordThanReplaceIt)
{
	std::string input{"acdf"};
	auto output = replace(input);
	EXPECT_THAT(output, Eq("!cdf"));
}
TEST(ReplaceVowelSpec, WhenAInWordThanReplaceIt)
{
	std::string input{"Acdf"};
	auto output = replace(input);
	EXPECT_THAT(output, Eq("!cdf"));
}
