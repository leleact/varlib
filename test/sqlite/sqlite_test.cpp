#include <gtest/gtest.h>
#include <varlib/log.hpp>
#include <varlib/singleton.hpp>
#include <varlib/sqlite/sqlite.hpp>

TEST(sqlite, session) {
  using session = varlib::sqlite_v3::session;
  session s("test.db");
  remove("test.db");
}

TEST(sqlite, stmt) {

  using session = varlib::sqlite_v3::session;
  using stmt = varlib::sqlite_v3::stmt;

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
