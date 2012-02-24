#include "Ticker.h"
#include "Timestamp.h"
#include <event2/event.h>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

Ticker::Ticker (
    void
) {}

Ticker::~Ticker (
    void
) {}

static void
listen_callback (
    evutil_socket_t listen_fd,
    short what,
    void *arg) {

  std::cerr << "listen_callback" << std::endl;

  struct sockaddr_storage ss;
  socklen_t slen = sizeof(ss);

  int fd = accept(listen_fd, (struct sockaddr *)&ss, &slen);

  if (fd < 0) {

    std::cerr << "accept() failed." << std::endl;
  }
  else {

    std::string response(Timestamp::instance().timestamp());

    write(fd, response.c_str(), response.length());
    close(fd);
  }
}

void
Ticker::run (
    unsigned short port,
    int backlog
) const {

  // socket()

  evutil_socket_t sockfd = socket(AF_INET, SOCK_STREAM, 0);
  evutil_make_socket_nonblocking(sockfd);

  // sockaddr_in

  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  // bind()

  if (bind(
        sockfd,
        reinterpret_cast< struct sockaddr * >(&servaddr),
        sizeof(servaddr)) < 0) {

    std::cerr << "bind() failed." << std::endl;

    return;
  }

  // listen()

  if (listen(sockfd, backlog) < 0) {

    std::cerr << "linten() failed." << std::endl;

    return;
  }

  // event_base_new()

  struct event_base *base = event_base_new();

  if (!base) {

    std::cerr << "event_base_new() failed." << std::endl;

    return;
  }

  // event_new() / event_add()

  struct event *read_event = event_new(
      base,
      sockfd,
      EV_READ | EV_PERSIST,
      listen_callback,
      (void *)base);

  event_add(read_event, NULL);

  // event_base_dispatch()

  event_base_dispatch(base);
}
