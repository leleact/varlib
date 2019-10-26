#include <chrono>
#include <gtest/gtest.h>
#include <sstream>
#include <thread>
#include <varlib/log.hpp>
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

TEST(sqlite, session) {
  session s("test.db");
  remove("test.db");
}

TEST(sqlite, stmt) {
  session s{"test.db"};

  int rc = s.exec("create table if not exists people(id TEXT primary key, name "
                  "TEXT, age int);");
  LOGI("rc = {}", rc);

  rc = s.exec("insert into people values('a', 'a', 1);");
  LOGI("rc = {}", rc);

  rc = s.exec("insert into people values('b', 'a', 1);");
  LOGI("rc = {}", rc);

  rc = s.exec("update people set name = 'b' where id = 'b';");
  LOGI("rc = {}", rc);

  stmt st(s, "select * from people where id = ? and name = :name;");
  st.bind(1, "b");
  st.bind(":name", "b");
  while ((rc = st.exec()) == varlib::sqlite_v3::stmt::ROW) {
    std::string id = st.get<std::string>(0);
    std::string name = st.get<std::string>(1);
    int age = st.get<int>(2);
    LOGI("id = {}, name = {}, age = {}", id, name, age);
  }
  remove("test.db");
}

template <typename T> class base {
public:
  void dosth() {
    T &_d = static_cast<T &>(*this);
    _d.do_sth();
  }

  static base &instance() {
    static T t;
    return t;
  }

protected:
  base() {
    T &_d = static_cast<T &>(*this);
    _d.init();
  };
  base(const base &) = delete;
  base operator=(const base &) = delete;
};

class A : public base<A> {
  friend class base<A>;
  varlib::sqlite_v3::session _M_s{"test.db"};

public:
  void init() {}
  void do_sth() { std::cout << _M_s << std::endl; }
};

TEST(sqlite, session_in_class) {
  //  A::instance().dosth();
  base<A> &b = A::instance();
  b.dosth();
  remove("test.db");
}

TEST(sqlite, thread) {

  varlib::sqlite_v3::manager<people_manager> &m =
      varlib::sqlite_v3::manager<people_manager>::instance();

  std::thread t1([]() {
    session __session{"test.db"};
    LOGI("");
    std::this_thread::sleep_for(std::chrono::seconds{1});
    LOGI("");
    __session.exec("insert into people values ('1', 1)");
    LOGI("");
  });
  std::thread t2([]() {
    session __session{"test.db"};
    LOGI("");
    std::this_thread::sleep_for(std::chrono::seconds{2});
    LOGI("");
    __session.exec("insert into people values ('2', 2)");
    LOGI("");
  });

  t1.join();
  t2.join();

  std::vector<people> vec = m.read_all<people>();
  std::for_each(vec.begin(), vec.end(), [](const people &__p) {
    LOGI("id: {}, age: {}", __p.id, __p.age);
  });
}
