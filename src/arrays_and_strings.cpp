#include <gtest/gtest.h>

#include <set>
#include <list>

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
  std::transform(input.begin(), input.end(), input.begin(),
                 [](char c) { return std::tolower(c); });
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

/// Question 1.5

// returns how many chars of `big` are missing from `small`
unsigned num_of_removed_chars(const std::string& big,
                              const std::string& small){
  unsigned num_diff = 0;
  auto bit = big.begin();
  auto sit = small.begin();
  while ((sit != small.end()) and (bit != big.end())) {
    if (*bit != *sit) { ++num_diff; }
    else              { ++sit; }
    ++bit;
  }
  return num_diff + std::distance(bit, big.end());
}

unsigned num_of_altered_chars(const std::string& alpha,
                              const std::string& beta){
  assert(alpha.size() == beta.size());
  unsigned num_alter = 0;
  auto ait = alpha.begin();
  auto bit = beta.begin();
  while ((ait != alpha.end()) and (bit != beta.end())) {
    if (*bit != *ait) { ++num_alter; }
    ++ait;
    ++bit;
  }
  return num_alter;
}

bool is_max_one_edit_away(std::string alpha, std::string beta){
  bool ret = false;
  if (alpha == beta) {
    ret = true;
  } else {
    if (alpha.size() == beta.size()) {
      ret = (1 == num_of_altered_chars(alpha, beta));
    } else {
      if (alpha.size() < beta.size()) { std::swap(alpha, beta); }
      ret = (1 == num_of_removed_chars(alpha, beta));
    }
  }
  return ret;
}

TEST(Arrays_and_Strings, Question_1_5) {
  EXPECT_EQ(num_of_removed_chars("abc", "ac"), 1);
  EXPECT_EQ(num_of_removed_chars("abc", "abc"), 0);
  EXPECT_EQ(num_of_removed_chars("abc", "a"), 2);
  EXPECT_EQ(num_of_removed_chars("abc", "bc"), 1);
  EXPECT_EQ(num_of_removed_chars("bc", "a"), 2);

  EXPECT_EQ(num_of_altered_chars("abc", "azc"), 1);
  EXPECT_EQ(num_of_altered_chars("abc", "ayz"), 2);
  EXPECT_EQ(num_of_altered_chars("abc", "xyz"), 3);

  EXPECT_TRUE(is_max_one_edit_away("abc", "ab"));
  EXPECT_TRUE(is_max_one_edit_away("ab", "abc"));
  EXPECT_TRUE(is_max_one_edit_away("abc", "bc"));
  EXPECT_TRUE(is_max_one_edit_away("ac", "abc"));
  EXPECT_TRUE(is_max_one_edit_away("abc", "abc"));
  EXPECT_TRUE(is_max_one_edit_away("abc", "azc"));
  EXPECT_FALSE(is_max_one_edit_away("aa", "bb"));
  EXPECT_FALSE(is_max_one_edit_away("ab", "abcd"));
}

// Question 1.6

std::string compress(const std::string& input){
  std::string ret = "";
  char current = input.at(0);
  unsigned num_reps = 1;
  for (auto it = input.begin() + 1; it < input.end(); ++it) {
     if (current != *it){
       ret += current + std::to_string(num_reps);
       current = *it;
       num_reps = 1;
     } else {
        ++num_reps;
     }
  }
  ret += current + std::to_string(num_reps);
  if (ret.size() > input.size()) { ret = input; }
  return ret;
}

TEST(Arrays_and_Strings, Question_1_6) {
  EXPECT_EQ(compress("abc"), "abc");
  EXPECT_EQ(compress("aaa"), "a3");
  EXPECT_EQ(compress("aabb"), "a2b2");
  EXPECT_EQ(compress("abbbcc"), "a1b3c2");
  EXPECT_EQ(compress("aab"), "aab");
}

// Question 1.7

using Pixel = std::array<char, 4>;

template <typename T, std::size_t N, std::size_t M = N>
using Matrix = std::array<std::array<T, M>, N>;

template <typename T, std::size_t N>
inline
Matrix<T, N> rotate90degree(const Matrix<T, N>& input){
  Matrix<T, N> ret;
  for (std::size_t row = 0; row < N; ++row) {
    for (std::size_t col = 0; col < N; ++col) {
      ret.at(row).at(col) = input.at(col).at(N - 1 - row);
    }
  }
  return ret;
}

TEST(Arrays_and_Strings, Question_1_7) {
  Matrix<int, 3> in({
    {{1, 2, 5},
     {3, 4, 6},
      9, 7, 8} });
  Matrix<int, 3> out({
    {{5, 6, 8},
     {2, 4, 7},
     {1, 3, 9}} });
  EXPECT_EQ(rotate90degree(in), out);
}

// Question 1.8

using IndexList = std::list<std::pair<std::size_t, std::size_t>>;

template <typename T, std::size_t N,std::size_t M>
void erase_row_col(Matrix<T, N, M>& input, const IndexList& indices){
  for (const auto& entry : indices) {
    for (std::size_t col = 0; col < M; ++col) {
      input.at(entry.first).at(col) = 0;
    }
    for (std::size_t row = 0; row < N; ++row) {
      input.at(row).at(entry.second) = 0;
    }
  }
}

template <typename T, std::size_t N,std::size_t M>
void zero_row_col(Matrix<T, N, M>& input){
  IndexList indices;
  for (std::size_t row = 0; row < N; ++row) {
    for (std::size_t col = 0; col < M; ++col) {
      if (0 == input.at(row).at(col)) {
        indices.push_back({row, col});
      }
    }
  }
  erase_row_col(input, indices);
}

TEST(Arrays_and_Strings, Question_1_8) {
  Matrix<int, 3> in({
    {{1, 2, 5},
     {3, 4, 0},
      9, 7, 8} });
  Matrix<int, 3> out({
    {{1, 2, 0},
     {0, 0, 0},
      9, 7, 0} });
  zero_row_col(in);
  EXPECT_EQ(in, out);
}

// Question 1.9

bool is_substring(const std::string& whole, const std::string& word){
  bool ret = false;
  if (whole.find(word) != std::string::npos) {
    ret = true;
  }
  return ret;
}

bool is_rotation_of(const std::string& alpha, const std::string& beta){
  const auto gamma = alpha + alpha;
  return is_substring(gamma, beta);
}

TEST(Arrays_and_Strings, Question_1_9) {
  EXPECT_TRUE(is_rotation_of("erbottlewat", "waterbottle"));
  EXPECT_TRUE(is_rotation_of("abc", "cab"));
  EXPECT_TRUE(is_rotation_of("a", "a"));
  EXPECT_FALSE(is_rotation_of("abc", "def"));
}
