/**
 * @file fd_event.hh
 * @author alongnice
 * @brief 事件响应
 * @version 0.1
 * @date 2025-04-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <memory>
#include <functional>
#include <sys/epoll.h>

#include "../log/log.hh"

namespace arpc {

/**
 * @brief 定义IO事件类型
 *
 */
enum class IOEvent {
    READ = EPOLLIN,                      // 读事件，表示文件描述符上有数据可读
    WRITE = EPOLLOUT,                    // 写事件，表示文件描述符可以写数据
    ETModel = static_cast<int>(EPOLLET)  // 边缘触发模式，用于高效事件通知
};

class FdEvent {
public:
    typedef std::shared_ptr<FdEvent> ptr;

    /**
     * @brief 构造一个新的Fd事件对象
     *
     * @param fd 文件描述符
     */
    FdEvent(int fd) : m_fd(fd), m_listen_events(0) {
        if (fd < 0)
            throw std::invalid_argument("Invalid file descriptor: fd < 0");
    }
    ~FdEvent() {}

    /**
     * @brief 处理事件
     *
     * @param flag 事件类型
     */
    void handleEvent(int flag) {
        if (flag == static_cast<int>(IOEvent::READ)) {
            if (m_readCallback)
                m_readCallback();
            else
                LOG << "read callback not set" << std::endl;
        } else if (flag == static_cast<int>(IOEvent::WRITE)) {
            if (m_writeCallback)
                m_writeCallback();
            else
                LOG << "write callback not set" << std::endl;
        } else {
            LOG << "error flag" << std::endl;
        }
    }
    void setCallBack(IOEvent flag, std::function<void()> cb) {
        if (flag == IOEvent::READ)
            m_readCallback = cb;
        else if (flag == IOEvent::WRITE)
            m_writeCallback = cb;
        else {
            throw std::invalid_argument("Invalid IOEvent flag provided to setCallBack");
        }
    }

    /**
     * @brief 设置监听对象
     *
     * @param flag 事件类型标志
     */
    void setListenEvents(int flag) {
        if (flag != static_cast<int>(IOEvent::READ) && flag != static_cast<int>(IOEvent::WRITE) &&
            flag != static_cast<int>(IOEvent::ETModel)) {
            throw std::invalid_argument("Invalid flag passed to setListenEvents");
        }
        m_listen_events = flag;
    }

    int getFd() const {
        return m_fd;
    }  // 提供只读访问
    int getListenEvents() const {
        return m_listen_events;
    }  // 提供只读访问
    
    private:
    int m_fd{-1};
    // 读事件的回调函数
    std::function<void()> m_readCallback;
    // 写事件的回调函数
    std::function<void()> m_writeCallback;
    int m_listen_events;
};

}  // namespace arpc