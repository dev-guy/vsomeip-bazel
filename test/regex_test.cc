#include "gtest/gtest.h"
#include <regex> 

namespace k9 {
namespace {
TEST(Regex, one) {
  using namespace std;

  string a = " GeekGeekForGeeks"; 

  // Here b is an object of regex (regular expression) 
  regex b("^\\s(Geek)+([^s]+)s$");

  // regex_match function for matching a range in string  
  // against regex b 
  sregex_iterator it = sregex_iterator(a.begin(), a.end(), b); 
  for(; it != sregex_iterator(); it++) {
    smatch match = *it;
    cout << it->str(1) << endl;
  }
}

TEST(Regex, two) {
  using namespace std;

  regex inputs_rex("^SignalService\\?.*?output=[^(]+\\(.*?inputs=`([^`]+)`");
  regex frequency_rex("^SignalService\\?.*?output=[^(]+\\(.*?frequency=`([^`]+)`");

  string a("SignalService?output=s1(inputs=`vehspeed,engspeed`, frequency=`10hz,10hz`)");
  smatch match;
  if (regex_search(a, match, inputs_rex)) {
    cout << match.str(1) << endl;
  }
  else {
    ASSERT_EQ(true, false);
  }
  if (regex_search(a, match, frequency_rex)) {
    cout << match.str(1) << endl;
  }
  else {
    ASSERT_EQ(true, false);
  }

  // string inputs("SignalService?output=s1(inputs=`vehspeed,engspeed`, frequency=`10hz,10hz`)");
}
}  // namespace 
}  // namespace k9
  