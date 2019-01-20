#include <string>
#include <regex>

std::string replace(std::string const& input)
{
        std::regex vowel_re("a|o|e|u|i", std::regex_constants::icase);
	auto output = std::regex_replace(input, vowel_re, "!");
	return output;
}

