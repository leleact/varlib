#pragma once

#ifndef _SQLITE_H
#define _SQLITE_H

#include <cstring>
#include <iostream>
#include <memory>
#include <sqlite3.h>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <varlib/varlib.h>
#include <vector>

VARLIB_NAMESPACE_BEGIN

namespace sqlite_v3 {

class sqlite_exception : public std::runtime_error {
public:
  sqlite_exception(const int &__rc, const std::string &__errMsg)
      : runtime_error(__errMsg.c_str()), _M_sqlite_rc(__rc),
        _M_sqlite_msg(__errMsg){};

private:
  int _M_sqlite_rc;
  std::string _M_sqlite_msg;
};

class session;
class stmt;

struct util {
  static inline void check(const session &__s, const int &__rc);
};

class session {
  friend class stmt;

  friend std::ostream &operator<<(std::ostream &__os, const session &__s) {
    __os << "_M_db_location: " << __s._M_db_location;
    return __os;
  }

public:
  session(const std::string &__location)
      : _M_db_location(__location), _M_conn(nullptr) {
    _M_open_db();
  }

  session(const session &__session) : _M_db_location(__session._M_db_location) {
    _M_open_db();
  }

  session(session &&__session)
      : _M_db_location(std::move(__session._M_db_location)),
        _M_conn(std::exchange(__session._M_conn, nullptr)) {}

  session &operator=(const session &__session) {
    _M_close_db();
    _M_db_location = __session._M_db_location;
    _M_open_db();
    return *this;
  }

  session &operator=(session &&__session) {
    _M_close_db();
    _M_db_location = std::move(__session._M_db_location);
    _M_conn = std::exchange(__session._M_conn, nullptr);
    return *this;
  }

  ~session() { _M_close_db(); }

  inline const int exec(const char *__str) const {
    const int &__rc = sqlite3_exec(_M_conn, __str, nullptr, nullptr, nullptr);
    util::check(*this, __rc);
    return sqlite3_changes(_M_conn);
  }

  inline const int exec(const std::string &__str) const {
    return exec(__str.c_str());
  }

  bool is_exists(const std::string &__table) const;

  stmt statment(const std::string &__str) const;

  const int changes() const { return sqlite3_changes(_M_conn); }

  const int err_code() const { return sqlite3_errcode(_M_conn); }

  const char *err_msg() const { return sqlite3_errmsg(_M_conn); }

  const std::string db_location() const { return _M_db_location; }

private:
  std::string _M_db_location;
  sqlite3 *_M_conn;

  inline void _M_open_db() {
    int __rc = sqlite3_open(_M_db_location.c_str(), &_M_conn);
    if (__rc != SQLITE_OK) {
      throw sqlite_exception{__rc, nullptr};
    }
  }

  inline void _M_close_db() { sqlite3_close(_M_conn); }
};

template <typename T> struct ret_type {
  using type = T;
  using const_type = const T;
  using collection_type = std::vector<T>;
};

class stmt {

public:
  enum { ROW, DONE };

  stmt(const session &__session, const std::string &__stmt)
      : _M_session(__session), _M_stmt(__stmt), _M_sqlite_stmt(nullptr) {
    _M_init_stmt();
  }

  stmt(const stmt &__stmt)
      : _M_session(__stmt._M_session), _M_stmt(__stmt._M_stmt),
        _M_sqlite_stmt(nullptr) {
    _M_init_stmt();
  }

  stmt(stmt &&__stmt)
      : _M_session(std::move(__stmt._M_session)),
        _M_stmt(std::move(__stmt._M_stmt)),
        _M_sqlite_stmt(std::exchange(__stmt._M_sqlite_stmt, nullptr)) {}

  stmt &operator=(const stmt &__stmt) {
    _M_session = __stmt._M_session;
    _M_stmt = __stmt._M_stmt;
    _M_sqlite_stmt = nullptr;
    _M_init_stmt();
    return *this;
  }

  stmt &operator=(stmt &&__stmt) {
    _M_finalize_stmt();
    _M_session = std::move(__stmt._M_session);
    _M_stmt = std::move(__stmt._M_stmt);
    _M_sqlite_stmt = std::exchange(__stmt._M_sqlite_stmt, nullptr);
    return *this;
  }
  ~stmt() { _M_finalize_stmt(); }

  template <typename I, typename T>
  inline void bind(const I &, const T &,
                   const sqlite3_destructor_type & = SQLITE_TRANSIENT);

  template <typename I, typename T>
  inline void bind(const I *, const T &,
                   const sqlite3_destructor_type & = SQLITE_TRANSIENT);

  template <typename I, typename T>
  inline void bind(const I &, const T *,
                   const sqlite3_destructor_type & = SQLITE_TRANSIENT);

  template <typename I, typename T>
  inline void bind(const I *, const T *,
                   const sqlite3_destructor_type & = SQLITE_TRANSIENT);

  template <typename I, typename T>
  inline void bind(const I &, const T *, const int &,
                   const sqlite3_destructor_type & = SQLITE_TRANSIENT);

  template <typename I, typename T>
  inline void bind(const I *, const T *, const int &,
                   const sqlite3_destructor_type & = SQLITE_TRANSIENT);

  template <typename T>
  inline const typename ret_type<T>::type get(const int &);

  inline const int get_col_count() {
    return sqlite3_column_count(_M_sqlite_stmt);
  }

  inline const int exec() {
    const int rc = sqlite3_step(_M_sqlite_stmt);
    if (rc == SQLITE_ROW) {
      return ROW;
    } else if (SQLITE_DONE == rc) {
      return DONE;
    } else {
      _M_check(rc);
    }
    return rc;
  }

  inline void reset() const {
    const int __rc = sqlite3_reset(_M_sqlite_stmt);
    _M_check(__rc);
  }

  inline void clear_bind() const {
    const int __rc = sqlite3_clear_bindings(_M_sqlite_stmt);
    _M_check(__rc);
  }

private:
  session _M_session;
  std::string _M_stmt;
  sqlite3_stmt *_M_sqlite_stmt;

  inline void _M_init_stmt() {
    int __rc = sqlite3_prepare_v2(_M_session._M_conn, _M_stmt.c_str(),
                                  _M_stmt.size(), &_M_sqlite_stmt, NULL);
    if (__rc != SQLITE_OK) {
      throw sqlite_exception{__rc, _M_session.err_msg()};
    }
  }

  inline void _M_finalize_stmt() { sqlite3_finalize(_M_sqlite_stmt); }

  inline void _M_check(const int &__rc) const {
    if (SQLITE_OK != __rc) {
      throw sqlite_exception{__rc, _M_session.err_msg()};
    }
  }
};

//{@ bind
template <>
inline void stmt::bind(const int &__index, const std::string &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int rc = sqlite3_bind_text(_M_sqlite_stmt, __index, __value.c_str(), -1,
                                   __sqlite_destructor);
  _M_check(rc);
}

template <>
inline void stmt::bind(const int &__index, const char *__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int rc = sqlite3_bind_text(_M_sqlite_stmt, __index, __value, -1,
                                   __sqlite_destructor);
  _M_check(rc);
}

template <>
inline void stmt::bind(const int &__index, const int &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  int rc = sqlite3_bind_int(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const int &__index, const unsigned &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  int rc = sqlite3_bind_int64(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const int &__index, const long &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  int rc = sqlite3_bind_int64(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const int &__index, const double &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  int rc = sqlite3_bind_double(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const std::string &__name, const std::string &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index =
      sqlite3_bind_parameter_index(_M_sqlite_stmt, __name.c_str());
  const int rc = sqlite3_bind_text(_M_sqlite_stmt, __index, __value.c_str(), -1,
                                   __sqlite_destructor);
  _M_check(rc);
}

template <>
inline void stmt::bind(const std::string &__name, const char *__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index =
      sqlite3_bind_parameter_index(_M_sqlite_stmt, __name.c_str());
  const int rc = sqlite3_bind_text(_M_sqlite_stmt, __index, __value, -1,
                                   __sqlite_destructor);
  _M_check(rc);
}

template <>
inline void stmt::bind(const std::string &__name, const int &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index =
      sqlite3_bind_parameter_index(_M_sqlite_stmt, __name.c_str());
  int rc = sqlite3_bind_int(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const std::string &__name, const unsigned &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index =
      sqlite3_bind_parameter_index(_M_sqlite_stmt, __name.c_str());
  int rc = sqlite3_bind_int64(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const std::string &__name, const long &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index =
      sqlite3_bind_parameter_index(_M_sqlite_stmt, __name.c_str());
  int rc = sqlite3_bind_int64(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const std::string &__name, const double &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index =
      sqlite3_bind_parameter_index(_M_sqlite_stmt, __name.c_str());
  int rc = sqlite3_bind_double(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const char *__name, const std::string &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index = sqlite3_bind_parameter_index(_M_sqlite_stmt, __name);
  const int rc = sqlite3_bind_text(_M_sqlite_stmt, __index, __value.c_str(), -1,
                                   __sqlite_destructor);
  _M_check(rc);
}

template <>
inline void stmt::bind(const char *__name, const char *__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index = sqlite3_bind_parameter_index(_M_sqlite_stmt, __name);
  const int rc = sqlite3_bind_text(_M_sqlite_stmt, __index, __value, -1,
                                   __sqlite_destructor);
  _M_check(rc);
}

template <>
inline void stmt::bind(const char *__name, const int &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index = sqlite3_bind_parameter_index(_M_sqlite_stmt, __name);
  int rc = sqlite3_bind_int(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const char *__name, const unsigned &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index = sqlite3_bind_parameter_index(_M_sqlite_stmt, __name);
  int rc = sqlite3_bind_int64(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const char *__name, const long &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index = sqlite3_bind_parameter_index(_M_sqlite_stmt, __name);
  int rc = sqlite3_bind_int64(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const char *__name, const double &__value,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index = sqlite3_bind_parameter_index(_M_sqlite_stmt, __name);
  int rc = sqlite3_bind_double(_M_sqlite_stmt, __index, __value);
  _M_check(rc);
}

template <>
inline void stmt::bind(const int &__index, const void *__value,
                       const int &__size,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  int rc = sqlite3_bind_blob(_M_sqlite_stmt, __index, __value, __size,
                             __sqlite_destructor);
  _M_check(rc);
}

template <>
inline void stmt::bind(const char *__name, const void *__value,
                       const int &__size,
                       const sqlite3_destructor_type &__sqlite_destructor) {
  const int __index = sqlite3_bind_parameter_index(_M_sqlite_stmt, __name);
  int rc = sqlite3_bind_blob(_M_sqlite_stmt, __index, __value, __size,
                             __sqlite_destructor);
  _M_check(rc);
}

// {@ end bind

// {@ get
template <>
inline const std::string stmt::get<std::string>(const int &__index) {
  const char *__raw_ptr = reinterpret_cast<const char *>(
      sqlite3_column_text(_M_sqlite_stmt, __index));
  const int __size = sqlite3_column_bytes(_M_sqlite_stmt, __index);
  return std::string(__raw_ptr, __size);
}

template <> inline const int stmt::get<int>(const int &__index) {
  return sqlite3_column_int(_M_sqlite_stmt, __index);
}

template <> inline const long stmt::get<long>(const int &__index) {
  return sqlite3_column_int64(_M_sqlite_stmt, __index);
}

template <> inline const double stmt::get<double>(const int &__index) {
  return sqlite3_column_double(_M_sqlite_stmt, __index);
}
// {@ end get

void util::check(const session &__s, const int &__rc) {
  if (SQLITE_OK != __rc) {
    throw sqlite_exception(__rc, __s.err_msg());
  }
}

bool session::is_exists(const std::string &__table) const {
  stmt _st{*this,
           "SELECT count(*) FROM sqlite_master WHERE type='table' AND name=?"};
  _st.bind(1, __table);
  _st.exec();
  return 1 == _st.get<int>(0);
}

stmt session::statment(const std::string &__str) const {
  return stmt(*this, __str);
}

template <typename T> class manager {

public:
  static manager &instance() {
    static T m;
    return m;
  }

  template <typename Tp> int create(Tp &&obj) {
    T &_derived = static_cast<T &>(*this);
    return _derived._create(std::forward<Tp>(obj));
  }

  template <typename R, typename... K>
  typename ret_type<R>::type read_one(K... key) {
    T &_derived = static_cast<T &>(*this);
    return _derived._read_one(std::forward<K...>(key)...);
  }

  template <typename R, typename... K>
  typename ret_type<R>::collection_type read_list(K... key) {
    T &_derived = static_cast<T &>(*this);
    return _derived._read_list(std::forward<K...>(key)...);
  }

  template <typename R> typename ret_type<R>::collection_type read_all() {
    T &_derived = static_cast<T &>(*this);
    return _derived._read_all();
  }

  template <typename... Args> int update(Args... args) {
    T &_derived = static_cast<T &>(*this);
    return _derived._update(std::forward<Args...>(args)...);
  }

  template <typename... Args> int dispose(Args... args) {
    T &_derived = static_cast<T &>(*this);
    return _derived._dispose(std::forward<Args...>(args)...);
  }

protected:
  manager() {}
  manager(const manager &) = delete;
  manager &operator<<(const manager &) = delete;
};

} // namespace sqlite_v3

VARLIB_NAMESPACE_END

#endif
