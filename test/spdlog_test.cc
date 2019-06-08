#include "spdlog/logger.h"
// #include "spdlog/sinks/ansicolor_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/dist_sink.h"
#include "spdlog/sinks/syslog_sink.h"
#include "gtest/gtest.h"
#include <memory>

namespace k9
{
namespace
{
  TEST(spdlog, stdout_and_syslog)
  {
    // auto syslog_sink = std::make_shared<spdlog::sinks::syslog_sink>("please.help.me");
    // auto console_sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
    auto syslog_sink = std::make_shared<spdlog::sinks::syslog_sink_st>("please.help.me");
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();

    auto dist_sink = std::make_shared<spdlog::sinks::dist_sink_st>();
    dist_sink->add_sink(syslog_sink);
    dist_sink->add_sink(console_sink);

    auto logger = std::make_shared<spdlog::logger>("my_logger", dist_sink);
    logger->set_level(spdlog::level::info);
    logger->error("error");
    logger->info("info");
    logger->debug("debug");
    logger->flush();
  }
} // namespace
} // namespace k9
