/**
 * @file mutex.hh
 * @author alongnice
 * @brief 互斥锁
 * @version 0.1
 * @date 2025-04-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <pthread.h>

namespace arpc {

class MutexLock {
public:
    MutexLock() {
        pthread_mutex_init(&m_mutex, nullptr);
    }
    ~MutexLock() {
        pthread_mutex_destroy(&m_mutex);
    }

    void lock() {
        if (!m_is_lock) {
            pthread_mutex_lock(&m_mutex);
            m_is_lock = true;
        }
    }

    void unlock() {
        if (m_is_lock) {
            pthread_mutex_unlock(&m_mutex);
            m_is_lock = false;
        }
    }

private:
    pthread_mutex_t m_mutex;
    bool m_is_lock{false};
};

}  // namespace arpc