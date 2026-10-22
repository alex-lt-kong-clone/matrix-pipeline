#include "statistics.h"

#include <gtest/gtest.h>

#include <chrono>
#include <deque>
#include <map>

namespace {

using MatrixPipeline::Utils::calculate_frame_rate;
using MatrixPipeline::Utils::calculate_percentiles;
using MatrixPipeline::Utils::FrameTimestamp;
using MatrixPipeline::Utils::update_fps;
using namespace std::chrono_literals;

TEST(FrameRate, UsesFrameIntervalsAndWindow) {
  EXPECT_FLOAT_EQ(calculate_frame_rate(11, 500ms, 1000ms), 20.0f);
  EXPECT_FLOAT_EQ(calculate_frame_rate(11, 2000ms, 1000ms), 10.0f);
}

TEST(FrameRate, HandlesInitialSamplesAndZeroWindow) {
  EXPECT_FLOAT_EQ(calculate_frame_rate(0, 0ms, 1000ms), 0.0f);
  EXPECT_FLOAT_EQ(calculate_frame_rate(1, 0ms, 1000ms), 0.0f);
  EXPECT_FLOAT_EQ(calculate_frame_rate(2, 0ms, 1000ms), 1.0f);
  EXPECT_FLOAT_EQ(calculate_frame_rate(2, 100ms, 0ms), 0.0f);
}

TEST(FrameRate, DropsFramesOutsideWindow) {
  std::deque<FrameTimestamp> timestamps;
  for (const auto t : {0ms, 500ms, 1500ms})
    update_fps(timestamps, FrameTimestamp{t}, 1000ms);
  EXPECT_EQ(timestamps.front(), FrameTimestamp{500ms});
}

TEST(FrameRate, KeepsNewestFrameWithNegativeWindow) {
  std::deque<FrameTimestamp> timestamps;
  update_fps(timestamps, FrameTimestamp{0ms}, -1ms);
  EXPECT_FLOAT_EQ(update_fps(timestamps, FrameTimestamp{100ms}, -1ms), 0.0f);
  EXPECT_EQ(timestamps.size(), 1u);
}

TEST(LatencyPercentiles, SortsSamplesAndClampsPercentiles) {
  const std::map<double, long long> expected{
      {-0.5, 10}, {0.0, 10}, {0.5, 50}, {0.9, 70}, {1.0, 90}, {1.5, 90}};
  EXPECT_EQ(calculate_percentiles({90, 10, 50, 30, 70},
                                  {-0.5, 0.0, 0.5, 0.9, 1.0, 1.5}),
            expected);
}

TEST(LatencyPercentiles, HandlesEmptyAndSingleSamples) {
  EXPECT_TRUE(calculate_percentiles({}, {0.5, 0.99}).empty());
  const std::map<double, long long> expected{{0.5, 42}, {0.99, 42}};
  EXPECT_EQ(calculate_percentiles({42}, {0.5, 0.99}), expected);
}

} // namespace
