#pragma once

#ifndef _SQLITE_H
#define _SQLITE_H

#include <cstring>
#include <exception>
#include <memory>
#include <sqlite3.h>
#include <utility>
#include <varlib/varlib.h>

VARLIB_NAMESPACE_BEGIN

namespace sqlite_v3 {

enum init_state { OK = 0L, ERR = 1L << 0 };

class sqlite_exception : public std::exception {};

class session {
  friend class stmt;

public:
  session() : _M_db_location(""), _M_conn(nullptr), state(ERR) {}

  session(const std::string &__location)
      : _M_db_location(__location), _M_conn(nullptr), state(ERR) {
    _M_open_db();
  }

  session(const session &__session) : _M_db_location(__session._M_db_location) {
    _M_open_db();
  }

  session(session &&__session)
      : _M_db_location(std::move(__session._M_db_location)),
        _M_conn(std::exchange(__session._M_conn, nullptr)),
        state(std::exchange(__session.state, ERR)) {}

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
    state = std::exchange(__session.state, ERR);
    return *this;
  }

  ~session() { _M_close_db(); }

  bool is_initialied() const { return state == OK; }

protected:
  init_state state;

private:
  std::string _M_db_location;
  sqlite3 *_M_conn;

  inline void _M_open_db() {
    int rc = sqlite3_open(_M_db_location.c_str(), &_M_conn);
    if (rc == SQLITE_OK) {
      state = OK;
    } else {
      state = ERR;
    }
  }

  inline void _M_close_db() { sqlite3_close(_M_conn); }
};

class stmt {

public:
  stmt(const session &__session, const std::string &__stmt)
      : _M_session(__session), _M_stmt(__stmt), _M_sqlite_stmt(nullptr),
        _M_state(ERR) {
    _M_init_stmt();
  }

  stmt(const stmt &__stmt)
      : _M_session(__stmt._M_session), _M_stmt(__stmt._M_stmt),
        _M_sqlite_stmt(nullptr), _M_state(ERR) {
    _M_init_stmt();
  }

  stmt(stmt &&__stmt)
      : _M_session(std::move(__stmt._M_session)),
        _M_stmt(std::move(__stmt._M_stmt)),
        _M_sqlite_stmt(std::exchange(__stmt._M_sqlite_stmt, nullptr)),
        _M_state(std::exchange(__stmt._M_state, ERR)) {}

  stmt &operator=(const stmt &__stmt) {
    _M_session = __stmt._M_session;
    _M_stmt = __stmt._M_stmt;
    _M_sqlite_stmt = nullptr;
    _M_state = ERR;
    _M_init_stmt();
    return *this;
  }

  stmt &operator=(stmt &&__stmt) {
    _M_finalize_stmt();
    _M_session = std::move(__stmt._M_session);
    _M_stmt = std::move(__stmt._M_stmt);
    _M_sqlite_stmt = std::exchange(__stmt._M_sqlite_stmt, nullptr);
    _M_state = std::exchange(__stmt._M_state, ERR);
    return *this;
  }

  ~stmt() { _M_finalize_stmt(); }

  template <typename T>
  void bind(const int, T &&,
            const sqlite3_destructor_type & = SQLITE_TRANSIENT) {}

  template <>
  void bind(const int __index, const std::string &__str,
            const sqlite3_destructor_type &__sqlite_destructor) {
    const int rc = sqlite3_bind_text(_M_sqlite_stmt, __index, __str.c_str(), -1,
                                     __sqlite_destructor);
    check(rc);
  }

  template <>
  void bind(const int __index, const char *&__str,
            const sqlite3_destructor_type &__sqlite_destructor) {
    int rc = sqlite3_bind_text(_M_sqlite_stmt, __index, __str, -1,
                               __sqlite_destructor);
    check(rc);
  }

  template <>
  void bind(const int __index, const int &__value,
            const sqlite3_destructor_type &__sqlite_destructor) {
    int rc = sqlite3_bind_int(_M_sqlite_stmt, __index, __value);
    check(rc);
  }

  template <>
  void bind(const int __index, const unsigned &__value,
            const sqlite3_destructor_type &__sqlite_destructor) {
    int rc = sqlite3_bind_int64(_M_sqlite_stmt, __index, __value);
    check(rc);
  }

  template <>
  void bind(const int __index, const long &__value,
            const sqlite3_destructor_type &__sqlite_destructor) {
    int rc = sqlite3_bind_int64(_M_sqlite_stmt, __index, __value);
    check(rc);
  }

  template <>
  void bind(const int __index, const double &__value,
            const sqlite3_destructor_type &__sqlite_destructor) {
    int rc = sqlite3_bind_double(_M_sqlite_stmt, __index, __value);
    check(rc);
  }

  template <typename T>
  void bind(const int, T &&, const int,
            const sqlite3_destructor_type & = SQLITE_TRANSIENT) {}

  template <>
  void bind(const int __index, const void *&__value, const int __size,
            const sqlite3_destructor_type &__sqlite_destructor) {
    int rc = sqlite3_bind_blob(_M_sqlite_stmt, __index, __value, __size,
                               __sqlite_destructor);
    check(rc);
  }

private:
  session _M_session;
  std::string _M_stmt;
  sqlite3_stmt *_M_sqlite_stmt;
  init_state _M_state;

  inline void _M_init_stmt() {
    int rc = sqlite3_prepare_v2(_M_session._M_conn, _M_stmt.c_str(),
                                _M_stmt.size(), &_M_sqlite_stmt, NULL);
    if (rc == SQLITE_OK) {
      _M_state = OK;
    } else {
      _M_state = ERR;
    }
  }

  inline void _M_finalize_stmt() { sqlite3_finalize(_M_sqlite_stmt); }

  inline void check(const int __rc) {
    // TODO check response rc
  }
};

} // namespace sqlite_v3

VARLIB_NAMESPACE_END

#endif
