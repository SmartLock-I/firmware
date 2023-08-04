#include <gtest/gtest.h>

#include "sli.h"

TEST(UTIL, GET_INTERVAL) {
  uint32_t current_time;
  uint32_t last_time;

  last_time = 0;
  current_time = 1;
  EXPECT_EQ(GET_INTERVAL(current_time, last_time), 1);

  last_time = 0xFFFFFFFF;
  current_time = 0x00000000;
  EXPECT_EQ(GET_INTERVAL(current_time, last_time), 1);

  last_time = 0xFFFFFFFF;
  current_time = 0x00000001;
  EXPECT_EQ(GET_INTERVAL(current_time, last_time), 2);
}
