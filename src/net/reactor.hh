/**
 * @file reactor.hh
 * @brief 反应器模式实现，用于事件循环和IO多路复用
 * @author Your Name
 * @version 1.0
 * @date 2023
 */

#pragma once

#include <sys/epoll.h>
#include <vector>

#include "fd_event.hh"
#include "mutex.hh"

namespace arpc {

/**
 * @brief 反应器类，用于管理事件循环
 * @details 基于epoll实现的事件循环，用于处理文件描述符的IO事件
 */
class Reactor {
public:
    /**
     * @brief 构造函数
     */
    Reactor();

    /**
     * @brief 析构函数
     */
    ~Reactor(){};

    /**
     * @brief 添加文件描述符事件到事件循环
     * @param fd_event 文件描述符事件对象
     * @param events 要监听的事件类型
     */
    void add2Loop(arpc::FdEvent::ptr fd_event, int events);

    /**
     * @brief 从事件循环中删除文件描述符事件
     * @param fd_event 要删除的文件描述符事件对象
     */
    void delFromLoop(arpc::FdEvent::ptr fd_event);

private:
    /**
     * @brief 事件循环主函数
     */
    void loop();

    /**
     * @brief 初始化反应器
     * @return 初始化是否成功
     */
    bool init();

    int m_epfd;
    bool m_stop_flag;
    int m_pending_tasks;
    MutexLock lock;

    std::vector<arpc::FdEvent::ptr> m_fds;
};

}  // namespace arpc