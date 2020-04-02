
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
