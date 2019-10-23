#include <gtest/gtest.h>
#include <varlib/sqlite/sqlite.hpp>

TEST(sqlite, session) {
  using session = varlib::sqlite_v3::session;
  session s("test.db");
  ASSERT_EQ(true, s.is_initialied());
  remove("test.db");
}
