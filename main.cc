#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <iostream>
#include <cstdio>
#include <cstring>

static const size_t const MAX_LINE = 1 << 14;

const std::string responseString (void) {

  return std::string("ok?");
}

void listen_callback(
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

    std::string response(responseString());

    write(fd, response.c_str(), response.length());
    close(fd);
  }
}

void run (uint16_t port) {

  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = 0;
  sin.sin_port = htons(port);

  evutil_socket_t read_fd = socket(AF_INET, SOCK_STREAM, 0);
  evutil_make_socket_nonblocking(read_fd);

  // bind()

  if (bind(read_fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {

    std::cerr << "bind() failed." << std::endl;

    return;
  }

  // listen()

  if (listen(read_fd, 16) < 0) {

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
      read_fd,
      EV_READ | EV_PERSIST,
      listen_callback,
      (void *)base);

  event_add(read_event, NULL);

  // event_base_dispatch()

  event_base_dispatch(base);
}

int main (
  int argc,
  char **argv) {

  setvbuf(stdout, NULL, _IONBF, 0);

  run(8888);

  return 0;
}
