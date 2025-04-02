#include <sys/socket.h>
#include <sys/epoll.h>
#include <cstring>
#include "reactor.hh"
#include "../log/log.hh"

namespace arpc {

Reactor::Reactor() : m_epfd(-1), m_stop_flag(false) {}

bool Reactor::init() {
    if ((m_epfd = epoll_create(1)) <= 0) {
        LOG << "epoll_create error: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

void Reactor::loop() {
    while (!m_stop_flag) {
    }
}

void Reactor::add2Loop(arpc::FdEvent::ptr fd_event, int events) {
    epoll_event event;
    event.data.ptr = fd_event.get();
    event.events = events;

    if (epoll_ctl(m_epfd, EPOLL_CTL_ADD, fd_event->getFd(), &event) != 0) {
        LOG << "epoll_ctl ADD error: " << strerror(errno) << std::endl;
        return;
    }
    LOG << "add succ" << std::endl;
}

void Reactor::delFromLoop(arpc::FdEvent::ptr fd_event) {
    if (epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd_event->getFd(), nullptr) != 0) {
        LOG << "epoll_ctl DEL error" << std::endl;
        return;
    }
    LOG << "delete succ" << std::endl;
}

}  // namespace arpc