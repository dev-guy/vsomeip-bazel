#include "gtest/gtest.h"
#include "k9/logger.h"
#include "k9/app.h"

 #include "spdlog/spdlog.h"
 #include <memory>

namespace k9 {
namespace {
TEST(App, one) {
  ASSERT_EQ(app_, nullptr);
  app::start();
  ASSERT_NE(app_, nullptr);

  auto logger = spdlog::get("default");
  logger->info("what");

  app::stop();
  ASSERT_EQ(app_, nullptr);
}
}  // namespace 
}  // namespace k9
