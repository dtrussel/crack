
#include <gtest/gtest.h>

#include <set>

/// Question 1.1

bool has_only_unique(std::string input){
  bool ret = true;
  std::set<char> uniques{};
  for (const auto character : input){
    auto insertion = uniques.insert(character);
    if (not insertion.second) {
      ret = false;
      break;
    }
  }
  return ret;
}

TEST(Arrays_and_Strings, Question_1_1) {
    EXPECT_TRUE(has_only_unique("ab"));
    EXPECT_TRUE(has_only_unique("abcdefg"));
    EXPECT_TRUE(has_only_unique("qwertyuiop"));
    EXPECT_FALSE(has_only_unique("aa"));
    EXPECT_FALSE(has_only_unique("bcdb"));
}

/// Question 1.2

bool is_permutation(std::string one, std::string other){
  return std::is_permutation(one.begin(), one.end(), other.begin());
}

TEST(Arrays_and_Strings, Question_1_2) {
  EXPECT_TRUE(is_permutation("ab", "ba"));
  EXPECT_TRUE(is_permutation("abcdefg", "bcdefga"));
  EXPECT_FALSE(is_permutation("ab", "ac"));
  EXPECT_FALSE(is_permutation("abcdefg", "abcdefh"));
}

/// Question 1.3

std::string urlify(std::string input){
  std::string ret;
  ret.reserve(input.size() + 3 * std::count(input.begin(), input.end(), ' '));
  auto start = input.begin();
  while (start != input.end()) {
    auto next_space = std::find(start, input.end(), ' ');
    if (next_space != input.end()) {
      ret += std::string(start, next_space) + "%20";
      start = next_space + 1;
    } else {
      ret += std::string(start, next_space);
      start = next_space;
    }
  }
  return ret;

}

TEST(Arrays_and_Strings, Question_1_3) {
  EXPECT_EQ("abc", urlify("abc"));
  EXPECT_EQ("a%20b%20c", urlify("a b c"));
  EXPECT_EQ("%20%20%20", urlify("   "));
  EXPECT_EQ("%20a%20b%20c", urlify(" a b c"));
}

/// Question 1.4

bool is_palindrom(const std::string& input){
  bool ret = true;
  auto front = input.begin();
  auto back = input.end() - 1;
  while (front < back) {
    if (*front++ != *back--) {
      ret = false;
      break;
    }
  }
  return ret;
}

std::vector<std::string> get_palindrom_permutations(std::string input){
  auto end = std::remove(input.begin(), input.end(), ' ');
  input.erase(end, input.end());
  std::transform(input.begin(), input.end(), input.begin(), [](char c) { return std::tolower(c); });
  std::sort(input.begin(), input.end());
  std::vector<std::string> ret;
  bool has_next = true;
  while (has_next) {
    has_next = std::next_permutation(input.begin(), input.end());
    if (is_palindrom(input)) {
      ret.push_back(input);
    }
  }
  return ret;
}

TEST(Arrays_and_Strings, Question_1_4) {
  EXPECT_TRUE(is_palindrom("abcdcba"));
  EXPECT_TRUE(is_palindrom("aba"));
  EXPECT_TRUE(is_palindrom("abba"));
  EXPECT_FALSE(is_palindrom("abcdcb"));
  auto pals = get_palindrom_permutations("Tact coa");
  EXPECT_EQ(pals.size(), 6);
  pals = get_palindrom_permutations("abcdefg");
  EXPECT_EQ(pals.size(), 0);
}
