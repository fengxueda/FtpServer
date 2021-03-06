#ifndef SESSION_H
#define SESSION_H

#if defined(__WIN32__)
#include <winsock2.h>
#include <mutex>
#elif defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#include <mutex>
#endif

#include "NetworkDriver.h"

namespace model {

class Context;

class SessionType {
 public:
  static const int kTypeUndefined = 0;
  static const int kTypeFTP = 1;
};

class Session : public NetworkDriver {
 public:
  Session()
      : sockfd_(-1),
        ip_address_(0),
        port_(0),
        timeout_(0),
        listen_sockfd_(-1),
        alive_(true) {
  }
  virtual ~Session() {

  }

  int sockfd() const {
    return sockfd_;
  }
  void set_sockfd(int sockfd) {
    sockfd_ = sockfd;
  }

  unsigned int ip_address() const {
    return ip_address_;
  }
  void set_ip_address(const unsigned int ip_address) {
    ip_address_ = ip_address;
  }

  unsigned short port() const {
    return port_;
  }
  void set_port(unsigned short port) {
    port_ = port;
  }

  int timeout() {
    return timeout_;
  }
  void set_timeout(int timeout) {
    timeout_ = timeout;
  }

  int listen_sockfd() const {
    return listen_sockfd_;
  }
  void set_listen_sockfd(const int listen_sockfd) {
    listen_sockfd_ = listen_sockfd;
  }

  void set_alive(const bool flag) {
    alive_ = flag;
  }
  bool has_alive() const {
    return alive_;
  }

  const std::mutex& mutex() const {
    return mutex_;
  }

  virtual int type() const = 0;

 private:
  int sockfd_;
  unsigned int ip_address_;
  unsigned short port_;
  int timeout_;
  int listen_sockfd_;
  bool alive_;
  std::mutex mutex_;
};

}

#endif // SESSION_H
