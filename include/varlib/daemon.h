#pragma once

#ifndef _VARLIB_DAEMON_H
#define _VARLIB_DAEMON_H

#include "varlib.h"
#include <csignal>
#include <cstdlib>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

VARLIB_NAMESPACE_BEGIN
class daemon {

public:
  daemon(const std::string &__chdir = "/", const uint &__mask = 0)
      : _M_chdir(__chdir), _M_mask(__mask) {
    _M_init();
  }

private:
  daemon(const daemon &) = delete;
  daemon &operator=(const daemon &) = delete;

  std::string _M_chdir;
  uint _M_mask;
  int _M_pid;
  int _M_sid;

  void _M_init() {
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
      exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
      exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if ((_M_sid = setsid()) < 0)
      exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    // TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    _M_pid = fork();

    /* An error occurred */
    if (_M_pid < 0)
      exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (_M_pid > 0)
      exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(_M_mask);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir(_M_chdir.c_str());

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
      close(x);
    }
  }
};

VARLIB_NAMESPACE_END

#endif
