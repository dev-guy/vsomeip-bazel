#include "gtest/gtest.h"
#include <stdexcept>

#include "k9/algorithm.h"

namespace k9
{
namespace
{
  TEST(algorithm_builder, opeq)
  {
    algorithm_builder config;
    config.name_ = "alg";
    algorithm_builder c2;
    c2 = config;
    ASSERT_EQ(config.name_, "alg");
    ASSERT_EQ(c2.name_, "alg");
  }

  TEST(algorithm_builder, lvalue_move)
  {
    algorithm_builder config;
    algorithm alg(std::move(config));
    ASSERT_EQ(config.name_.length(), 0);
  }

  TEST(algorithm_builder, signals)
  {
    algorithm_builder config;
    config.process_pulls("SignalService?output=s1(inputs=`  vehspeed , engspeed  `)");
    const std::set<std::string> deps({"vehspeed", "engspeed"});
    ASSERT_EQ(config.dependent_signal_names_, deps);
  }

  TEST(algorithm_builder, frequency1)
  {
    algorithm_builder config;
    config.process_pulls("SignalService?output=s1(inputs=`vehspeed`,  frequency=` 10hZ, 100hz `");
    ASSERT_EQ(config.idle_.low_, absl::Milliseconds(10));
    ASSERT_EQ(config.idle_.high_, absl::Milliseconds(100));
  }

  TEST(algorithm_builder, frequency2)
  {
    algorithm_builder config;
    config.process_pulls("SignalService?output=s1(frequency=`10HZ,80Hz`");
    ASSERT_EQ(config.idle_.low_, absl::Milliseconds(12));
    ASSERT_EQ(config.idle_.high_, absl::Milliseconds(100));
  }

  TEST(algorithm_builder, frequency3)
  {
    algorithm_builder config;
    config.process_pulls("SignalService?output=s1(frequency=`1HZ,1Hz`");
    ASSERT_EQ(config.idle_.low_, absl::Milliseconds(1000));
    ASSERT_EQ(config.idle_.high_, absl::Milliseconds(1000));
  }

  TEST(algorithm_builder, frequency4)
  {
    algorithm_builder config;
    config.process_pulls("SignalService?output=s1(frequency=`  10HZ  `");
    ASSERT_EQ(config.idle_.low_, absl::Milliseconds(100));
    ASSERT_EQ(config.idle_.high_, absl::Milliseconds(100));
  }

  TEST(algorithm_builder, frequency5)
  {
    algorithm_builder config;
    config.process_pulls("SignalService?output=s1(frequency=`10hz, 100 HZ,`");
    ASSERT_EQ(config.idle_.low_, absl::Milliseconds(10));
    ASSERT_EQ(config.idle_.high_, absl::Milliseconds(100));
  }

  TEST(algorithm_builder, frequency6)
  {
    algorithm_builder config;
    config.process_pulls("SignalService?output=s1(frequency=`10 hz,`");
    config.process_pulls("SignalService?output=s1(frequency=`10         hz,,`");
    ASSERT_EQ(config.idle_.low_, absl::Milliseconds(100));
    ASSERT_EQ(config.idle_.high_, absl::Milliseconds(100));
  }

  TEST(algorithm_builder, invalid_frequency2)
  {
    algorithm_builder config;
    try
    {
      config.process_pulls("SignalService?output=s1(frequency=`0hz, 100hz`");
      ASSERT_EQ(true, false);
    }
    catch(const std::invalid_argument&)
    {
    }
  }

  TEST(algorithm_builder, invalid_frequency3)
  {
    algorithm_builder config;
    try
    {
      config.process_pulls("SignalService?output=s1(frequency=`5hz, 5000hz`");
      ASSERT_EQ(true, false);
    }
    catch(const std::invalid_argument&)
    {
    }
  }

  TEST(algorithm_builder, invalid_frequency6)
  {
    algorithm_builder config;
    try
    {
      config.process_pulls("SignalService?output=s1(frequency=` `");
      ASSERT_EQ(true, false);
    }
    catch(const std::invalid_argument&)
    {
    }
  }

  TEST(algorithm_builder, invalid_frequency5)
  {
    algorithm_builder config;
    try
    {
      config.process_pulls("SignalService?output=s1(frequency=`100 Hz, 10 Hz`");
      ASSERT_EQ(true, false);
    }
    catch(const std::invalid_argument&)
    {
    }
  }

  TEST(algorithm_builder, constructor1)
  {
    const char* name = "alg_signals";

    auto j = R"json(
{"exceeddata": { "job": 
  { "pulls": "SignalService?output=s1(  ,  inputs=`  vehspeed , engspeed  `)" }
}})json"_json;

    ASSERT_NE(j["exceeddata"], nullptr);
    algorithm_builder config(name, j);
    ASSERT_EQ(j["exceeddata"], nullptr);

    ASSERT_EQ(config.name_, name);
    const std::set<std::string> deps({"vehspeed", "engspeed"});
    ASSERT_EQ(config.dependent_signal_names_, deps);
  }

  TEST(algorithm, bad_definition1)
  {
    auto j = R"-(
{"exceeddata": {
  "job": []
}
})-"_json;

    try
    {
      algorithm_builder config("test", j);
      ASSERT_EQ(true, false);
    }
    catch(const std::invalid_argument& ex)
    {
      // std::cout << ex.what();
    }
  }

  TEST(algorithm, bad_definition2)
  {
    auto j = R"-(
{"exceeddata2": {
}
})-"_json;

    try
    {
      algorithm_builder config("test", j);
      ASSERT_EQ(true, false);
    }
    catch(const std::invalid_argument& ex)
    {
      // std::cout << ex.what();
    }
  }
} // namespace
} // namespace k9
