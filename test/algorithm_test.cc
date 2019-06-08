#include "k9/algorithm.h"
#include "gtest/gtest.h"

namespace k9
{
namespace
{
  TEST(algorithm, execute1)
  {
    // The algorithm definition JSON
    auto definition(R"-(
{"exceeddata": {
   "job": {
     "pulls": "SignalService?output=s1(inputs=`vehspeed,engspeed`)"
  }
}})-"_json);

    // Create the algorithm object
    algorithm_builder builder("test_algorithm", std::move(definition));
    algorithm alg1(std::move(builder));

    // Create a vector of messages to send to the algorithm
    absl::Time now(absl::Now());
    auto message1 = R"({"engspeed": 5})";
    message::message_vector messages = {std::make_shared<message>(now, std::string(message1))};

    // Send the messages to the algorithm
    alg1.execute(messages);
  }
} // namespace
} // namespace k9
