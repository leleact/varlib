#include <chrono>
#include <gtest/gtest.h>
#include <sstream>
#include <thread>
#include <varlib/log.hpp>
#include <varlib/random.hpp>
#include <varlib/singleton.hpp>
#include <varlib/sqlite/sqlite.hpp>

bool varlib::log_initialize::initialized = []() {
  spdlog::set_level(spdlog::level::trace);
  spdlog::set_pattern("[%Y-%m-%d %T.%e] [%^%l%$] [thread %t] [%s:%#::(%!)] %v");
  return true;
}();

using session = varlib::sqlite_v3::session;
using stmt = varlib::sqlite_v3::stmt;

struct people {
  std::string id;
  int age;
};

class people_manager : public varlib::sqlite_v3::manager<people_manager> {

  friend class varlib::sqlite_v3::manager<people_manager>;

  session _M_session{"test.db"};

  int _create(const people &__p) {
    std::stringstream ss;
    ss << "insert into people values ('" << __p.id << "', " << __p.age << ")";
    return _M_session.exec(ss.str());
  }

  people _read_one(const std::string &__id) {
    stmt _st{_M_session, "select * from people where id = ?"};
    _st.bind(1, __id);
    _st.exec();
    std::string _id = _st.get<std::string>(0);
    int _age = _st.get<int>(1);
    return people{_id, _age};
  }

  std::vector<people> _read_all() {
    stmt _st{_M_session, "select * from people"};
    std::vector<people> vec;
    while (stmt::ROW == _st.exec()) {
      std::string _id = _st.get<std::string>(0);
      int _age = _st.get<int>(1);
      vec.push_back(people{_id, _age});
    }
    return vec;
  }

  people_manager() {
    _M_session.exec(
        "create table if not exists people(id TEXT primary key, age INT)");
  };

  ~people_manager() { remove("test.db"); }
};

TEST(sqlite_benchmark, INSERT) {
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < 1000; i++) {
    std::stringstream ss;
    ss << i;
    people _p{ss.str(), i};
    people_manager::instance().create(_p);
  }
  auto end = std::chrono::system_clock::now();
  LOGI("time {}", (end - start).count());
}
