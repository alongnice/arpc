/**
 * @file log.hh
 * @author alongnice
 * @brief 日志添加定位辅助内容
 * @version 0.1
 * @date 2025-04-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <sstream>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>

namespace arpc {
#define LOG log()

/**
 * @brief 获取日志信息
 *
 * @return std::stringstream&
 */
std::stringstream& log() {
    static std::stringstream ss;
    ss.str("");                         // 清空流内容
    ss.clear();                         // 清空流状态
    ss << "[]" << time(NULL)            // 时间戳
       << "] [" << getpid()             // 进程id
       << "] [" << syscall(SYS_gettid)  // 线程id
       << "] [" << __FILE__             // 所在文件
       << "] [" << __func__             // 所在函数
       << "] [" << __LINE__             // 所在行
       << "]  ";
    return ss;
}

}  // namespace arpc