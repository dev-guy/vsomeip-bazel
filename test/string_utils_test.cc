#include "k9/string_utils.h"
#include "gtest/gtest.h"

#include <queue>
#include <vector>

namespace k9 {
namespace {
TEST(trim, one) {
  using namespace std;

  const vector<string> original = {"abc   ", "  abc  ", "",      " abc", "a",
                                   "abc",    " abc  ",  "  ab ", "  "};

  const vector<string> trimmed = {"abc", "abc", "", "abc", "a", "abc", "abc", "ab", ""};

  vector<absl::string_view> output;

  for_each(original.begin(), original.end(),
           [&output](const string &s) { output.push_back(trim(s)); });

  ASSERT_EQ(output.size(), trimmed.size());

  auto trimmed_i = trimmed.begin();
  auto output_i = output.begin();

  while (trimmed_i != trimmed.end()) {
    // cout << *trimmed_i << endl;
    // cout << *output_i << endl;
    ASSERT_EQ(*output_i, *trimmed_i);
    ++trimmed_i;
    ++output_i;
  }
}
} // namespace
} // namespace k9
