#pragma once

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <deque>
#include <map>
#include <vector>

namespace MatrixPipeline::Utils {

inline float calculate_frame_rate(std::size_t frame_count,
                                  std::chrono::milliseconds actual_duration,
                                  std::chrono::milliseconds window_duration) {
  auto duration = std::chrono::duration<float>(window_duration);
  if (actual_duration < window_duration &&
      actual_duration > std::chrono::milliseconds::zero()) {
    duration = std::chrono::duration<float>(actual_duration);
  }
  const float seconds = duration.count();
  return frame_count > 1 && seconds > 0.0f
             ? static_cast<float>(frame_count - 1) / seconds
             : 0.0f;
}

using FrameTimestamp = std::chrono::time_point<std::chrono::steady_clock,
                                               std::chrono::milliseconds>;

inline float update_fps(std::deque<FrameTimestamp> &timestamps,
                        FrameTimestamp now, std::chrono::milliseconds window) {
  timestamps.push_back(now);
  while (timestamps.size() > 1 && now - timestamps.front() > window)
    timestamps.pop_front();
  return calculate_frame_rate(timestamps.size(), now - timestamps.front(),
                              window);
}

inline std::map<double, long long>
calculate_percentiles(std::vector<long long> values,
                      const std::vector<double> &percentiles) {
  if (values.empty())
    return {};

  std::sort(values.begin(), values.end());
  std::map<double, long long> results;
  for (double p : percentiles) {
    const double valid_p = std::max(0.0, std::min(1.0, p));
    const auto index = static_cast<std::size_t>(valid_p * (values.size() - 1));
    results[p] = values[index];
  }
  return results;
}

} // namespace MatrixPipeline::Utils
